/*
 * This file defines bit groups and quest bits for Gondor
 */

#ifndef GONDOR_BITS
#define GONDOR_BITS

#define TOUR_GROUP                        0

#define TOUR_FIRST_BIT                    0
#define TOUR_LAST_BIT                     4
#define TOUR_NO_OF_BITS                   5

#define GILRAEN_WOLFCAVE_BIT              5 /* Hunthor */
#define GILRAEN_WOLFCAVE_QUEST_EXP     2500

#define HARAD_BANNER_BIT                  6 /* Hunthor */
#define HARAD_BANNER_EXP               3000

#define THORNLIN_OX_GROUP                 0 /* Hunthor */
#define THORNLIN_OX_BIT                   7
#define THORNLIN_OX_EXP                1000

#define PELARGIR_STATUE_GROUP             0 /* Hunthor */
#define PELARGIR_STATUE_BIT               8
#define PELARGIR_STATUE_EXP            1000

#define ENTWASH_LARVAE_GROUP              0
#define ENTWASH_LARVAE_BIT                9
#define ENTWASH_LARVAE_EXP             1000

#define DWARVEN_RACE_GUILD_CHESS_GROUP    0
#define DWARVEN_RACE_GUILD_CHESS_BIT     10
#define DWARVEN_RACE_GUILD_CHESS_EXP   3000

#define VENGEFUL_WIGHT_BIT               11
#define VENGEFUL_WIGHT_EXP             5000

#define MTIRITH_MURDER_GROUP              0 /* Hunthor */
#define MTIRITH_MURDER_BIT               12
#define MTIRITH_MURDER_EXP            15000

#define PELARGIR_LIGHTHOUSE_GROUP         0
#define PELARGIR_LIGHTHOUSE_BIT          13
#define PELARGIR_LIGHTHOUSE_EXP        3000

#define RIVERSTEAD_TOUR_GROUP             0
#define RIVERSTEAD_TOUR_BIT               14
#define RIVERSTEAD_TOUR_EXP               100

#define PELARGIR_REPAIR_DOCK_GROUP        0
#define PELARGIR_REPAIR_DOCK_BIT         15
#define PELARGIR_REPAIR_DOCK_EXP       1200

#define GRIMA_LETTER_BIT                 16
#define GRIMA_LETTER_EXP               1000

// Pelargir tours
#define PEL_TOUR_FIRST_GROUP              0 /* Hunthor */
#define PEL_TOUR_FIRST_BIT               17
#define PEL_TOUR_LAST_BIT                19
#define PEL_TOUR_NO_OF_BITS               3

#define GONDOR_GROUP                      1

#define HERB_SMUGGLER_BIT                 0
#define HERB_SMUGGLER_EXP              3000

#define RANGER_TEST_BIT                   1 
#define RANGER_TEST_EXP                 100

#define ENCHANT_SEED_BIT                  2
#define ENCHANT_SEED_EXP                700

#define LOST_RANGER_BIT                   3
#define LOST_RANGER_EXP                3000

#define EDORAS_RING_BIT                   4
#define EDORAS_RING_EXP                2000

#define ELFHELM_URUK_BIT                  5
#define ELFHELM_URUK_EXP               4000

#define RABBIT_STEW_BIT                   6
#define RABBIT_STEW_EXP               27500

#define EAGLES_EGG_BIT                    7
#define EAGLES_EGG_EXP                12500

#define WOSE_SHAMAN_BIT                   8
#define WOSE_SHAMAN_EXP                1000

#define SPYING_ORC_BIT                   11
#define SPYING_ORC_EXP                 2001

#define SIRITH_PIG_GROUP                  1
#define SIRITH_PIG_BIT                   12
#define SIRITH_PIG_EXP                 1000

#define PAINT_GROUP			              1
#define PAINT_BIT			             13
#define PAINT_REWARD			       5000

#define CANDROS_GROUP                     1
#define CANDROS_MARIDAN_BIT              14
#define CANDROS_MARIDAN_EXP             300

#define RANGER_GROUP			  1
#define RANGER_GUILD_BIT                 16
#define RANGER_BIT                       18
#define RANGER_CAPTAIN_BIT               19

/*
 * Arman tells you: so the check will be:
 * if(TP->test_bit("gondor", MORGUL_GURU_GROUP, MORGUL_GURU_BIT))  
 *
 * This is for future MM guru quest
 * (Group 2, Bit 1)
 * Finwe, Jan 2019
 */

#define MORGUL_GROUP                      2
#define MORGUL_MAGE_BIT                   0
#define MORGUL_MAGE_Q                     1
#define MORGUL_MAGE_Q1                    1
#define MORGUL_MAGE_Q2                    2
#define MORGUL_MAGE_Q3                    3
#define MORGUL_MAGE_Q4                    4

#define MORGUL_ENTRY_BIT                  5
#define MORGUL_ENTRY_QUEST_EXP        25000

#define ANGMAR_STANDARD_BIT               6 /* Warden-MM */
#define ANGMAR_STANDARD_QUEST_EXP     15000

#define AMON_DIN_FIREWOOD_GROUP           2 /* Warden-MM */
#define AMON_DIN_FIREWOOD_BIT             7
#define AMON_DIN_FIREWOOD_EXP         12000

#define POROS_CORSAIRS_BIT                8
#define POROS_CORSAIRS_EXP             1000

#define ISEN_ENTRY_GROUP                  2
#define ISEN_ENTRY_BIT                    9
#define ISEN_ENTRY_EXP                    1 /* XXX until decided */

#define HARONDOR_CHIEF_GROUP              2
#define HARONDOR_CHIEF_Q1                10
#define HARONDOR_CHIEF_EXP               1200


#define IMRAHIL_GROUP                     3
#define IMRAHIL_PORRIDGE_BIT              0
#define IMRAHIL_PORRIDGE_EXP           2000

#define MTIRITH_PORTER_GROUP              3 /* MT */
#define MTIRITH_PORTER_BIT                5
#define MTIRITH_PORTER_EXP             3500

#define MTIRITH_OAT_BIT                   6 /* MT */
#define MTIRITH_OAT_EXP               10000

#define MTIRITH_DENETHOR_BIT              7 /* MT */
#define MTIRITH_DENETHOR_EXP          18000

#define IGARD_GROUP                       3
#define IGARD_COURIER_BIT                 8
#define IGARD_COURIER_EXP             15000

#define IGARD_EVIDENCE_BIT                9
#define IGARD_EVIDENCE_EXP             2000

#define MEARAS_HEAD_GROUP                 3
#define MEARAS_HEAD_BIT                  10
#define MEARAS_HEAD_EXP                1000

#define JAINE_QUEST_GROUP                 3
#define JAINE_QUEST_BIT                  11
#define JAINE_QUEST_EXP                8000

/* no definitions beyond this line */
#endif GONDOR_BITS
