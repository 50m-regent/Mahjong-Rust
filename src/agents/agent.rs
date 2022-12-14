use crate::player::Player;
use crate::internal::tile::Tile;

pub trait Agent {
    fn discard(&self, player: &mut Player) -> Tile;
}