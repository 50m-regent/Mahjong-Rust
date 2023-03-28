use std::error::Error;
use std::fmt;

use crate::internal::tile;
use tile::Tile;

#[derive(Debug)]
struct TooManySameTileError {
    tile: Tile,
}

impl fmt::Display for TooManySameTileError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Too many tiles of same kind: {}", tile::to_str(self.tile))
    }
}

impl Error for TooManySameTileError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        None
    }
}

pub struct Tiles {
    tiles_bits: [u64; 4],
}

impl Tiles {
    pub fn from(vec: Vec<Tile>) -> Tiles {
        let mut tiles: Tiles = Tiles {
            tiles_bits: [0; 4],
        };
        tiles.init(vec);

        tiles
    }

    pub fn add(&mut self, tile: Tile) -> Result<(), TooManySameTileError> {
        for tiles_bit in self.tiles_bits.iter_mut() {
            if 0 == *tiles_bit & tile {
                *tiles_bit |= tile;
                return Ok(());
            }
        }

        Err(TooManySameTileError{tile})
    }

    fn init(&mut self, tiles: Vec<Tile>) {
        for tile in tiles {
            match self.add(tile) {
                Ok(()) => (),
                Err(error) => panic!("{}", error),
            }
        }
    }
}