/* Bits defined for the Domain Shire - Dunstable, April, 1994 */

#ifndef SHIRE_BITS
#define SHIRE_BITS

#define FIRST_GROUP         0
/*
 * Bit 0 is used for Hin Warrior Membership
 * Bit 1 is used for the spelltome quest
 *
 * Bits 2 and 3 are used for the first and second parts of
 * the letter quest, given by /d/Shire/common/hobbiton/
 * quest_hobbit.c
 *
 * Bit 4 is planned for Tricky's White Towers Quest
 * Bit 5 is proposed for some 'Witch Quest'
 * The latter two quests will probably not open, and so we
 * can use these bits at a later time
 */
#define FIX_STILL_BIT       5
#define FIX_STILL_EXP       2500

#define SECOND_GROUP        1
/* This group has Rogon's spellcasting guild reserving
 * bits 0-2....This may changed to be put in the GUILD_GROUP
 * Thus keeping all our guild stuff in one group
 */
#define WESTERN_GROUP       2
#define HAY_QUEST_EXP       250
#define HAY_QUEST_BIT       0
#define LUNCH_QUEST_BIT     1
#define LUNCH_QUEST_EXP     2000
#define BRACELET_BIT        2
#define BRACELET_EXP        10000
#define TROLL_REVENGE_BIT   3
#define TROLL_REVENGE_EXP   20000
#define POND_QUEST_BIT      4
#define POND_QUEST_EXP      1000
#define MILKING_QUEST_BIT   5
#define MILKING_QUEST_EXP   1000
#define HOBBIT_ENTRANCE_BIT 6
#define HOBBIT_ENTRANCE_EXP 1000
#define BUMBLEBERRY_BIT     7
#define BUMBLEBERRY_EXP     19000
#define BOAR_BIT            8
#define BOAR_EXP            500
#define DWARVEN_FRIEND_BIT  9
#define DWARVEN_FRIEND_EXP  100
#define KILL_WOLVES_BIT     10
#define KILL_WOLVES_EXP     1000
/*****************************/
#define EASTERN_GROUP       3
#define BREE_LOCKET_BIT     0
#define BREE_LOCKET_EXP     3500
//Moria quests are all given or hinted at by
//Gloin in the Prancing Pony...
//Moria_exit, west_gate, and then
//The Durin's axe quest.
#define MORIA_EXIT_BIT      1
#define MORIA_EXIT_EXP      5000
#define WEST_GATE_BIT       2
#define WEST_GATE_EXP       1000
/* I had thought these following quests were going into
 * the WESTERN_GROUP, but I neglected to put them there
 * before opening, so they're in the EASTERN_GROUP instead.
 * No matter, really, but there are currently no 3,4,5
 * bits defined. /Dunstable
 */
#define FISHING_BIT         3
#define FISHING_EXP         2000
#define BREE_AID_BIT        4
#define BREE_AID_EXP        0

#define MAPPING_BIT         6
#define MAPPING_EXP         17500
#define FEATHER_BIT         7
#define FEATHER_EXP         7500
#define MAGE_BIT            8
#define MAGE_EXP            3000
// The following bits are for the Quests we saved from Rhovanion
// bits 9-14 are saved for this purpose
// -Igneous
#define CLIMBING_BIT        9
#define CLIMBING_EXP        1500
#define TORCH_BIT           10
#define TORCH_EXP           200
#define PRISONER_TRUST_BIT  11
#define PRISONER_TRUST_EXP  10000
#define PRISONER_FOOD_BIT   12
#define PRISONER_FOOD_EXP   500
#define PRISONER_WEP_BIT    13
#define PRISONER_WEP_EXP    5000
#define PRISONER_FINAL_BIT  14
#define PRISONER_FINAL_EXP  25000

#define WILLOW_BIT          15
#define WILLOW_EXP          1000
/******************************/
#define FOURTH_GROUP        4
/* The Fourth Group is the Guild Group! :) */
/* Also appropriate here are entrance quests to guilds. */
#define GOBLIN_BIT          0
#define HERALD_BIT          1
#define TRICKSTER_BIT       2
#define SMITHS_BIT          3
#define FOGEY_BIT           4
#define EASTERLING_BIT      5
#define HEREN_ISTIMOR_BIT   6
#define EQUESTRIAN_BIT      7
#define SINDAR_RACIAL       8
#define SINDAR_OCC          9
#define MITHLOND_ARCHERS   10
#define HUNTCLUB_BIT       11
#endif
