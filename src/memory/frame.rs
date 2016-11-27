//! `Frame` define a physical memory region.
//! The size is 4096 and it corresponds page size.

pub const SIZE: usize = 4096;


#[derive(PartialEq)]
pub enum FrameState {
    Free,
    Alloc,
}


#[repr(C, packed)]
pub struct Frame {
    pub order: usize,
    pub status: FrameState,
}


impl Frame {
    pub fn size(&self) -> usize
    {
        SIZE * (1 << self.order)
    }


    pub fn is_alloc(&self) -> bool
    {
        self.status == FrameState::Alloc
    }


    #[allow(dead_code)]
    pub fn is_free(&self) -> bool
    {
        !self.is_alloc()
    }
}


impl Default for Frame {
    fn default() -> Frame
    {
        Frame {
            order: 0,
            status: FrameState::Free,
        }
    }
}
