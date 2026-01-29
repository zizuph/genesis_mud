// file name:   /d/Avenir/common/outpost/tomato_quest/tomato_drop.h
// creator(s):  Kazz
// last update: April 1995
//		Denis, Jul'96: Moved the file out of outpost dir into
//			       separate tomato quest directory,
//			       various misc changes supplementing the conversion
//			       of the quest to SMIS-version.
// purpose: 	defines for tomato_drop quest started by outpost/mon/brat
// note:
// bug(s):
// to-do:      

// approved by Goldberry
# define TOMATOQ_GROUP		0
# define TOMATOQ_BIT		13


// used to signify the brat already told player the quest
# define TOMATOQ_QUEST_VERSION 	"_avenir_started_tomato_drop_quest_"
# define TOMATOQ_ACCEPTED	1
# define TOMATOQ_NOT_ACCEPTED	0

# define TOMATOQ_QUEST_XP	1500

# define TOMATOQ_DIR		"/d/Avenir/common/outpost/tomato_quest/"
# define TOMATOQ_TOWER		"/d/Avenir/common/outpost/tower_middle2"
# define TOMATOQ_SNOB_LOC	"/d/Avenir/common/outpost/fort3"
# define TOMATOQ_BRAT_LOC	"/d/Avenir/common/outpost/fort6"

# define TOMATOQ_TOMATO		"/d/Avenir/common/outpost/tomato_quest/tomato"

# define TOMATOQ_QUEST_ID	"_avenir_tomato_drop_quest_id_"

# define TOMATOQ_LOG_FILE "/d/Avenir/log/quest/tomato_drop"
# define TOMATOQ_WRITE_LOG(x) (write_file(TOMATOQ_LOG_FILE, ctime(time()) + \
             " " +							    \
	     this_player()->query_name() + "(" + 			    \
	     this_player()->query_average_stat() + ")" + (x)))
