#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const inline std::vector<unsigned short> ALL_BLOCKS({
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 33, 34, 35, 36, 37, 38, 39, 44, 45, 46, 47, 48, 49, 55, 56, 57, 58, 59, 66, 67, 68, 69, 77, 78, 79, 88, 89, 99,
    111, 112, 113, 114, 115, 116, 117, 118, 119, 122, 123, 124, 125, 126, 127, 128, 129, 133, 134, 135, 136, 137, 138, 139, 144, 145, 146, 147, 148, 149, 155, 156, 157, 158, 159, 166, 167, 168, 169, 177, 178, 179, 188, 189, 199,
    222, 223, 224, 225, 226, 227, 228, 229, 233, 234, 235, 236, 237, 238, 239, 244, 245, 246, 247, 248, 249, 255, 256, 257, 258, 259, 266, 267, 268, 269, 277, 278, 279, 288, 289, 299,
    333, 334, 335, 336, 337, 338, 339, 344, 345, 346, 347, 348, 349, 355, 356, 357, 358, 359, 366, 367, 368, 369, 377, 378, 379, 388, 389, 399,
    444, 445, 446, 447, 448, 449, 455, 456, 457, 458, 459, 466, 467, 468, 469, 477, 478, 479, 488, 489, 499,
    555, 556, 557, 558, 559, 566, 567, 568, 569, 577, 578, 579, 588, 589, 599,
    666, 667, 668, 669, 677, 678, 679, 688, 689, 699,
    777, 778, 779, 788, 789, 799,
    888, 889, 899,
    999
});

std::unordered_map<
    unsigned int,
    std::vector<
        std::pair<
            unsigned int,
            std::pair<unsigned char, unsigned char>
        >
    >
> cache_data;

const inline unsigned short minimize(
    unsigned short block
) {
    if (0 == block) {
        return 0;
    }

    if (10 > block) {
        return 1;
    } else if (100 > block) {
        const unsigned char min_tile = block / 10;
        block -= (min_tile - 1) * 11;
    } else {
        const unsigned char min_tile = block / 100;
        block -= (min_tile - 1) * 111;
    }

    return block;
}

const inline std::pair<
    unsigned char,
    unsigned char
> calculate_xiangting(
    unsigned short block
) {
    block = minimize(block);
    const unsigned char left_tiles  = minimize(block / 10);
    const unsigned char right_tiles = minimize(block % 100);

    unsigned char mianzi_xiangting = 2;
    if (0 == block) {
        mianzi_xiangting = 3;
    } else if (111 == block || 123 == block) {
        mianzi_xiangting = 0;
    } else if (
        11 == left_tiles || 11 == right_tiles ||
        12 == left_tiles || 12 == right_tiles ||
        13 == left_tiles || 13 == right_tiles
    ) {
        mianzi_xiangting = 1;
    }

    unsigned char tou_xiangting = 1;
    if (0 == block) {
        tou_xiangting = 2;
    } else if (11 == left_tiles || 11 == right_tiles) {
        tou_xiangting = 0;
    }

    return {mianzi_xiangting, tou_xiangting};
}

const inline std::vector<unsigned char> add_tile_count(
    std::vector<unsigned char> tile_count,
    const unsigned short block
) {
    assert(9 == tile_count.size());

    if (0 < block) {
        ++tile_count[block % 10 - 1];
    }
    if (10 < block) {
        ++tile_count[(block / 10) % 10 - 1];
    }
    if (100 < block) {
        ++tile_count[(block / 100) - 1];
    }

    return tile_count;
}

const unsigned int bitize(
    const std::vector<unsigned short> blocks
) {
    std::vector<unsigned char> tile_count(9, 0);
    for (const unsigned short block: blocks) {
        tile_count = add_tile_count(tile_count, block);
    }

    unsigned int bit = 0;
    for (unsigned char i = 0; i < 9; ++i) {
        bit += tile_count[i] * std::pow(5, i);
    }

    return bit;
}

const void cache(
    const std::vector<unsigned short> blocks
) {
    assert(5 == blocks.size());

    std::vector<
        std::pair<
            unsigned int,
            std::pair<unsigned char, unsigned char>
        >
    > blocks_data;
    for (const unsigned short block: blocks) {
        blocks_data.emplace_back(std::make_pair(
            bitize({block}),
            calculate_xiangting(block)
        ));
    }
    std::sort(
        blocks_data.begin(), blocks_data.end(),
        [](
            std::pair<
                unsigned int,
                std::pair<unsigned char, unsigned char>
            > a,
            std::pair<
                unsigned int,
                std::pair<unsigned char, unsigned char>
            > b
        ) {
            return a.second.first > b.second.first;
        }
    );

    const unsigned int bit = bitize(blocks);
    if (!cache_data.contains(bit)) {
        cache_data.emplace(bit, blocks_data);
    } else {
        // cache_data.emplace(bit, blocks_data);
    }
}

const void search(
    std::vector<unsigned short> blocks,
    const std::vector<unsigned char> tile_count
) {
    for (const unsigned short block: ALL_BLOCKS) {
        if (!blocks.empty() && block < blocks.back()) {
            continue;
        }

        const std::vector<unsigned char> new_count = add_tile_count(tile_count, block);
        if (*std::max_element(new_count.begin(), new_count.end()) > 4) {
            continue;
        }

        blocks.emplace_back(block);
        if (5 == blocks.size()) {
            cache(blocks);
        } else {
            search(blocks, new_count);
        }
        blocks.pop_back();
    }
}

const void print_cache() {
    for (const std::pair<
        unsigned int,
        std::vector<
            std::pair<
                unsigned int,
                std::pair<unsigned char, unsigned char>
            >
        >
    > cache: cache_data) {
        unsigned short pai_bits[4] = {};
        unsigned int pai_bit = cache.first;
        for (unsigned char i = 0; i < 9; ++i, pai_bit /= 5) {
            for (unsigned char j = 0; j < pai_bit % 5; ++j) {
                pai_bits[j - 1] |= 1 << i;
            }
        }
        for (unsigned char i = 0; i < 4; ++i) {
            std::cout << pai_bits[i] << " ";
        }

        for (const std::pair<
            unsigned int,
            std::pair<unsigned char, unsigned char>
        > block: cache.second) {
            
        }
        std::cout << std::endl;
    }
}

int main() {
    search({}, std::vector<unsigned char>(9, 0));
    print_cache();
}