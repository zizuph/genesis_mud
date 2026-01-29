
 /* Stonewalkers Defs */

#ifndef GUILD_NAME
#define GUILD_NAME "Stonewalkers of Thalassia"
#endif
#define GUILD_TYPE "occupational"
#define GUILD_STYLE "magic"

#define GUILD_BASE_TAX        16
#define SPELL_TAX_LEVEL_ONE   1
#define SPELL_TAX_LEVEL_TWO   0
#define SPELL_TAX_LEVEL_THREE 1
#define SPELL_TAX_LEVEL_FOUR  1
#define SPELL_TAX_LEVEL_FIVE  1
#define SPELL_TAX_LEVEL_SIX   1
#define SPELL_TAX_LEVEL_SEVEN 1
#define SPELL_TAX_LEVEL_EIGHT 5
#define SPELL_TAX_LEVEL_NINE  1
#define SPELL_TAX_LEVEL_TEN   2

#define SPELLS_ONE_FLAG       1
#define SPELLS_TWO_FLAG       2
#define SPELLS_THREE_FLAG     4
#define SPELLS_FOUR_FLAG      8
#define SPELLS_FIVE_FLAG     16
#define SPELLS_SIX_FLAG      32
#define SPELLS_SEVEN_FLAG    64
#define SPELLS_EIGHT_FLAG   128
#define SPELLS_NINE_FLAG    256
#define SPELLS_TEN_FLAG     512
#define ALL_SPELL_LEVELS (SPELLS_ONE_FLAG | SPELLS_TWO_FLAG | SPELLS_THREE_FLAG | SPELLS_FOUR_FLAG | SPELLS_FIVE_FLAG | SPELLS_SIX_FLAG | SPELLS_SEVEN_FLAG | SPELLS_EIGHT_FLAG | SPELLS_NINE_FLAG | SPELLS_TEN_FLAG)

#define GUILD_TAX(chosen) \
        (GUILD_BASE_TAX + \
        ((chosen & SPELLS_ONE_FLAG) ? SPELL_TAX_LEVEL_ONE : 0) + \
        ((chosen & SPELLS_TWO_FLAG) ? SPELL_TAX_LEVEL_TWO : 0) + \
        ((chosen & SPELLS_THREE_FLAG) ? SPELL_TAX_LEVEL_THREE : 0) + \
        ((chosen & SPELLS_FOUR_FLAG) ? SPELL_TAX_LEVEL_FOUR : 0) + \
        ((chosen & SPELLS_FIVE_FLAG) ? SPELL_TAX_LEVEL_FIVE : 0) + \
        ((chosen & SPELLS_SIX_FLAG) ? SPELL_TAX_LEVEL_SIX : 0) + \
        ((chosen & SPELLS_SEVEN_FLAG) ? SPELL_TAX_LEVEL_SEVEN : 0) + \
        ((chosen & SPELLS_EIGHT_FLAG) ? SPELL_TAX_LEVEL_EIGHT : 0) + \
        ((chosen & SPELLS_NINE_FLAG) ? SPELL_TAX_LEVEL_NINE : 0) + \
        ((chosen & SPELLS_TEN_FLAG) ? SPELL_TAX_LEVEL_TEN : 0))

#define SS_CARVED             114050
#define SS_PUNISHMENT         114051
#define SS_PATRON_ELEMENTAL   114052
#define SS_WALKER_STATUS      114054
#define SS_PRAYER             114055
#define SS_ELEMENT_SPIRIT     114056
#define SS_WALKER_PUNISHMENT  114057
#define SS_WALKER_CHOSEN      114058
#define SS_WALKER_TITLE       114059

#define WORSTART "/d/Calia/worshippers/temple/startroom"
#define WORSHIPSOUL "/d/Calia/worshippers/specials/worshipsoul"

#define STONE_TRAINER "/d/Calia/walkers/shrine/stone_trainroom"
#define STONESOUL "/d/Calia/walkers/stone/specials/stonesoul"

