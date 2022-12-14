use crate::internal::tile::Tile;

pub struct Tiles {
    tiles_bit: [u64; 4],
}

impl Tiles {
    pub fn from(vec: Vec<Tile>) -> Tiles {
        let mut tiles = Tiles {
            tiles_bit: [0; 4],
        };
        tiles.init(vec);

        tiles
    }

    pub fn add(&mut self, tile: Tile) -> bool {
        if 0 != self.tiles_bit[3] & tile {
            return false;
        } else if 0 != self.tiles_bit[2] & tile {
            self.tiles_bit[3] |= tile;
        } else if 0 != self.tiles_bit[1] & tile {
            self.tiles_bit[2] |= tile;
        } else if 0 != self.tiles_bit[0] & tile {
            self.tiles_bit[1] |= tile;
        } else {
            self.tiles_bit[0] |= tile;
        }
 
        true
    }

    fn init(&mut self, tiles: Vec<Tile>) {
        for tile in tiles {
            self.add(tile);
        }
    }
}