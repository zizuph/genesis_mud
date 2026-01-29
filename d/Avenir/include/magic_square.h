//-*-C++-*_
// file name: ~Avenir/include/magic_square.h
// creator(s): Boriska, Nov 1994         
// last update: Mar 2 1995
//              Zizuph Aug 2022: update for quest fix
// purpose:     common constants and definitions for magic square quest.
// note:        See ~Avenir/QUEST/magic_square.doc
// bug(s):
// to-do:     

#define GROUP 0
#define BIT 2
// quest bit

// Xp and money values are for test purposes only!
#define BIG_XP 30000
// given out when artifact returned

//money rewards in gold
#define BIG_MONEY 125
// handed out by Josen for helping him

#define JUST_MONEY 25
// handed out by Barmaley for helping him

#define SIZE 3
// square size

// number of stones given to player is a sum of first 9 members in
// arithmetical progression with first member a1 picked from the
// interval [1,START_MAX-1] and increment d picked from interval [1,INCR_MAX-1]
// The formula for the sum is s = 9*(a1 + 4*d).

#define START_MAX 11
#define INCR_MAX 4

#define QUEST_ITEM "/d/Avenir/common/dark/obj/m_stone"
// stone to be dropped

#define QUEST_ROOM "/d/Avenir/common/dark/l4/cr"
// rooms' files names forming a square start like that

#define SQUARE_SUM "_avenir_i_square_sum_"
// set to expected sum of magic square

#define QUEST_VERSION "_avenir_i_magic_square_version_"
//negative for inquisitor, positive for hegemon

#define QUEST_ID "_avenir_s_magic_square_quest_id_"
//used to distinguish stones given to different players

#define SQUARE_SOLVED "_avenir_i_magic_square_solved_"
// set in players after successful ascend on the pillar and getting to
// the artifact room.
// Filters out people who obtain the artifact from somebody else

#define POUCH "/d/Avenir/common/dark/obj/pouch"

#define DAIS_ROOM "/d/Avenir/common/dark/l4/cr22"

#define ARTIFACT_ROOM "/d/Avenir/common/dark/l4/ceiling"

#define ARTIFACT "/d/Avenir/common/dark/obj/flame"

// id for recognition of the artifact
// Zizuph - added underscores to id
#define ARTIFACT_ID "_flame_that_is_not_a_flame"

#define VIAL "/d/Avenir/common/dark/obj/vial"

#define VIAL_ID "_avenir_vial_"

#define LOG_FILE "/d/Avenir/log/quest/magic_square"

#define WRITE_LOG(x) (write_file(LOG_FILE, ctime(time()) + " " + \
	     this_player()->query_name() + "(" + \
	     this_player()->query_average_stat() + "," + \
	     this_player()->query_alignment() + ")" + (x)))
