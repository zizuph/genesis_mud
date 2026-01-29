// file name:		~Avenir/common/dark/l3/l3_defs.h
// creator(s):		Denis
// revision history:
//			Jan 96: Cleaned up A Lot Of Junk(TM)
//				Added couple of things for quest reset-ability.
//				-=Denis
// purpose:		Level 3 definitions and Impquest definitions.
// note:		FOR INFO ON IPQUEST SEE FILE ~Avenir/QUESTS/ipquest.doc
// bug(s):
// to-do:

#define ACLO_ALTAR   OBJ + "spider_altar"
 
/*-----[ Property in the room which inherits l3_room.c            ]---*/
/*-----[ indicating how many imps (statues at first) will be here ]---*/
# define STATUES_IN_ROOM "_statues_in_room"
 
/*-----[ Imp support room. Handles imps arrival and imp quest     ]---*/
/*-----[ statues smashing                                         ]---*/
# define L3_ROOM "/d/Avenir/common/dark/l3/l3_room"
 
/*-----[ File which contains source placement manipulation        ]---*/
/*-----[ for imp quest                                            ]---*/
# define SOURCE_PLACER "/d/Avenir/common/dark/l3/entry.c"
 
/*-----[ Inheritable object for all rooms that can contain piece  ]---*/
/*-----[ of source                                                ]---*/
# define SOURCE_CHECKER "/d/Avenir/common/dark/l3/l3_so.c"

# define ALTAR		"/d/Avenir/common/dark/l3/altar.c"
 
/*-----[ Total room of places where sources can be found          ]---*/
# define ALL_SOURCES 4
 
/*-----[ Number of pieces of source that can be found per reset   ]---*/
/*-----[ Set this value to >= 3 to allow the quest to be solved   ]---*/
/*-----[ by mortals                                               ]---*/
/*-----[ Never make it more than 5!!!!!!<reboots are longer now>  ]---*/
# define SEL_SOURCES 4
 
/*-----[ Imps quest internal definitions                          ]---*/
# define ROOMS_FREED_FROM_IMPS	"_Utterdark_kicked_imps"
# define GHOST_ASKED_FOR_HELP	"_Utterdark_ghost_imps"
# define GHOST_QUEST_REWARD	20000
# define IMPS_QUEST_HAMMER	"/d/Avenir/common/dark/obj/smash_tool"
# define IMPS_ROOMS_NUMBER	10

# define IS_STATUE_SMASHER	"_is_imp_statue_smasher"
# define IS_IMP			"_is_UtterDark_imp"
# define L3_GHOST		"_Utterdark_impquest_ghost"

/*-----[ Quest solving logging                                    ]---*/
# define LOG_FILE "/d/Avenir/log/quest/impquest"
# define WRITE_LOG(ob) write_file(LOG_FILE,ctime(time()) +": "+      \
                        capitalize((ob)->query_real_name())+"("+     \
                        (ob)->query_average_stat()+") solved the "+  \
                        "impquest (20,000 xp).\n")

