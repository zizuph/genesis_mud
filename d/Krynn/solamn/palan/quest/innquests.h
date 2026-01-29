/* created by Aridor 08/31/93 */

/* this is the master file for the Palanthas Quests */



#define QUEST_KEEPER_ROOM     "/d/Krynn/solamn/palan/city/inn2"
#define BAR_KEEPER_ROOM       "/d/Krynn/solamn/palan/city/inn1"

#define PLAYER_I_ON_INN_QUEST "_player_i_on_inn_quest"
#define NUM_OF_QUESTS    3

#define QUEST_LOG        "/d/Krynn/common/log/quests/inn"
#define DO_LOG_QUESTS    1

/* Very careful with these Bits!                        *
 * This means that bits 7 and 8 are used, but numbers   *
 * are stored reversed!! This means there is the possibility *
 * to do 3 quests max, but it is also possible to add another *
 * bit (Bit 9), so 7 quests could be stored altogether. */
#define GROUP            2
#define FIRST_BIT        7
#define NUM_OF_BITS      2
