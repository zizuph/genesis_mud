#include "/d/Roke/common/defs.h"

#ifndef ROKE_QBITS
#define ROKE_QBITS

/* object handling nifty logging of quests */

#define LOGGER "/d/Roke/common/questlogger"

/* #define XXX_QUEST 0(Change nr for each quest) */
/* Example */
/* #define A_QUEST 0 */
/* #define B_QUEST 1 */
/* #define C_QUEST 2 */

/* use LOG_QUESTS!=0 to log quests */

#define LOG_QUESTS 1
#define QUESTLOG "/d/Roke/log/quest.log"

#define QDONE(group,apa) (this_player()->test_bit("Roke", group, apa))
#define QSET(group,bepa)  this_player()->set_bit(group,bepa)
/* #define QLOG(cepa) if(LOG_QUESTS) write_file(QUESTLOG, extract(ctime(time()), \
		  4,15)+" "+cepa+" "+capitalize(TP->query_real_name()) + "\n")
*/

#define QLOG(cepa) if(LOG_QUESTS) (LOGGER)->log_quest(cepa)

/* Then we can do: if(QDONE(XXX_QUEST)) then .... */
/* Lord Ged  */

/*I was lazy when i put groups into this file */
#define GROUP0 0 
#define STATUEQUEST 0
#define SCROLLQUEST 1

#define ROKEGROUP 0
#define WIZARDQUEST 2
#define DRAGONQUEST 3
#define GUILDMEMBER 4

#define MAYORGROUP 0
#define MAYORBIT1   5
#define MAYORBIT2   6
#define MAYORBIT3   7
#define MAYORBIT4   8

/* the above group of bits (5-8) is used as a four-bit binary word */

#define OGIONMAZE   9
#define DROWNGIRL  10
#define SPIRITQUEST 11
#define KAHEDA_GROUP 0
#define KAHEDA_MEMBER 12
#define KAHEDA_OCCUP 13

#define SKELETON 14
#define BEGGARQUEST 15
#define PAPERQUEST 16
#define EYEQUEST 17
#define KITTENQUEST 18

#define TRAV_GROUP 0
#define TRAV_MEMBER 19

#define GROUP1 1
#define BLUEDRAGON 0
#define GURUQUEST  1
#define AXE_QUEST 2
#define WOLFQUEST 3
#define JABBERWOCK 4

#define GROUP2 2
#define ANTONSHIT1 1  /* yes, I'm really pissed off!!! /gres */
#define ANTONSHIT2 2

#define GLAD_GROUP 2
#define GLAD_TRAIN_GURU 17
#define GLAD_MEMBER 18
#define GLAD_TRAIN_MASTER 19

/******************************************************
 some properties used to determine if the player has
 performed what he should
*******************************************************/

#define MQ1PROP "_hylla_pippi_"
#define MQ2PROP "_leta_efter_camp_"
#define MQ3PROP "_hittat_hypert_camp_"
#define MQ4PROP "_g}_till_pippin_igen_"

#define COLDFEET "_jomen_de_e_kallt_"
#define GHOSTKINGSAXE "_roke_ghostkingaxe"
#define GHOSTKINGKILLER "_roke_ghostkingkiller"

#endif





