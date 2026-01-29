// file name:        /d/Avenir/common/bazaar/admin/admin.h
// creator(s):       Lilith, Oct '96
// revisions: 
// purpose:          Put defines and includes here that are needed
//                   in all the area files         
// note:             
// bug(s):           
// to-do:            

#include "/d/Avenir/include/defs.h"      /* Short-hand macros */
#include "/d/Avenir/include/paths.h"     /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"    /* ADD_SKIN, etc */
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* self-explanatory */
#include <math.h>                        /* NAME_TO_RANDOM */

/* Area defines and connections */
#define BAZ_ADMIN  BAZAAR + "admin/"
#define BAZ_OBJ    BAZAAR + "Obj/"
#define BAZ_MON    BAZAAR + "NPCS/"

/* Quest defines */

#define QNUM(x)      (NAME_TO_RANDOM((x)->query_name(), 503, 4) + 1)
#define K_ERR_LOG   "/d/Avenir/log/quest/kestares_quests"
#define KESTARES_GROUP  1
#define DEFILE       3
#define REPAIR       4
#define THIEF        5
#define SLAVE        6

#define D_EXP       1500
#define R_EXP       1500 
#define T_EXP       1500  
#define S_EXP       1500  

#define DEFILE_QUESTOR   "_Avenir_defile_quest"
#define REPAIR_QUESTOR   "_Avenir_repair_quest"
#define THIEF_QUESTOR    "_Avenir_thief_quest"
#define SLAVE_QUESTOR    "_Avenir_slave_quest"
#define QUEST_FILE	 "/d/Avenir/log/quest/admin_quests"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#undef QUEST_DEBUG

#ifdef  QUEST_DEBUG
#define QDB(x) find_player("lilith")->catch_msg("Admin Quest: "+x+"\n")
#else
#define QDB(x) ;
#endif

