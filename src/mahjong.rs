use crate::internal::{wind::Wind, state::State};
use crate::agents::agent::Agent;
use crate::player::Player;

pub struct Mahjong<T, U, V, W> where
    T: Agent,
    U: Agent,
    V: Agent,
    W: Agent {
    end_wind: Wind,
    has_red: bool,
    agents: (T, U, V, W),

    players: (Player, Player, Player, Player),
    states: Vec<State>,
}

impl<T: Agent, U: Agent, V: Agent, W: Agent> Mahjong<T, U, V, W> {
    pub fn four_players(
        end_wind: Wind,
        has_red: bool,
        agents: (T, U, V, W),
    ) -> Mahjong<T, U, V, W> {
        Mahjong {
            end_wind: end_wind,
            has_red: has_red,
            agents: agents,

            players: (
                Player::new(),
                Player::new(),
                Player::new(),
                Player::new(),
            ),
            states: Vec::new(),
        }
    }

    
}