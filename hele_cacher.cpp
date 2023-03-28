#include <iostream>
#include <vector>
#include <map>
#include <cmath>

class Block {
public:
    Block(const unsigned short raw_block) :
        raw_block(raw_block),
        bit_block(this->bitize()),
        xiangting(this->calculate_xiangting())
    {
        assert(1000 > raw_block);
    }

    const inline unsigned get_bit() const {
        return this->bit_block;
    }

    const inline unsigned char get_tile(const unsigned char n) const {
        assert(3 > n);

        switch (n) {
            case 0:
                return this->raw_block / 100;
            case 1:
                return this->raw_block / 10 % 10;
            case 2:
                return this->raw_block % 10;
        }

        return 0;
    }

    const inline unsigned char get_xiangting() const {
        return this->xiangting;
    }

private:
    const inline unsigned short tile_bit(const unsigned char tile) const {
        assert(10 > tile);
        return tile ? 1 << (tile - 1) : 0;
    }

    const inline unsigned bitize() const {
        return
            (this->tile_bit(this->get_tile(0)) << 18) |
            (this->tile_bit(this->get_tile(1)) << 9) |
            this->tile_bit(this->get_tile(2));
    }

    const inline unsigned char minimize(const unsigned short block) const {
        assert(1000 > block);

        if (0 == block) {
            return 0;
        }
        if (10 > block) {
            return 1;
        } else if (100 > block) {
            const unsigned char min_tile = block / 10;
            return block - (min_tile - 1) * 11;
        } else {
            const unsigned char min_tile = block / 100;
            return block - (min_tile - 1) * 111;
        }
    }
    
    const inline unsigned char calculate_xiangting() const {
        const unsigned char
            minimum_block = this->minimize(this->raw_block),
            left_block    = this->minimize(this->raw_block / 10),
            right_block   = this->minimize(this->raw_block % 100);

        if (0 == minimum_block) {
            return 3;
        } else if (111 == minimum_block || 123 == minimum_block) {
            return 0;
        } else if (
            11 == left_block || 11 == right_block ||
            12 == left_block || 12 == right_block ||
            13 == left_block || 13 == right_block
        ) {
            return 1;
        } else {
            return 2;
        }
    }
    
    const unsigned short raw_block;
    const unsigned bit_block;
    const unsigned char xiangting;
};

const inline std::vector<Block> ALL_BLOCKS({
    0,
    1,
        11, 12, 13, 14, 15, 16, 17, 18, 19,
        111, 112, 113, 114, 115, 116, 117, 118, 119,
        122, 123, 124, 125, 126, 127, 128, 129,
        133, 134, 135, 136, 137, 138, 139,
        144, 145, 146, 147, 148, 149,
        155, 156, 157, 158, 159,
        166, 167, 168, 169,
        177, 178, 179,
        188, 189,
        199,
    2,
        22, 23, 24, 25, 26, 27, 28, 29,
        222, 223, 224, 225, 226, 227, 228, 229,
        233, 234, 235, 236, 237, 238, 239,
        244, 245, 246, 247, 248, 249,
        255, 256, 257, 258, 259,
        266, 267, 268, 269,
        277, 278, 279,
        288, 289,
        299,
    3,
        33, 34, 35, 36, 37, 38, 39,
        333, 334, 335, 336, 337, 338, 339,
        344, 345, 346, 347, 348, 349,
        355, 356, 357, 358, 359,
        366, 367, 368, 369,
        377, 378, 379,
        388, 389,
        399,
    4,
        44, 45, 46, 47, 48, 49,
        444, 445, 446, 447, 448, 449,
        455, 456, 457, 458, 459,
        466, 467, 468, 469,
        477, 478, 479,
        488, 489,
        499,
    5,
        55, 56, 57, 58, 59,
        555, 556, 557, 558, 559,
        566, 567, 568, 569,
        577, 578, 579,
        588, 589,
        599,
    6,
        66, 67, 68, 69,
        666, 667, 668, 669,
        677, 678, 679,
        688, 689,
        699,
    7,
        77, 78, 79,
        777, 778, 779,
        788, 789,
        799,
    8,
        88, 89,
        888, 889,
        899,
    9,
        99,
        999
});

const bool has_too_many_tiles_of_kind(const std::vector<Block> blocks) {
    std::vector<unsigned char> count(9, 0);
    for (const Block block: blocks) {
        if (block.get_tile(0) && ++count[block.get_tile(0) - 1] > 4) {
            return true;
        }
        if (block.get_tile(1) && ++count[block.get_tile(1) - 1] > 4) {
            return true;
        }
        if (block.get_tile(2) && ++count[block.get_tile(2) - 1] > 4) {
            return true;
        }
    }

    return false;
}

const unsigned count_tiles(const std::vector<Block> blocks) {
    unsigned count = 0;
    for (const Block block: blocks) {
        count += std::pow(5, block.get_tile(0) - 1);
        count += std::pow(5, block.get_tile(1) - 1);
        count += std::pow(5, block.get_tile(2) - 1);
    }

    return count;
}

void print(
    const unsigned count,
    const std::tuple<unsigned, unsigned, unsigned, unsigned> blocks
) {
    std::cout <<
        count << " " <<
        std::get<0>(blocks) << " " <<
        std::get<1>(blocks) << " " <<
        std::get<2>(blocks) << " " <<
        std::get<3>(blocks) <<
    std::endl;
    
    /*
    unsigned tile_count = count;
    for (unsigned i = 1; i <= 9; ++i, tile_count /= 5) {
        for (unsigned j = 0; j < (tile_count % 5); ++j) {
            std::cout << i;
        }
    }
    std::cout << " ";
    for (int j = 2; j >= 0; --j) {
        for (unsigned k = 1; k <= 9; ++k) {
            if (std::get<0>(blocks) & (1 << (j * 9 + k - 1))) {
                std::cout << k;
            }
        }
    }
    std::cout << " ";
    for (int j = 2; j >= 0; --j) {
        for (unsigned k = 1; k <= 9; ++k) {
            if (std::get<1>(blocks) & (1 << (j * 9 + k - 1))) {
                std::cout << k;
            }
        }
    }
    std::cout << " ";
    for (int j = 2; j >= 0; --j) {
        for (unsigned k = 1; k <= 9; ++k) {
            if (std::get<2>(blocks) & (1 << (j * 9 + k - 1))) {
                std::cout << k;
            }
        }
    }
    std::cout << " ";
    for (int j = 2; j >= 0; --j) {
        for (unsigned k = 1; k <= 9; ++k) {
            if (std::get<3>(blocks) & (1 << (j * 9 + k - 1))) {
                std::cout << k;
            }
        }
    }
    std::cout << std::endl << std::endl;
    */
}

int main() {
    for (unsigned i1 = 0; i1 < ALL_BLOCKS.size(); ++i1) {
        const Block block1 = ALL_BLOCKS[i1];
        if (block1.get_xiangting() % 3) {
            continue;
        }

        for (unsigned i2 = i1; i2 < ALL_BLOCKS.size(); ++i2) {
            const Block block2 = ALL_BLOCKS[i2];

            if (
                block2.get_xiangting() % 3 ||
                has_too_many_tiles_of_kind({block1, block2})
            ) {
                continue;
            }

            for (unsigned i3 = i2; i3 < ALL_BLOCKS.size(); ++i3) {
                const Block block3 = ALL_BLOCKS[i3];

                if (
                    block3.get_xiangting() % 3 ||
                    has_too_many_tiles_of_kind({block1, block2, block3})
                ) {
                    continue;
                }

                for (unsigned i4 = i3; i4 < ALL_BLOCKS.size(); ++i4) {
                    const Block block4 = ALL_BLOCKS[i4];

                    if (
                        block4.get_xiangting() % 3 ||
                        has_too_many_tiles_of_kind({block1, block2, block3, block4})
                    ) {
                        continue;
                    }

                    const unsigned tile_count = count_tiles({block1, block2, block3, block4});
                    print(tile_count, std::make_tuple(block1.get_bit(), block2.get_bit(), block3.get_bit(), block4.get_bit()));
                }
            }
        }
    }
}