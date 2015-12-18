//! GPIO module.
//! http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/
//! https://www.raspberrypi.org/documentation//hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
//!  LED ON, Zero -> CLR
//!        , Pi 1 B+ -> SET

use super::addr::Addr;


#[allow(dead_code)]
pub enum Function {
    Input      = 0b000,
    Output     = 0b001,
    Alternate0 = 0b100,
    Alternate1 = 0b101,
    Alternate2 = 0b110,
    Alternate3 = 0b111,
    Alternate4 = 0b011,
    Alternate5 = 0b010,
}


pub enum Output {
    CLEAR,
    SET,
}


pub enum GpioPin {
    #[cfg(any(RPi_a, RPi_aplus))]
    OkLed = 16,
    #[cfg(any(RPi_zero, RPi_bplus, RPi2_b))]
    OkLed = 47,

    Spi0Ce1N = 7,
    Spi0Ce0N = 8,
    Spi0Miso = 9,
    Spi0Mosi = 10,
    Spi0Sclk = 11,

    Ili9340Dc = 17,
    Ili9340Res = 18,
}


pub fn set_pin_function(pin_number: GpioPin, func: Function)
{
    let n                  = pin_number as usize;
    let gpf_sel_number:usize = n / 10;
    let gpf_sel_addr  :usize = Addr::GpioBase.to_usize() + (gpf_sel_number * 0x4);
    let set_value      = (func as u32) << (3 * (n % 10));

    unsafe {
        *(gpf_sel_addr as *mut u32) = set_value;
    }
}


pub fn write_output_pin(pin_number: GpioPin, mode: Output)
{
    let n = pin_number as usize;
    let register =
        if n <= 31 {
            match mode {
                Output::SET   => Addr::GpioGpSet0.to_usize(),
                Output::CLEAR => Addr::GpioGpClr0.to_usize(),
            }
        } else {
            match mode {
                Output::SET   => Addr::GpioGpSet1.to_usize(),
                Output::CLEAR => Addr::GpioGpClr1.to_usize(),
            }
        };

    let addr = register;
    unsafe {
        *(addr as *mut u32) = 1 << (n % 32);
    }
}


#[inline(never)]
pub fn dummy_wait()
{
    unsafe {
        asm!("
            mov r2,#0xF0000
        inner_loop:
            sub r2, #1
            eor r1, r2, r1
            cmp r2, #0
            bne inner_loop"
            :
            :
            : "r1", "r2"
            );
    }
}


unsafe fn set_bit(addr: usize, val: u32, clobbered_mask: u32) {
    let ptr = addr as *mut u32;
    let mut current_val = *ptr;

    // Keep Not write value.
    let new_val = (current_val & !clobbered_mask) | (val & clobbered_mask);
    *ptr = new_val;
}


// Only the SPI0 controller is available on the header pin.
fn init_spi() {
    // Set GPIO function for SPI0.
    set_pin_function(GpioPin::Spi0Ce1N, Function::Alternate0);
    set_pin_function(GpioPin::Spi0Ce0N, Function::Alternate0);
    set_pin_function(GpioPin::Spi0Miso, Function::Alternate0);
    set_pin_function(GpioPin::Spi0Mosi, Function::Alternate0);
    set_pin_function(GpioPin::Spi0Sclk, Function::Alternate0);

    // Set SPI0 CS register to all zero.
    unsafe {
        *(Addr::Spi0RegisterCs.to_usize() as *mut u32) = 0;

        // Clear TX and RX FIFO.
        // With memory barrier.
        // asm!("dmb");
        *(Addr::Spi0RegisterCs.to_usize() as *mut u32) = 0x00000030;

        // Set data mode.
        // With memory barrier.
        // asm!("dmb");
        *(Addr::Spi0RegisterCs.to_usize() as *mut u32) = 0x00000030;
    }
}


unsafe fn spi_transfer(val: u8) -> u8 {
    // Clear TX and RX fifos.
    set_bit(Addr::Spi0RegisterCs.to_usize(), 0x00000030, 0x00000030);

    // Set TA = 1.
    set_bit(Addr::Spi0RegisterCs.to_usize(), 1 << 7, 1 << 7);

    // Wait for TXD.
    loop {
        // WTF
        // let cs_reg :u32= volatile_load(Addr::Spi0RegisterFifo.to_usize() as *const u32);
        let mut val = 0;
        asm!(
            "ldr r1, [r0]"
            : "={r1}"(val)
            : "{r0}"(Addr::Spi0RegisterCs.to_usize())
            : "volatile", "intel"
            );
        if val == 0x30 {
            break;
        }
    }

    // Write to FIFO
    *(Addr::Spi0RegisterFifo.to_usize() as *mut u8) = val;

    // Wait for DONE
    loop {
        // WTF
        // let cs_reg :u32= volatile_load(Addr::Spi0RegisterFifo.to_usize() as *const u32);
        let mut val = 0;
        asm!(
            "ldr r1, [r0]"
            : "={r1}"(val)
            : "{r0}"(Addr::Spi0RegisterCs.to_usize())
            : "volatile", "intel"
            );
        if val == 0x00010000 {
            break;
        }
    }

    // Write to FIFO
    let read_data = *(Addr::Spi0RegisterFifo.to_usize() as *mut u8);

    // Set TA = 1.
    set_bit(Addr::Spi0RegisterCs.to_usize(), 0, 1 << 7);

    read_data
}


/// For ILI9340 IC.
fn ili9340_write_command(command: u8) {
    write_output_pin(GpioPin::Ili9340Dc, Output::CLEAR);
    unsafe {
        spi_transfer(command);
    }
    write_output_pin(GpioPin::Ili9340Dc, Output::SET);
}

// SPI Write Data
// D/C=HIGH then,write data(8bit)
fn ili9340_write_data(data: u8)
{
    write_output_pin(GpioPin::Ili9340Dc, Output::SET);
    unsafe {
        spi_transfer(data);
    }
}
