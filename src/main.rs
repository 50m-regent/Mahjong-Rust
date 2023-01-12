mod agents;
mod internal;
mod mahjong;

use internal::{tile, tiles::Tiles, wind::Wind};
use tile::Tile;
use agents::greedy::GreedyAgent;
use mahjong::Mahjong;

fn main() {
    let tiles: Tiles = Tiles::from(vec![
        Tile::M1,
        Tile::M1,
        Tile::M1,
        Tile::M2,
        Tile::M3,
        Tile::M4,
        Tile::M5,
        Tile::Mr,
        Tile::M6,
        Tile::M7,
        Tile::M8,
        Tile::M9,
        Tile::M9,
        Tile::M9,
    ]);

    let game: Mahjong<GreedyAgent, GreedyAgent, GreedyAgent, GreedyAgent> = Mahjong::four_players(
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