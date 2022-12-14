use crate::agents::agent::Agent;
use crate::player::Player;
use crate::internal::tile::Tile;

pub struct GreedyAgent {}

impl Agent for GreedyAgent {
    fn discard(&self, player: &mut Player) -> Tile {
        Tile::White
    }
}