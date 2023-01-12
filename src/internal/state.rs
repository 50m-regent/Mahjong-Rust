use crate::internal::{wind::Wind, action::Action, player::Player};

pub struct State {
    wind: Wind,
    round_count: u8,
    players: (Player, Player, Player, Player),
    dealer_index: u8,
    turn: u8,
    action: Action,
}