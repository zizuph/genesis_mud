// file name: /d/Avenir/common/dead/dead.h
// creator(s): Ilyian (August 12, 1995)
// last update: Lilith, April 2021  Added paths and defs for the Catacombs
//                area and quests. 
// purpose: File to be included in all /common/dead/ areas
// note:
// bug(s):
// to-do:
#ifndef __DEAD_DEFS__
#define __DEAD_DEFS__

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include <language.h>

// I'm putting herbs around here--moved to dead.c
//#include "/d/Avenir/common/herbs/herbsearch.h"

/* Paths */
#define UMAKER "/d/Avenir/common/dead/u_maker"
#define GET_ONE(x)   ((x) [random(sizeof(x))])
#define MARSH    "/d/Avenir/common/dead/marsh/" 
#define PATH     "/d/Avenir/common/dead/path/"  
#define CRYPT    "/d/Avenir/common/dead/catacombs/"   
#define CAHOR    "/d/Avenir/common/dead/cahor/"
#define MASQ     "/d/Avenir/common/dead/mascarvin/" 
#define HILL     "/d/Avenir/common/dead/hill/" 
#define BARROW   "/d/Avenir/common/dead/barrow/" 

#define MON      "/d/Avenir/common/dead/mon/"   
#define OBJ      "/d/Avenir/common/dead/obj/"  
#define DECK     "/d/Avenir/common/dead/obj/deck/"

#define NAMEQ(x)  (x)->query_name()

/* Log files */
#define GATE_LOG   "/d/Avenir/log/quest/crypt_gate"
#define HEG_LOG   "/d/Avenir/log/quest/hegemon"
#define MASQ_LOG   "/d/Avenir/log/quest/mascarvin"
#define MASQ_GET_LOG "/d/Avenir/log/mascarvin_table_get"
#define SHEE_LOG   "/d/Avenir/log/quest/banshee"
#define QUEST_FILE "/d/Avenir/log/quest/cahor"

/* Properties */
#define WIND_PROP      "_av_wind_watch"
#define ABDM           "_Avenir_banshee_dropped_me"
#define DMASK_PROP     "_Avenir_death_mask_wearer"
#define HEG_TOP_PROP   "_Avenir_Heg_Scepter1"
#define HEG_WAND_PROP  "_Avenir_Heg_Scepter2"

/* Quest related defines */
// Catacomb Gate quest
#define GATE_QUEST   "Catacomb Gate"
#define Q_GROUP      0
#define GATE_BIT     1
#define GATE_EXP     3500 
#define CHECK_QUEST_GATE(x) \
        (x)->test_bit("Avenir", Q_GROUP, GATE_BIT)

// Bring specific death mask to Banshee:
#define MASK_QUEST  "Banshee Mask"
#define SHEE_GROUP  0
#define SHEE_BIT    11
#define SHEE_EXP    7000  
#define CHECK_QUEST_MASK(x) \
        (x)->test_bit("Avenir", SHEE_GROUP, SHEE_BIT)
		
// Hegemon's Ghost quest:
#define HEG_QUEST   "Hegemon's Ghost"
#define HEG_GROUP   1
#define HEG_BIT     1
#define HEG_EXP     3400
#define CHECK_QUEST_HEG(x) \
        (x)->test_bit("Avenir", HEG_GROUP, HEG_BIT)

// Solve the puzzles, meet Mascarvin, get your just reward:
#define MASQ_QUEST   "Meet Mascarvin"
#define MASQ_GROUP   1
#define MASQ_BIT     9
#define MASQ_EXP     20000 
#define MASQ_EXP_ALT  3500 
#define CHECK_QUEST_MASQ(x) \
        (x)->test_bit("Avenir", MASQ_GROUP, MASQ_BIT)

// Tracks the Meet Mascarvin quest progress so
// players don't have to re-do each stage if
// they can't complete it all in one go
#define SS_MASQ_STAGE  139002
#define STAGE_1_HEG    1
#define STAGE_2_DOTS   2
#define STAGE_3_MAZE   3
#define STAGE_4_SKULLS 4
#define STAGE_5_MEET   5
#define STAGE_6_THIEF  6


/* Shortcuts to minimize keystrokes */
#define PROP(x)  this_player()->query_prop(x)
#define APROP(x) this_player()->add_prop(x , 1)
#define RPROP(x) this_player()->remove_prop(x)
#define UND(x)   x->query_prop("_live_i_undead")
#define ALIGN(x) x->query_alignment()

/* How many of each undead type do we want to
 * be wandering around the marsh at one time? 
 * Used by: /common/dead/u_maker.c
 */
#define WRAITHS  10
#define WIGHTS   7
#define GHOULS   15
#define SPIRITS  10
#define APPARITIONS 15
#define GHOSTS   7

#define LANG(x)  x->query_skill(SS_LANGUAGE)

#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))


#endif __DEAD_DEFS__