fn main() {
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