use crate::agents::agent::Agent;
use crate::internal::{tile::Tile, player::Player};

pub struct GreedyAgent {}

impl Agent for GreedyAgent {
    fn discard(&self, player: &mut Player) -> Tile {
        Tile::White
    }
}