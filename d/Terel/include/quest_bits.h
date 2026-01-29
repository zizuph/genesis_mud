/*
 * Definitions for quest xp quest bits
 */


/* Quest-definitions:
 * QUEST_xxx_GROUP : group for quest bit (0..4)
 * QUEST_xxx_BIT : bit number
 * QUEST_xxx_EXP : exp points given for this quest
 */

/*
 * Available:
 * 1:17-1:19,
 * 2:1->
 *
 */

#ifndef _terel_quest_only_
#define _terel_quest_only_

#define QUEST_LOG        "/d/Terel/log/quests"

/* ZODIAC RELATED QUESTS */

/* fire-quest in caves */
#define QUEST_FIRE_GROUP      0
#define QUEST_FIRE_BIT        0
#define QUEST_FIRE_EXP        2000
/* balance-quest (riddle) */
#define QUEST_BAL_GROUP       0
#define QUEST_BAL_BIT         1
#define QUEST_BAL_EXP         2000
/* red-death-quest (dangerous) */
#define QUEST_DEATH_GROUP     0
#define QUEST_DEATH_BIT       2
#define QUEST_DEATH_EXP       4000
/* maze-quest (colored rooms) */
#define QUEST_MAZE_GROUP      0
#define QUEST_MAZE_BIT        3
#define QUEST_MAZE_EXP        4000
/* Porcia-quest (also yellow hint for door quest) */
#define QUEST_POR_GROUP       0
#define QUEST_POR_BIT         13
#define QUEST_POR_EXP         3000
/* big zodiac quest */
#define QUEST_ZOD_GROUP       0
#define QUEST_ZOD_BIT         17
#define QUEST_ZOD_EXP         70000
/* chisel quest in mines */
#define QUEST_CHI_GROUP       0
#define QUEST_CHI_BIT         18
#define QUEST_CHI_EXP         5000

/* The quests _G1_ to _G7_ are handled by the fortune teller in
 * the GYPSY CAMP
 */
/* The hat quest */
#define QUEST_G1_GROUP  0
#define QUEST_G1_BIT    5
#define QUEST_G1_EXP    100
/* The beard quest */
#define QUEST_G2_GROUP  0
#define QUEST_G2_BIT    6
#define QUEST_G2_EXP    500
/* The belt quest */
#define QUEST_G3_GROUP  0
#define QUEST_G3_BIT    7
#define QUEST_G3_EXP    1000
/* The juggle quest */
#define QUEST_G4_GROUP  0
#define QUEST_G4_BIT    8
#define QUEST_G4_EXP    1000
/* The tight-rope quest */
#define QUEST_G5_GROUP  0
#define QUEST_G5_BIT    9
#define QUEST_G5_EXP    2000
/* The magic quest */
#define QUEST_G6_GROUP  0
#define QUEST_G6_BIT    10
#define QUEST_G6_EXP    16500
/* The spooky quest */
#define QUEST_G7_GROUP  0
#define QUEST_G7_BIT    11
#define QUEST_G7_EXP    10000

/* MANSION QUESTS */

/* The Sacrifice Quest, by Vader */
#define QUEST_SAC_GROUP  0
#define QUEST_SAC_BIT    12
#define QUEST_SAC_EXP    10000
/* Thane quest part 1: find sword, tear tapestry       Cedric */
#define QUEST_TH1_GROUP  0
#define QUEST_TH1_BIT    14
#define QUEST_TH1_EXP    5000

/* Thane quest part 2: kill the Dark One          Cedric */
#define QUEST_TH2_GROUP  0
#define QUEST_TH2_BIT    15
#define QUEST_TH2_EXP    5000
/* witch quest, by Janus and Mortricia */
#define QUEST_WIT_GROUP  0
#define QUEST_WIT_BIT    19
#define QUEST_WIT_EXP    15000

/* ENCHANTED GARDEN */

/* Bring the cat back quest by Janus */
#define QUEST_JJ1_GROUP 1
#define QUEST_JJ1_BIT   0
#define QUEST_JJ1_EXP   1600
/* Bracelet quest, by Janus */
#define QUEST_JJ2_GROUP 1
#define QUEST_JJ2_BIT   1
#define QUEST_JJ2_EXP   10000
/* Kill the bug queen quest, by Janus */
#define QUEST_JJ3_GROUP 1
#define QUEST_JJ3_BIT   2
#define QUEST_JJ3_EXP   20000

/* RIBOS */

/* Kill the evil dragon in Ribos, by Vader */
#define QUEST_RIB_GROUP        1
#define QUEST_RIB_BIT          3
#define QUEST_RIB_EXP          40000
/* Solve Crime in Ribos quest */
#define QUEST_CRIME_GROUP      1
#define QUEST_CRIME_BIT        11 
#define QUEST_CRIME_EXP        4000

/* OTHERS */

/* Child Quest (bring Jeffrey home) */
#define QUEST_CHILD_GROUP     0
#define QUEST_CHILD_BIT       4
#define QUEST_CHILD_EXP       1000
/* The vote_room puzzle quest, by Sorgum */
#define QUEST_SS1_GROUP       1
#define QUEST_SS1_BIT         6
#define QUEST_SS1_EXP         9000
/* The missing sandal quest by Sorgum */
#define QUEST_SS2_GROUP       1
#define QUEST_SS2_BIT         7
#define QUEST_SS2_EXP         5000
/* Mystic Order Quest,  by Mecien  */
#define QUEST_MOQ_GROUP       0
#define QUEST_MOQ_BIT         16
#define QUEST_MOQ_EXP         8000
/* The Musicians torment part1 quest, by Janus */
#define QUEST_JJ4_GROUP       1
#define QUEST_JJ4_BIT         8
#define QUEST_JJ4_EXP         300
/* Get the batshit to the witch quest, by Janus */
#define QUEST_JJ5_GROUP       1
#define QUEST_JJ5_BIT         9
#define QUEST_JJ5_EXP         1500
/* Gardener missing gloves quest, by Tomas */
#define QUEST_GMG_GROUP       1
#define QUEST_GMG_BIT         12
#define QUEST_GMG_EXP         750
/*Bandit treasure quest*/
#define QUEST_CRYPT_GROUP     1
#define QUEST_CRYPT_BIT       13
#define QUEST_CRYPT_REWARD    20000
/*Caravan protection/attack quest*/
#define QUEST_CARAV_GROUP     1
#define QUEST_CARAV_BIT       14
#define QUEST_CARAV_REWARD    20000
/* Hunt Assassin Quest */
#define QUEST_HAQ_GROUP       1
#define QUEST_HAQ_BIT         15
#define QUEST_HAQ_EXP         10000
/* Merchant Quest, Ghastly Keep */
#define TEREL_GHASTLY_KEEP_GROUP 1
#define TEREL_GHASTLY_KEEP_BIT   16
#define TEREL_GHASTLY_KEEP_EXP   3000
/* Moor Cottage Chest Quest */
#define COTTAGE_CHEST_GROUP   1
#define COTTAGE_CHEST_BIT     17
#define COTTAGE_CHEST_EXP     500

/* Calathin  */
#define QUEST_CAL_GROUP  2
#define QUEST_ENE_BIT    0


/* NOT DONE */

/* Slingshot the Crow */
#define QUEST_GG1_GROUP 1
#define QUEST_GG1_BIT 10
#define QUEST_GG1_EXP 500
/* Shinto's eremite daughter quest */
#define QUEST_EDQ_GROUP 1
#define QUEST_EDQ_BIT 12
#define QUEST_EDQ_EXP 12000

#endif
