use std::ops;

#[derive(Copy, Clone, Debug)]
pub enum Tile {
    None = 0,

    M1 = 1 << 0,
    M2 = 1 << 1,
    M3 = 1 << 2,
    M4 = 1 << 3,
    M5 = 1 << 4,
    Mr = 1 << 5,
    Mg = 1 << 6,
    M6 = 1 << 7,
    M7 = 1 << 8,
    M8 = 1 << 9,
    M9 = 1 << 10,

    P1 = 1 << 11,
    P2 = 1 << 12,
    P3 = 1 << 13,
    P4 = 1 << 14,
    P5 = 1 << 15,
    Pr = 1 << 16,
    Pg = 1 << 17,
    P6 = 1 << 18,
    P7 = 1 << 19,
    P8 = 1 << 20,
    P9 = 1 << 21,

    S1 = 1 << 22,
    S2 = 1 << 23,
    S3 = 1 << 24,
    S4 = 1 << 25,
    S5 = 1 << 26,
    Sr = 1 << 27,
    Sg = 1 << 28,
    S6 = 1 << 29,
    S7 = 1 << 30,
    S8 = 1 << 31,
    S9 = 1 << 32,

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

        Tile::M1 => "M1",
        Tile::M2 => "M2",
        Tile::M3 => "M3",
        Tile::M4 => "M4",
        Tile::M5 => "M5",
        Tile::Mr => "Mr",
        Tile::Mg => "Mg",
        Tile::M6 => "M6",
        Tile::M7 => "M7",
        Tile::M8 => "M8",
        Tile::M9 => "M9",

        Tile::P1 => "P1",
        Tile::P2 => "P2",
        Tile::P3 => "P3",
        Tile::P4 => "P4",
        Tile::P5 => "P5",
        Tile::Pr => "Pr",
        Tile::Pg => "Pg",
        Tile::P6 => "P6",
        Tile::P7 => "P7",
        Tile::P8 => "P8",
        Tile::P9 => "P9",

        Tile::S1 => "S1",
        Tile::S2 => "S2",
        Tile::S3 => "S3",
        Tile::S4 => "S4",
        Tile::S5 => "S5",
        Tile::Sr => "Sr",
        Tile::Sg => "Sg",
        Tile::S6 => "S6",
        Tile::S7 => "S7",
        Tile::S8 => "S8",
        Tile::S9 => "S9",

        Tile::East  => "We",
        Tile::South => "Ws",
        Tile::West  => "Ww",
        Tile::North => "Wn",

        Tile::White => "Dw",
        Tile::Green => "Dg",
        Tile::Red   => "Dr",
    }
}