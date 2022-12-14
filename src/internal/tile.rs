use std::ops;

#[derive(Copy, Clone)]
pub enum Tile {
    None = 0,

    C1 = 1 << 0,
    C2 = 1 << 1,
    C3 = 1 << 2,
    C4 = 1 << 3,
    C5 = 1 << 4,
    CR = 1 << 5,
    CG = 1 << 6,
    C6 = 1 << 7,
    C7 = 1 << 8,
    C8 = 1 << 9,
    C9 = 1 << 10,

    D1 = 1 << 11,
    D2 = 1 << 12,
    D3 = 1 << 13,
    D4 = 1 << 14,
    D5 = 1 << 15,
    DR = 1 << 16,
    DG = 1 << 17,
    D6 = 1 << 18,
    D7 = 1 << 19,
    D8 = 1 << 20,
    D9 = 1 << 21,

    B1 = 1 << 22,
    B2 = 1 << 23,
    B3 = 1 << 24,
    B4 = 1 << 25,
    B5 = 1 << 26,
    BR = 1 << 27,
    BG = 1 << 28,
    B6 = 1 << 29,
    B7 = 1 << 30,
    B8 = 1 << 31,
    B9 = 1 << 32,

    East  = 1 << 33,
    North = 1 << 34,
    West  = 1 << 35,
    South = 1 << 36,

    White = 1 << 37,
    Green = 1 << 38,
    Red   = 1 << 39,
}

impl ops::BitAnd<Tile> for u64 {
    type Output = u64;

    fn bitand(self, rhs: Tile) -> Self::Output {
        self & rhs as u64
    }
}

impl ops::BitOrAssign<Tile> for u64 {
    fn bitor_assign(&mut self, rhs: Tile) {
        *self |= rhs as u64;
    }
}

pub const fn to_str(tile: Tile) -> &'static str {
    match tile {
        Tile::None => "None",

        Tile::C1 => "C1",
        Tile::C2 => "C2",
        Tile::C3 => "C3",
        Tile::C4 => "C4",
        Tile::C5 => "C5",
        Tile::CR => "CR",
        Tile::CG => "CG",
        Tile::C6 => "C6",
        Tile::C7 => "C7",
        Tile::C8 => "C8",
        Tile::C9 => "C9",

        Tile::D1 => "D1",
        Tile::D2 => "D2",
        Tile::D3 => "D3",
        Tile::D4 => "D4",
        Tile::D5 => "D5",
        Tile::DR => "DR",
        Tile::DG => "DG",
        Tile::D6 => "D6",
        Tile::D7 => "D7",
        Tile::D8 => "D8",
        Tile::D9 => "D9",

        Tile::B1 => "B1",
        Tile::B2 => "B2",
        Tile::B3 => "B3",
        Tile::B4 => "B4",
        Tile::B5 => "B5",
        Tile::BR => "BR",
        Tile::BG => "BG",
        Tile::B6 => "B6",
        Tile::B7 => "B7",
        Tile::B8 => "B8",
        Tile::B9 => "B9",

        Tile::East  => "WE",
        Tile::South => "WS",
        Tile::West  => "WW",
        Tile::North => "WN",

        Tile::White => "SW",
        Tile::Green => "SG",
        Tile::Red   => "SR",
    }
}