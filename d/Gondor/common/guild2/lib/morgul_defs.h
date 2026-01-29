/*
 * /d/Gondor/common/guild2/lib/morgul_defs.h
 *
 * Definitions for the Morgul Mages
 *
 * Olorin, 1994-1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 *
 *
 * Changed the #define for race checking: changed the existing
 * for use in the death_room and added a second for checking the
 * shadow (for logins, deaths, etc).
 * Altrus, Feb 8, 2006
 */
#define GUILD_NAME        "Morgul Mages"
#define GUILD_TYPE        "occupational"
#define GUILD_STYLE       "magic"

#define GUILD_DIR         "/d/Gondor/common/guild2/"
#define GUILD_LIB         (GUILD_DIR + "dir/")
#define GUILD_HELP        (GUILD_DIR + "help/")
#define GUILD_TOWER       (GUILD_DIR + "tower/")
#define MORGUL_HELP       (GUILD_DIR + "help/")
#define MORGUL_SPELLS     (GUILD_DIR + "spells/")
#define MORGUL_NPC        (GUILD_DIR + "npc/")
#define MORGUL_POTIONS    (GUILD_DIR + "potions/")
#define MORGUL_POISONS    (GUILD_DIR + "poisons/")
#define MORGUL_SPELL_OBJS (MORGUL_SPELLS + "obj/")
#define MORGUL_LOG_DIR    (GUILD_DIR + "log/")

#define MORGUL_TOWER      (GUILD_DIR + "tower/")
#define MORGUL_MASTER     (GUILD_DIR + "death_room")
#define MORGUL_NAZGUL_MASTER (GUILD_DIR + "throne_room")
#define IDLENESS          (GUILD_DIR + "idleness")
#define TICKER            (GUILD_DIR + "ticker")
#define STORAGE           (GUILD_DIR + "storage")
#define MORGUL_POST       (GUILD_DIR + "post.c")

// #define GUILD_SHADOW      (GUILD_DIR + "morgul_shadow")
#define GUILD_SHADOW      ("/d/Gondor/guilds/morgulmage/morgul_shadow")
#define MORGUL_SOUL_FILE  (GUILD_DIR + "morgul_soul")
#define MORGUL_SPELL_FILE (MORGUL_SPELLS + "morgul_spells")

#define MORGUL_RECORDS    ("/d/Gondor/common/guild2/log/nazgul_records")
#define MORGUL_COMPLAINTS ("/d/Gondor/common/guild2/log/complaints")

#define MORGUL_S_SUBLOC              "Morgul_Mage_SubLoc"
#define MORGUL_M_MAGIC_INGREDIENT    "_Morgul_m_magic_ingredient"

#define MORGUL_S_GUILD_OBJECT   "morgul_guild_object"
#define MORGUL_S_SPELL_OBJECT   "Morgul_Spell_Object"
#define MORGUL_MORGUL_CROWN     "Morgul_Morgul_Crown"
#define MORGUL_S_THRONE_GRANT   "_King_granted_this_Mage_Access"

//Checks at time of joining, in the death_room. Uses a query_race_name,
//mostly for cases such as uruks and orcs, where the race name is masked
#define MORGUL_AS_ILLEGAL_RACE_NAME  ({ "dwarf", "elf", "hobbit", "half-elf", "minotaur", "kender" })

//Checked when the shadow is loaded. This is to prevent the case where
//a member is kicked out because he/she is an orc with an elf-base
#define MORGUL_AS_ILLEGAL_RACE ({ "dwarf", "hobbit" })

#define MORGUL_I_ALIGN_JOIN      -250
#define MORGUL_I_ALIGN_WARN         0
#define MORGUL_I_ALIGN_REMOVE     150

#define MORGUL_I_INIT_PENALTY       0
#define MORGUL_PENALTY_EXPEL     1000
#define MORGUL_GUILDMASTER       "toby"
#define MORGUL_EMISSARIES        ({"gorboth","toby"})


#define APPRENTICE_LEVEL           12
#define LT_LEVEL                   24
#define SAGE_LEVEL                 25

/*
 * These are the valid actions and their values used by the idle Nazgul
 * system. Never ever call IDLENESS->increase_activity() using arbitrary
 * numbers. If you can't find a suitable activity reward among the below
 * actions add a new #define.
 */
#define APPOINT            600
#define SACRIFICE         1000
#define RAKASUL            800
#define TALK                10
#define SMALL_SPELL         15
#define COMBAT_SPELL        46
#define RARE_SPELL         220
#define EMOTION             53
#define NAZ_LIB_READ        80
#define NAZ_LIB_WRITE      300
#define NAZ_LIB_CREATE     600
#define NAZ_LIB_MOVE       400
#define READ_NOTE           50
#define REMOVE_NOTE        150
#define BOARD_NOTE         200
#define PUNISH             300
#define REWARD             501
#define EXPEL             1001
#define RELEGATE          1200
#define MINOR_ACTIVITY      10
#define TYPICAL_ACTIVITY   100
#define MAJOR_ACTIVITY     250
#define OTHER_LIB_READ      50
#define OTHER_LIB_MOVE     301
#define OTHER_LIB_CREATE   501
  
// curse lasts 30 min.
#define TICKER_LENGTH   (30.0*60.0)

// Sulambar limitation values, the regen time is in player age expired
// which means you need to multiply it with 2 to get the time in seconds.
#define MAX_SULAMBAR_CHARGES	10
#define SULAMBAR_REGEN_TIME		5400

/* Defines for combat spell timers.
 *
 * New rules in effect 2007 that min prep time is 6 seconds for spells.
 *
 * Spells will have max combat aid at 2*280 PEN damage with this.
 * So a delay after at 0 sec would make the spell have a max damage
 * of that value. A delay of 6 sec would give the spell a max PEN 
 * of 3*280 PEN (probably the fact for Thunaur).
 *
 * PEN(400) = 400/4 + random(400/4) + random(400/4) + random(400/4)
 * 
 *   
 *      - Toby, 2007.02.11
 *
 * The AoB have descided that the changes of magic rules was an unsuccessful
 * experiment and I revert to the old (original) casting times.
 *
 *      - Toby, Aug 2007
 */


#define NORMAL_SPELL_I_MIN_PREP_TIME 2
#define COMBAT_SPELL_I_TIME_CAST     "_morgul_combat_spell_i_time_cast"
#define COMBAT_SPELL_I_DELAY         "_morgul_combat_spell_i_delay"
#define COMBAT_SPELL_I_MIN_PREP_TIME 2
#define COMBAT_SPELL_I_MAX_DELAY     12
#define DRAMALGOS_I_MIN_DELAY        1
#define THUNAUR_I_MIN_DELAY          2



/*
 * Defines for appointing Mages to various positions within the Tower. 
 *  - For a start only Herbalist.
 *  - Next hopefully Artifact collector
 */
#define MORGUL_APPOINT_SAVE      (MAGES_DIR + "appointed_save")
#define MORGUL_HERBALIST_MASTER  "/d/Gondor/morgul/cellar/herb_shop"

/*
 * This list keeps all morgul mage emotions that are allowed in this post office.
 */
#define ALLOWED_MORGUL_EMOTIONS ({ \
    "mamuse", "mgrab", "msmile", "hail", "mlook", "mordor", \
    "mremember", "withdraw", "aware", "gaze", "hgaze", \
    "marm", "mdismiss", "mhood", "minspect", "mleer", \
    "mnarrow", "msniff", "mturn", "torture", \
    "bnlist", "frown", "point", "smile", "grin", \
    })