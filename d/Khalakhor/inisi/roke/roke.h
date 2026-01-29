/* Area specific defines for Roke */
/* They are mainly connected with quests */

#ifndef ROKE_DEF
#define ROKE_DEF

#include <stdproperties.h>

#define DOMAIN "Khalakhor"
#define ROKEDIR "/d/Khalakhor/inisi/roke/"
#define NYREESEDIR ROKEDIR+"nyreese/"
#define CARISCADIR ROKEDIR+"carisca/"
#define WILDDIR    ROKEDIR+"wild/"
#define SHIPDIR    ROKEDIR+"ships/"
#define CAMP       NYREESEDIR+"golbar-camp/"

// These are used by Roke code but are defined in the domain's defs.h
//#define TP           this_player()
//#define TO           this_object()
//#define ENV(x)       environment(x)
//#define NF(xxx)      notify_fail(xxx)

//#define MAL(xxx)  (present(xxx) && (present(xxx)->query_name() != "corpse"))
#define MAL(xxx)  (present(xxx))

#define INSIDE  add_prop(ROOM_I_INSIDE, 1)
#define OUTSIDE add_prop(ROOM_I_INSIDE, 0)
#define DARK    add_prop(ROOM_I_LIGHT, 0)
#define LIGHT   add_prop(ROOM_I_LIGHT, 1)
 
#define BEACH   add_prop(ROOM_I_TYPE, ROOM_BEACH)
#define WATER   add_prop(ROOM_I_TYPE, ROOM_IN_WATER)
 
#define NEVERKNOWN  add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN add_prop(LIVE_I_ALWAYSKNOWN, 1)


/* object handling nifty logging of quests */

#define LOGGER "/d/Roke/common/questlogger"

/* #define XXX_QUEST 0(Change nr for each quest) */
/* Example */
/* #define A_QUEST 0 */
/* #define B_QUEST 1 */
/* #define C_QUEST 2 */

/* use LOG_QUESTS!=0 to log quests */

#define LOG_QUESTS 1
//#define QUESTLOG ROKEDIR+"log/quest.log"

#define QDONE(group,apa) (this_player()->test_bit(DOMAIN, group, apa))
#define QSET(group,bepa)  this_player()->set_bit(group,bepa)
/* #define QLOG(cepa) if(LOG_QUESTS) write_file(QUESTLOG, extract(ctime(time()), \
                  4,15)+" "+cepa+" "+capitalize(TP->query_real_name()) + "\n")
*/

/*
#define QLOG(cepa) if(LOG_QUESTS) (LOGGER)->log_quest(cepa)
#define ADDEXP(player,amount,type) (LOGGER)->add_exp(player,amount,type)
*/
#define QLOGold(name,exp) if (LOG_QUESTS) \
     log_file("roke_quest", TP->query_real_name() + \
              " completed the " + name + " on " + ctime(time()) + \
              " and was awarded " + exp + " xp. Statave: " + \
              TP->query_average_stat() + ".\n", 50000)

#define ROKE_LOG(file,str) ((ROKEDIR + "log/questlogger")->special_log((file),(str)))

#define QLOG(name,exp) ROKE_LOG("questlog", TP->query_real_name() + \
                 " completed the " + name + " on " + ctime(time()) + \
                 " and was awarded " + exp + " xp. Statave: " + \
                 TP->query_average_stat() + ".\n")

/* Then we can do: if(QDONE(XXX_QUEST)) then .... */
/* Lord Ged  */

/* bits cleared to move into Khalakhor */
#define ROKEGROUP     3

#define STATUEQUEST   0
#define SCROLLQUEST   1
#define SKELETON      2
#define BEGGARQUEST   3
#define PAPERQUEST    4
/* The mayor bits (5-8) are used as a four-bit binary word */
#define MAYORGROUP    ROKEGROUP
#define MAYORBIT1     5
#define MAYORBIT2     6
#define MAYORBIT3     7
#define MAYORBIT4     8
#define OGIONMAZE     9
#define DROWNGIRL     10
#define SPIRITQUEST   11
#define POTIONQUEST   12
#define PAINTQUEST    13
#define BLUEDRAGON    14
#define JABBERWOCK    15
#define OGIONTRUENAME 16

/* exp for quests */
#define DROWNGIRLXP     500
#define STATUEQUESTXP   100
#define SCROLLQUESTXP   300
#define SPIRITQUESTXP   300
#define OGIONMAZEXP     2000
#define SKELETONXP      3000
#define BEGGARQUESTXP   150
#define PAPERQUESTXP    7000
#define POTIONQUESTXP   750
#define PAINTQUESTXP    50
#define BLUEDRAGONXP    2000
#define JABBERWOCKXP    10000
#define OGIONTRUENAMEXP 18000
/* Obsolete bits */
#if 0

/* Roke wizardschool */
#define WIZARDQUEST 2
#define DRAGONQUEST 3
#define GUILDMEMBER 4

/* Atuan */
#define EYEQUEST 17
#define KITTENQUEST 18
#define WOLFQUEST 3

/* Kaheda */
#define GURUQUEST  1

/* Thwil */
#define SHEEPQUEST 7
#define SHARKQUEST 8

/* Unknown */
#define AXE_QUEST 2
#define GROUP2 2
#define ANTONSHIT1 1  /* yes, I'm really pissed off!!! /gres */
#define ANTONSHIT2 2

#endif

/******************************************************
 some properties used to determine if the player has
 performed what he should
*******************************************************/

#define MQ1PROP "_hail_birdie_"
#define MQ2PROP "_look_for_camp_"
#define MQ3PROP "_found_nifty_camp_"
#define MQ4PROP "_go_to_birdie_again_"

#define COLDFEET "_oh_but_it_is_cold_"

#define ROOM_I_NO_DIG   "_room_i_no_dig"
#define ROOM_I_DIG_FUN  "_room_i_dig_fun"

#define HOLEFILE (ROKEDIR + "obj/hole")

#define CADU_DOORS (ROKEDIR + "obj/doors/")
#define REFNAS_DOOR_IN  (CADU_DOORS + "refnas-door-in")
#define REFNAS_DOOR_OUT (CADU_DOORS + "refnas-door-out")
#define REFNAS_KEY_ID 18041975
#define REFNAS_KEY (ROKEDIR + "obj/refnas-key")

#define CADU_DATA  (ROKEDIR + "obj/data/")

#define WOUNDS (ROKEDIR + "obj/wounds")

#endif
