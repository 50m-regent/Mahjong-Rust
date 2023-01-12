use crate::internal::tiles::Tiles;

pub struct Player {
    tiles: Tiles,
    score: u32,
}

impl Player {
    pub fn new() -> Player {
        Player {
            tiles: Tiles::from(vec![]),
            score: 0,
        }
    }
}