/* Guild.h */

#define GUILD_NAME    "Dwarven Warriors of the Neidar Clan"
#define GUILD_TYPE    "occupational"
#define GUILD_STYLE   "fighter"
#define GUILD_TAX     28
#define DOOM_TAX      31
#define GUILD_WIZ     "arman"

#define GUILD_DIR      "/d/Ansalon/guild/neidar/"
#define GUILD_ROOMS    GUILD_DIR+"rooms/"
#define GUILD_OBJS     GUILD_DIR+"objects/"
#define GUILD_NPCS     GUILD_DIR+"npcs/"
#define GUILD_SHADOWS  GUILD_DIR + "shadows/"
#define GUILD_SPECIALS GUILD_DIR + "specials/"
#define GUILD_EFFECTS  GUILD_SPECIALS + "effects/"
#define GUILD_SOULS    GUILD_DIR + "souls/"
#define GUILD_LIB      GUILD_DIR + "lib/"
#define GUILD_LOG      GUILD_DIR + "log/"
#define GUILD_DATA     GUILD_DIR + "data/"
#define GUILD_POST     GUILD_ROOMS + "post"
#define HELP_DIR       GUILD_DIR + "help/"
#define GUILD_EMBLEM   GUILD_OBJS + "emblem"
#define NEIDAR_SHADOW  GUILD_SHADOWS + "occ_shadow"
#define NEIDAR_CMDSOUL GUILD_SOULS + "cmdsoul"

#define DOOMSEEKER_SOUL (GUILD_SOULS + "doom_cmdsoul")

#define JOINED         "clan/joined_clan"
#define LEFT           "clan/left_clan"
#define ELDER_LIST     "clan/elder_list"
#define OLD_ELDER_LIST "clan/elder_list.old"
#define MEMBERS_LOG    "clan/members"

#define EXILE_MASTER   (GUILD_DIR + "objects/exile_master")
#define ADMIN          "/d/Ansalon/guild/neidar/rooms/admin"
#define ADMIN_MANAGER  (GUILD_LIB + "neidar_member_manager")
#define SAVE_PATH      GUILD_DIR + "log/"
#define DEBUGGER_TELL  "/d/Genesis/specials/debugger/debugger_tell.h"

#define BANISHED(p1)        EXILE_MASTER->query_is_exile(p1->query_real_name())
#define IS_MEMBER(p1)       ADMIN_MANAGER->query_is_member(p1)
#define IS_ELDER(p1)        ADMIN_MANAGER->query_elder_bits(p1)
#define IS_THANE(p1)        ADMIN_MANAGER->query_thane_bits(p1)
#define IS_EXILED(p1)       ADMIN_MANAGER->query_exile_bits(p1)
#define IS_DOOMSEEKER(p1)   ADMIN_MANAGER->query_is_doomseeker(p1)


#define AK_DEBUG(x)	    find_player("arman")->catch_msg("[Clan] " + x + "\n")

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
#define BATTLERAGING_SKILL       143003
#define SS_CLANTITLE             143016

/*
 * Special attack defines
 */
#define CHOP_NORMAL_AID 50
#define CHOP_FIERCE_AID 40
#define CHOP_AGGRESSIVE_AID 60
#define CHOP_MAX_AID CHOP_AGGRESSIVE_AID

#define CHOP_RACIAL_BONUS 5
#define NEIDAR_BLOCK_AID 20
#define ARMOUR_MASTER_AID 10
#define DEFENCE_MASTER_AID 40
#define STUBBORN_AID 15
#define STUBBORN_FULL_STRENGTH_TIME 90

// Chop gives 10% less aid when in fierce
#define BATTLERAGE_FIERCE_DAM_REDUCE_AID 10
// Chop gives 10% more aid when in aggressive
#define BATTLERAGE_AGGRESSIVE_DAM_ADD_AID 10
// During stubborn, they don't get normal attacks nor chop.
// We give 150% for this, but in actuality, they also lose layman too
// Although not durational effects such as shield spells.
#define BATTLERAGE_STUBBORN_DAM_REDUCE_AID 150

#define I_CAN_JOIN_ANSALON_CLAN  "_i_can_join_ansalon_clan"
#define AM_SITTING               "_am_sitting"
#define STANDING_STRONG          "_standing_strong_clan_special"

#define RUNE_LOG(f, who, whm) (log_file(f, sprintf("%s %-45s (%3d)\n", \
extract(ctime(time()), 4), \
who + " was given a rune by "+ \
C(whm->query_real_name()), \
500000))

#define GUILD_STARTLOC           GUILD_ROOMS + "start"

#define NEIDAR_RACIAL_ENEMIES \
    ({ "goblin", \
        "troll", \
        "giant", \
        "orc", \
        "hill giant", \
        "minotaur", \
        "ogre", \
        "half-ogre", \
        "ogre-magi", \
        "uruk", \
        "hobgoblin" \
    })

#define DOOMSEEKER_BANNED_ARMOURS \
    ({  A_BODY, \
        A_TORSO, \
        A_CHEST, \
        A_HEAD, \
        A_ARMS, \
        A_LEGS, \
        A_SHIELD, \
        W_RIGHT, \
        W_LEFT \
    })

#define NEIDAR_BLOCK_TARGET   "_neidar_block_target"

#define OPTIONS_MANAGER         (GUILD_LIB + "options_manager")
#define TIRELESS_SH             (GUILD_SHADOWS + "tireless_sh")
#define TIRELESS_OBJ            (GUILD_EFFECTS + "tireless_obj")
#define ARMOUR_MASTER_SH        (GUILD_SHADOWS + "armour_master_sh")
#define ARMOUR_MASTER_OBJ       (GUILD_EFFECTS + "armour_master_dam_mod")
#define STUBBORN_OBJ            (GUILD_EFFECTS + "stubborn_dam_mod")
#define DEFENCE_MASTER_OBJ      (GUILD_EFFECTS + "defence_master_evade")
#define NEIDAR_BLOCK_OBJ        (GUILD_EFFECTS + "neidarblock_evade")
#define CHOP_ABILITY            (GUILD_SPECIALS + "chop")
#define DOOM_CHOP_ABILITY       (GUILD_SPECIALS + "doom_chop")
#define DMASTER_ABILITY         (GUILD_SPECIALS + "defence_master")
#define BATTLERAGE_ABILITY      (GUILD_SPECIALS + "battlerage")
#define DOOM_BATTLERAGE         (GUILD_SPECIALS + "doom_battlerage")
#define BATTLERAGE_FIERCE       (GUILD_EFFECTS + "battlerage_fierce_dam_mod")
#define BATTLERAGE_AGGRESSIVE   (GUILD_EFFECTS + "battlerage_aggressive_dam_mod")
#define BATTLERAGE_STUBBORN     (GUILD_EFFECTS + "battlerage_stubborn_dam_mod")
#define DEFEND_ABILITY          (GUILD_SPECIALS + "defend")
#define DOOM_REGEN_OBJ          (GUILD_SPECIALS + "doom_regeneration_obj")

