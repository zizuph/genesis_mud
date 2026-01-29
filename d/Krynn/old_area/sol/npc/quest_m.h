/* A file containing global definitions for the quests 

   Made by Nick
*/

#define TOURISTING 	0 /* quest level 0 */
#define SMALLADV 	1 /* quest level 1 & 2 */
#define MAJADV 		2 /* quest 3 */
#define QUEST 		3
	/* quest 4 & 5, perhaps if we make a 5 it should be out */

    /* The adventure types. */
#define ATYPES 		({ "touristing", "small adventure", \
			   "major adventure", "quest" })

    /* The short adventure types. */
#define SH_ATYPES 	({ "tour", "small", "major", "quest" })

#define NUM_OF_TYPES 	sizeof(ATYPES)
#define QUEST_DIR 	"/d/Krynn/common/quests/"
#define QUEST_FILE(type, num) QUEST_DIR + SH_ATYPES[type] + num + ".c"
#define QUEST_MASTER 	"/d/Krynn/solace/new_village/npc/quest_master"
#define QUEST_LOG 	"/d/Krynn/common/log/quests/"
#define DO_LOG_QUESTS	1

    /* The bit definitions */
    /*                TOUR   SMALL    MAJOR  */
#define NUM_OF_BIT ({   6,     7,       7 })
#define GROUP      ({   0,     0,       0 })
#define E_BIT      ({   5,    12,      19 })
    /* Thus Tour bits are from 0 - 5, small 6 - 12 and major 13 - 19 */
    /* That gives us 63 levels of touristing, 127 of small adventures */
    /* and 127 of major adventures. And we only use up 20 bits !!!! */
    /* The only requirement is that the players have to solve the quests */
    /* in the demanded order, but that maybe isn't so bad. */


#define PLAYER_I_HELP_SALAMIC  "_player_i_help_salamic"
    /* The prop in the player that determines the amount of exp */
    /* to give for the salamic quest on rewarding. */
#define PLAYER_I_BRIMSCH_LIFE_QUEST "_player_i_brimsch_life_quest"
    /* The prop in the player that determines the amount of exp */
    /* to give for the brimsch life quest on rewarding. */
