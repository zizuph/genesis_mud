// file name: ~Avenir/common/park/faerie_quest.h
// creator(s):  Ilyian
// last update: April 1995
// purpose: definitions for the rescue the faerie quest
// note: more or less copied from Kazz's tomato_drop.h, with permission
// bug(s):
// to-do:

#define GROUP 0
#define BIT   14

#define QUEST_VERSION   "_avenir_got_faerie_quest_"
#define ACCEPTED        1
#define NOT_ACCEPTED      0

#define FAERIE_QUEST_XP    25000

#define FAERIE_ID "_park_quest_faerie_"

#define QUEST_ROOM "/d/Avenir/common/park/glade"

#define QUEST_ID "_avenir_faerie_quest_id_"

#define LOG_FILE "/d/Avenir/log/quest/rescue_faerie"

#define WRITE_LOG(x) (write_file(LOG_FILE, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + "," + \
             this_player()->query_alignment() + ")" + (x)))

#define KILL_NPC_FILE "/d/Avenir/ilyian/logs/quest_killers"

#define WRITE_GEN_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))
