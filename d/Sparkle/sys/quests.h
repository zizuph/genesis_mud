/*******************************************************************\
| QUESTS.H                                                          |
\*******************************************************************/

// DO NOT FORGET TO KEEP BITS IN OPEN DIR IN SYNC WITH THIS FILE !

#define S_QUEST_DOMAIN          "Sparkle"
#define S_QUEST_DOMAIN_OLD      "Genesis"

// The quest macros should be the only macros used to access quest bits !
//
// QUEST_TEST tells whether a quest bit is set
// QUEST_SET sets a quest bit
// QUEST_LOG logs a quest message
//
// All macros have counterparts ending in TP that act on this player.
//
// The idea is to have all quests identified by a pair of numbers
// telling the group and the bit. The pair would be defined here,
// the code would therefore look like:
//
// if (QUEST_TEST (Q_ORC_FIGURINE)) write ("You have done this before !\n");
// QUEST_SET (Q_ORC_FIGURINE);
// QUEST_LOG (TP, "finished the orc figurine quest.");

#define QUEST_TEST(who,que)     ( (who)->test_bit (S_QUEST_DOMAIN, que) )
#define QUEST_SET(who,que)      { (who)->set_bit (que); }
#define QUEST_LOG(who,msg)      { s_log (S_LOG_QUEST_FILE, s_get_Name (who) + " " + msg + "\n"); }

#define QUEST_TEST_TP(que)      QUEST_TEST (TP, que)
#define QUEST_SET_TP(que)       QUEST_SET (TP, que)
#define QUEST_LOG_TP(msg)       QUEST_LOG (TP, msg)

// For quests ported over from the Genesis domain, there is also the
// QUEST_PORT macro, which sets the Sparkle domain bit if the Genesis
// domain bit is set. This macro should be used for all quests ported
// over from the Genesis domain.

#define QUEST_PORT(who,old,new,msg)     {                                                       \
                                          if ((who)->test_bit (S_QUEST_DOMAIN_OLD, old))        \
                                          {                                                     \
                                            QUEST_SET (who, new);                               \
                                            QUEST_LOG (who, msg);                               \
                                          }                                                     \
                                        }

#define QUEST_PORT_TP(old,new,msg)      QUEST_PORT (TP, old, new, msg)

// Definitions for Genesis domain quest bits

#define Q_OLD_ORC_FIGURINE      0,0
#define Q_OLD_SACRIFICE_DUCK    0,1
#define Q_OLD_MONK_GURU         1,5
#define Q_OLD_DWARFHEIM_KING    2,0

// Definitions for Sparkle domain quest bits

#define Q_ORC_FIGURINE          0,0
#define Q_SACRIFICE_DUCK        0,1
#define Q_DWARFHEIM_KING        2,0
#define Q_MONK_GURU             3,0
#define Q_MONK_ACROBAT_GURU     3,1

// Definitions for Sparkle City quest bits

#define CITY_TOUR_SIGN_GROUP    2
#define CITY_TOUR_SIGN_BIT      5
#define CITY_TOUR_SIGN_EXP      300

#define CITY_TOUR_DOCK_GROUP    2
#define CITY_TOUR_DOCK_BIT      6
#define CITY_TOUR_DOCK_EXP      300

#define CITY_TOUR_FOOD_GROUP    2
#define CITY_TOUR_FOOD_BIT      7
#define CITY_TOUR_FOOD_EXP      100

#define CITY_TOUR_DRINK_GROUP   2
#define CITY_TOUR_DRINK_BIT     8
#define CITY_TOUR_DRINK_EXP     100

#define CITY_TOUR_ORBS_GROUP    2
#define CITY_TOUR_ORBS_BIT      9
#define CITY_TOUR_ORBS_EXP      300

#define CITY_TOUR_GUILD_GROUP   2
#define CITY_TOUR_GUILD_BIT     10
#define CITY_TOUR_GUILD_EXP     400

#define CITY_TOUR_LOCALQM_GROUP 2
#define CITY_TOUR_LOCALQM_BIT   11
#define CITY_TOUR_LOCALQM_EXP   1000

#define CITY_TOUR_FARQM_GROUP   2
#define CITY_TOUR_FARQM_BIT     12
#define CITY_TOUR_FARQM_EXP     2000

#define WRESTLE_BETS_Q1_GROUP   2
#define WRESTLE_BETS_Q1_BIT     13
#define WRESTLE_BETS_Q1_EXP     200

#define WRESTLE_BETS_Q2_GROUP   2
#define WRESTLE_BETS_Q2_BIT     14
#define WRESTLE_BETS_Q2_EXP     2000

#define ARM_WRESTLE_CHAMP_GROUP 2
#define ARM_WRESTLE_CHAMP_BIT   15
#define ARM_WRESTLE_CHAMP_EXP   25000

#define ARM_WRESTLE_Q1_GROUP    2
#define ARM_WRESTLE_Q1_BIT      16
#define ARM_WRESTLE_Q1_EXP      200

#define ARM_WRESTLE_Q2_GROUP    2
#define ARM_WRESTLE_Q2_BIT      17
#define ARM_WRESTLE_Q2_EXP      1000

#define ARM_WRESTLE_Q3_GROUP    2
#define ARM_WRESTLE_Q3_BIT      18
#define ARM_WRESTLE_Q3_EXP      2000

#define ARM_WRESTLE_Q4_GROUP    2
#define ARM_WRESTLE_Q4_BIT      19
#define ARM_WRESTLE_Q4_EXP      10000




/* Special info about the SPARKLE_VENDOR and SPARKLE_HERB quests:
 *   Though the listed exp for this quest is only 200, it actually is able
 *   give out to the player a total of 50,000. The idea is that this quest
 *   is repeatable, once per week. Therefore, a player is allowed to do
 *   it 250 times (200 * 250 = 50,000.) Doing this once per week will take
 *   a player who never misses an opportunity around five years. Once the
 *   player has completed it for the 250th time, the quest bit is finally
 *   set, and the player from then on gets a reward other than quest exp
 *   for completing the quest. Please refer any questions to Gorboth.
 */
#define SPARKLE_VENDOR_GROUP    4
#define SPARKLE_VENDOR_BIT      7
#define SPARKLE_VENDOR_EXP      200

#define SPARKLE_AUCTION_GROUP   4
#define SPARKLE_AUCTION_BIT     8
#define SPARKLE_AUCTION_EXP     1500

#define LIBRARY_SIGN_GROUP      4
#define LIBRARY_SIGN_BIT        9
#define LIBRARY_SIGN_EXP        1500

#define LIBRARY_RESTORE_GROUP   4
#define LIBRARY_RESTORE_BIT     10
#define LIBRARY_RESTORE_EXP     3000

#define SPARKLE_FINEST_GROUP    4
#define SPARKLE_FINEST_BIT      11
#define SPARKLE_FINEST_EXP      750

#define MERC_SPY_GROUP          4
#define MERC_SPY_BIT            12
#define MERC_SPY_EXP            2000

#define DAILY_APOTHECARY_GROUP  4
#define DAILY_APOTHECARY_BIT    13
#define DAILY_APOTHECARY_EXP    30

#define ORCTEMPLE_WEAPON_GROUP  4
#define ORCTEMPLE_WEAPON_BIT    14
#define ORCTEMPLE_WEAPON_EXP    1000

#define ORCTEMPLE_JOURNAL_GROUP 4
#define ORCTEMPLE_JOURNAL_BIT   15
#define ORCTEMPLE_JOURNAL_EXP   1500

#define ORCTEMPLE_FLUTE_GROUP   4
#define ORCTEMPLE_FLUTE_BIT     16
#define ORCTEMPLE_FLUTE_EXP     1500

#define ORCTEMPLE_GHOST_GROUP   4
#define ORCTEMPLE_GHOST_BIT     17
#define ORCTEMPLE_GHOST_EXP     5000

#define ORCTEMPLE_DEMON_GROUP   4
#define ORCTEMPLE_DEMON_BIT     18
#define ORCTEMPLE_DEMON_EXP     5000

#define SPARKLE_HERB_GROUP      4
#define SPARKLE_HERB_BIT        19
#define SPARKLE_HERB_EXP        200


// Definitions for tutorial are not compliant with the rest yet

#define TUTORIAL_POTION_GROUP   4
#define TUTORIAL_POTION_BIT     0
#define TUTORIAL_POTION_EXP     100

#define TUTORIAL_CARROT_GROUP   4
#define TUTORIAL_CARROT_BIT     1
#define TUTORIAL_CARROT_EXP     100

#define TUTORIAL_BUNNY_GROUP    4
#define TUTORIAL_BUNNY_BIT      2
#define TUTORIAL_BUNNY_EXP      400

#define TUTORIAL_GARLIC_GROUP   4
#define TUTORIAL_GARLIC_BIT     3
#define TUTORIAL_GARLIC_EXP     500

#define TUTORIAL_ROPE_GROUP     4
#define TUTORIAL_ROPE_BIT       4
#define TUTORIAL_ROPE_EXP       1000

#define TUTORIAL_JOURNAL_GROUP  4
#define TUTORIAL_JOURNAL_BIT    5
#define TUTORIAL_JOURNAL_EXP    1000

#define TUTORIAL_KROLOCK_GROUP  4
#define TUTORIAL_KROLOCK_BIT    6
#define TUTORIAL_KROLOCK_EXP    5000


// Definitions for Sparkle area quests

#define GOBLIN_ARMOURER_GROUP   1
#define GOBLIN_ARMOURER_BIT     5
#define GOBLIN_ARMOURER_EXP     500

#define GOBLIN_LOVE_GROUP       1
#define GOBLIN_LOVE_BIT         6
#define GOBLIN_LOVE_EXP         5000

#define GOBLIN_DARTS_GROUP      1
#define GOBLIN_DARTS_BIT1       7
#define GOBLIN_DARTS_BIT2       8
#define GOBLIN_DARTS_EXP1       500
#define GOBLIN_DARTS_EXP2       1000

#define LIBRARY_QUAKE_GROUP     1
#define LIBRARY_QUAKE_BIT       9
#define LIBRARY_QUAKE_EXP       25000

#define SPARKLE_PUB_GROUP       1
#define SPARKLE_PUB_BIT         10
#define SPARKLE_PUB_EXP         1000
