/* Guild.h */

#define GUILD_NAME    "Dwarven Warriors of the Neidar Clan"
#define GUILD_STYLE   "fighter"
#define GUILD_TAX     18


#define GUILD_DIR   "/d/Ansalon/guild/dwarf/"

#define GUILD_SHADOW  GUILD_DIR + "occ_shadow"
#define GUILD_CMDSOUL GUILD_DIR + "cmdsoul"
#define GUILD_EMBLEM  GUILD_DIR + "emblem"
#define GUILD_POST    GUILD_DIR + "post"
#define HELP_DIR      GUILD_DIR + "help/"

#define JOINED        "clan/joined_clan"
#define LEFT          "clan/left_clan"
#define ELDER_LIST    "clan/elder_list"
// #define EXILE_MASTER  (GUILD_DIR + "exile_master")
#define EXILE_MASTER      ("/d/Ansalon/guild/neidar/objects/exile_master")

#define BANISHED(p1) EXILE_MASTER->query_is_exile(p1->query_real_name())
/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + " emblem"
#define MEMBER(ob) ob->query_guild_member("Dwarven Warriors of the Neidar Clan")
#define GURU_QUEST_STAT 134
#define CHIEFTAIN_STAT 168

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */
#define WEAPON_SPEC_SKILL        143001
#define SS_GUILD_SPECIAL_SKILL   143002
#define SLAM_SPECIAL_SKILL       143003
#define SS_CLANTITLE             143016

#define I_CAN_JOIN_ANSALON_CLAN  "_i_can_join_ansalon_clan"
#define AM_SITTING               "_am_sitting"
#define STANDING_STRONG          "_standing_strong_clan_special"

#define RUNE_LOG(f, who, whm) (log_file(f, sprintf("%s %-45s (%3d)\n", \
extract(ctime(time()), 4), \
who + " was given a rune by "+ \
C(whm->query_real_name()), \
500000))

#define GUILD_STARTLOC           GUILD_DIR + "start"

#define ADMIN       "/d/Ansalon/guild/dwarf/admin"
#define SAVE_PATH   GUILD_DIR + "log/"
