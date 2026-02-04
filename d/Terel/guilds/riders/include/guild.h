#ifndef RIDER_DEFS
#define RIDER_DEFS

#define GUILD_NAME  "Riders of Last"
#define GUILD_STYLE "fighter"
#define GUILD_TAX   10
#define NUM_TITLES     5
#define MAX_SS_LAYMAN     120

#define RIDER_DIR "/d/Terel/guilds/riders/"

#define RIDER_ROOM_DIR     (RIDER_DIR + "room/")
#define RIDER_OBJ_DIR      (RIDER_DIR + "obj/")
#define RIDER_LOG_DIR      (RIDER_DIR + "log/")
#define RIDER_NPC_DIR      (RIDER_DIR + "npc/")
#define RIDER_HELP_DIR     (RIDER_DIR + "help/")
#define RIDER_STD_DIR      (RIDER_DIR + "std/")
#define RIDER_LIB_DIR      (RIDER_DIR + "lib/")
#define RIDER_MON_DIR      (RIDER_DIR + "monster/")

#define RIDER_LOG          (RIDER_LOG_DIR + "log")
#define RIDER_INFO_LOG      (RIDER_LOG_DIR + "rider_log")
#define RIDER_MBR_LOG         (RIDER_LOG_DIR + "member")
#define RIDER_SHADOW          (RIDER_DIR + "rider_shadow")
#define RIDER_SOUL            (RIDER_DIR + "rider_soul")
#define RIDER_GUILD_EMBLEM    (RIDER_OBJ_DIR + "sash")
#define RIDER_GUILD_EMBLEM_ID "_RIDER_guild_emblem"
#define RIDER_LEADER_EMBLEM_ID "_RIDER_leader_emblem"
#define RIDER_SUBLOC          "_rider_last_subloc"
#define RIDER_STARTLOC        (RIDER_ROOM_DIR + "start")

#define COUNCIL_MEMBER(x) (RIDER_LOG->query_council_member(x))
#define IS_MEMBER(x) (x->query_guild_member(GUILD_NAME))

#define ENV(arg)   environment(arg)
#define TP         this_player()
#define TO         this_object()
#define TI         this_interactive()
#define NF(mesg)   notify_fail(mesg)
#define PRONOUN(x)      (x->query_pronoun())

#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
   (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) :\
   (write_file(file, ctime(time()) + ": " + entry + "\n")))

#endif
