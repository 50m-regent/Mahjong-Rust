mod agents;
mod internal;
mod mahjong;
mod player;

use internal::{tile, tiles::Tiles, wind::Wind};
use tile::Tile;
use agents::greedy::GreedyAgent;
use mahjong::Mahjong;

fn main() {
    let tiles = Tiles::from(Vec::from([
        Tile::C1,
        Tile::C1,
        Tile::C1,
        Tile::C2,
        Tile::C2,
        Tile::C3,
        Tile::C4,
        Tile::C5,
        Tile::C6,
        Tile::C7,
        Tile::C8,
        Tile::C9,
        Tile::C9,
        Tile::C9,
    ]));
    
    println!("{}", tile::to_str(Tile::White));

    let game = Mahjong::four_players(
        Wind::East,
        true,
        (
            GreedyAgent {},
            GreedyAgent {},
            GreedyAgent {},
            GreedyAgent {},
        ),
    );
}