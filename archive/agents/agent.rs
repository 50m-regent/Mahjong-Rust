use crate::internal::{tile::Tile, player::Player};

pub trait Agent {
    fn discard(&self, player: &mut Player) -> Tile;
}