#include "magic_search.h"
#include "magic_random.h"
#include "bishop_attacks.h" 
#include "rook_attacks.h"
#include "slider_helpers.h"

const U64 rook_magics[64] = {
    0x0080001820804000ULL,
    0x0040004020001004ULL,
    0x0200208042001008ULL,
    0x0100081000050021ULL,
    0x0200042010020008ULL,
    0x120002002c181045ULL,
    0x0400280120921004ULL,
    0x00800d0003402080ULL,
    0x0020801080204002ULL,
    0x1001002040011081ULL,
    0x8213004020001304ULL,
    0x0082000a00421022ULL,
    0xc145000500080010ULL,
    0x0e96001084020008ULL,
    0x0001010001040200ULL,
    0x2060802840800900ULL,
    0x0c2081800020400cULL,
    0x3000404000201000ULL,
    0x8002020020804012ULL,
    0x0410018008001080ULL,
    0x0288808008000401ULL,
    0x0001010004000802ULL,
    0x0086040010018802ULL,
    0x0a00020000a40ac5ULL,
    0x0080004440002000ULL,
    0x8800200040005008ULL,
    0x21a0080040401000ULL,
    0x0000090100100020ULL,
    0x0000080100110004ULL,
    0x0001000300080400ULL,
    0x2080500400186b22ULL,
    0x1020304200008401ULL,
    0x0200400024800089ULL,
    0x4020402002401009ULL,
    0x0000802004801004ULL,
    0x0030008008080100ULL,
    0x1002002012000904ULL,
    0x0090800400800200ULL,
    0x0014021004000108ULL,
    0x8000244882000104ULL,
    0x0002824000228000ULL,
    0x0100201000404001ULL,
    0x0181004020010010ULL,
    0x0060100061030008ULL,
    0x0000080011010004ULL,
    0x1080020004008080ULL,
    0x1000010208040010ULL,
    0x2040041142860021ULL,
    0x0880004000200040ULL,
    0x140300e8820c4600ULL,
    0x1081007e40200100ULL,
    0x0100801000080080ULL,
    0x1408008008040080ULL,
    0x2240040080020080ULL,
    0x2800880142100400ULL,
    0x160210508d040200ULL,
    0x8000120484204102ULL,
    0xd422030082281042ULL,
    0x0005108009204202ULL,
    0x2008081000042101ULL,
    0x0002000850218402ULL,
    0x0011000802040001ULL,
    0x2108009058020104ULL,
    0x0001010406482282ULL
};

const U64 bishop_magics[64] = {
    0x5404208200410100ULL,
    0x0020020208411900ULL,
    0x452109040a801000ULL,
    0x0004240180008103ULL,
    0x0404050442008089ULL,
    0x0428441004014804ULL,
    0x01030c0212420080ULL,
    0x0001804050104811ULL,
    0x0000420202240500ULL,
    0x2000a02210860090ULL,
    0x0800440434004010ULL,
    0x2008024081000238ULL,
    0x0021640420880020ULL,
    0x0001220250046120ULL,
    0x8880058804132021ULL,
    0x4420008618010c90ULL,
    0x02200006204c2110ULL,
    0x0011020810208492ULL,
    0x0008000108010016ULL,
    0x02e4001844006a00ULL,
    0x8040808400e00008ULL,
    0x40c4101202020108ULL,
    0x0236003108310400ULL,
    0x1400480424122800ULL,
    0x2d88880820200128ULL,
    0x0802020810100210ULL,
    0x0042240020810400ULL,
    0x0040040002110010ULL,
    0x8200840030802000ULL,
    0x4090010241808880ULL,
    0x020803a021048843ULL,
    0x00021200008c4502ULL,
    0x0084210811241082ULL,
    0x00208a3120600400ULL,
    0x0406482200100408ULL,
    0x0100020080980080ULL,
    0x1910120080c49004ULL,
    0x0820008900148044ULL,
    0x0021010c08011404ULL,
    0x20608a0480284c14ULL,
    0x008088143080401fULL,
    0x00222090041a0840ULL,
    0x0002424020801000ULL,
    0x8000002019014800ULL,
    0x0400040094000200ULL,
    0x200802004a001410ULL,
    0x00200400821a00a0ULL,
    0x0402080052801300ULL,
    0x0006091120100204ULL,
    0x0000220802080000ULL,
    0x0178804404048003ULL,
    0x0040084084040000ULL,
    0x0820c01020220858ULL,
    0x080c090828082422ULL,
    0x0020a00421304004ULL,
    0x04103410c4004402ULL,
    0x28a1c04404201208ULL,
    0x0080042404040480ULL,
    0x0000019954040430ULL,
    0x000c81a000840420ULL,
    0x0008020822c55400ULL,
    0x0808280820188082ULL,
    0x0c02092004040042ULL,
    0x0040140404022821ULL
};


//vestigial function, but was pretty painful to go through so imma keep it here 

U64 find_magic(int square , int relevant_bits , int is_bishop){
    U64 occupancies[4096] , attacks[4096] , used_attacks[4096];
    U64 attack_mask = is_bishop ? bishop_attack_mask(square) : rook_attack_mask(square);

    if (relevant_bits < 0 || relevant_bits > 12 || count_bits(attack_mask) != relevant_bits){
        return 0ULL;
    }

    int occ_indices = 1 << relevant_bits;
    for (int index = 0 ; index < occ_indices ; index++){
        occupancies[index] = set_occupancy(index , relevant_bits , attack_mask); 
        attacks[index] = is_bishop ? bishop_attack_vector(square , occupancies[index]) : rook_attack_vector(square , occupancies[index]);
    }
    for (int random_count = 0 ; random_count < 100000000 ; random_count++){
        U64 magic_number = magic_random_candidate();
        if (count_bits((attack_mask * magic_number) & 0xFF00000000000000ULL) < 6) continue;
        memset(used_attacks , 0ULL , sizeof(used_attacks));
        int index , fail;
        for(index = 0 , fail = 0 ; !fail && index < occ_indices ; index++){
            int magic_index = (int)((occupancies[index ] * magic_number) >> (64 - relevant_bits));

            // on empty index available
            if (used_attacks[magic_index] == 0ULL){
                //init used attacks
                used_attacks[magic_index] = attacks[index];
            } else if (used_attacks[magic_index] != attacks[index]){
                fail = 1;
            }
        }
        if (!fail){
            return magic_number;
        }
    }
    printf("  Magic number fails!\n");
    return 0ULL;
}

