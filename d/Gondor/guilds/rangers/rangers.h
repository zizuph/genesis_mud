/*
 * /d/Gondor/guilds/rangers/rangers.h
 *
 * Ranger definitions
 *
 * Original Rangers coded by Elessar
 * Recoded by Gwyneth and Alto 2001-2002
 *
 * Modification log:
 *    Updated definitions, Tigerlily, January-May 2004
 *    Updated subloc defs, Gwyneth, July 2004
 *    Toggle switch to open for new apprentices, Tigerlily, Aug. 2004
 */

#ifndef RANGERS_DEFS
#define RANGERS_DEFS

#include "titles.h"

/* Basic information definitions */

#define RANGERS_GUILD_NAME            "Rangers of the Westlands"
#define RANGERS_SHORT_GUILD_NAME      "rangers"
#define RANGERS_STYLE                 "ranger"
#define RANGERS_TAX_FULL              20
#define RANGERS_TAX_NORTH             21
#define RANGERS_TAX_APPREN            8

/* Toggle for allowing new apprentices to join guild */
/*
#define RANGERS_NOT_OPEN_FOR_JOIN      1
*/

/* when false, rangers are open for new apprentices */
#define RANGERS_NOT_OPEN_FOR_JOIN      0

#ifndef DEBUG
#define DEBUG(x)            (find_living("tigerlily")->catch_msg(x))
#endif  DEBUG

/* Basic directory definitions */

#ifndef RANGERS_DIR
#define RANGERS_DIR              "/d/Gondor/guilds/rangers/"
#endif RANGERS_DIR

#define RANGERS_BOARD            (RANGERS_DIR + "boards/")
#define RANGERS_HELP             (RANGERS_DIR + "help/")
#define RANGERS_HQ_DIR           (RANGERS_DIR + "hq/")
#define RANGERS_ITH_DIR          (RANGERS_DIR + "ithilien/")
#define RANGERS_ITH_TUNNEL       (RANGERS_ITH_DIR + "tunnel/")
#define RANGERS_MANAGER          (RANGERS_DIR + "manager/")
#define RANGERS_LIBRARY          (RANGERS_DIR + "library/")
#define RANGERS_NOR_DIR          (RANGERS_DIR + "north/")
#define RANGERS_AMB_DIR          (RANGERS_DIR + "ambush/")
#define RANGERS_NPC              (RANGERS_DIR + "npc/")
#define RANGERS_OBJ              (RANGERS_DIR + "obj/")
#define RANGERS_POTION           (RANGERS_DIR + "potions/")
#define RANGERS_SPECIAL          (RANGERS_DIR + "special/")
#define RANGERS_SPECIAL_OBJ      (RANGERS_SPECIAL + "obj/")
#define RANGERS_SPELL            (RANGERS_DIR + "spells/")
#define RANGERS_TEXT             (RANGERS_DIR + "text/")
#define RANGERS_TASK             (RANGERS_DIR + "tasks/")
#define TRACKTASK_DIR            (RANGERS_DIR + "tasks/tracktask/")

/* Important file definitions */

#define MANAGER                  (RANGERS_MANAGER + "manager")
#define MEMBER_VOTE_ITH          (RANGERS_ITH_DIR + "window")
#define MEMBER_VOTE_NOR          (RANGERS_NOR_DIR + "great_hall")
#define RANGERS_SHADOW           (RANGERS_DIR + "shadow/rangers_shadow")
#define RANGERS_SOUL             (RANGERS_DIR + "soul/rangers_soul")
#define RANGERS_ITH_EMBLEM       (RANGERS_OBJ + "roi_amulet")
#define RANGERS_NOR_EMBLEM       (RANGERS_OBJ + "ron_brooch")
#define RANGERS_APP_EMBLEM       (RANGERS_OBJ + "app_ring")
#define RANGERS_COUNCILKEY       (RANGERS_OBJ + "councilkey")
#define RANGERS_EMBLEM_ID        "_rangers_emblem_id"

/* Log file definitions */
#define RANGERS_LOG_DIR          (RANGERS_DIR + "log/")
#define RANGERS_WIZ_LOG          ("newrangers")
#define RANGERS_LOG              (RANGERS_LOG_DIR + "rangers_log")
#define NORTH_LOG                (RANGERS_LOG_DIR + "north")
#define ITHILIEN_LOG             (RANGERS_LOG_DIR + "ithilien")
#define APPRENTICE_LOG           (RANGERS_LOG_DIR + "apprentice")
#define LOG_SIZE                 15000

/* Guildhouse rooms */

#define RANGERS_NOR_POST         (RANGERS_NOR_DIR + "post")
#define RANGERS_ITH_POST         (RANGERS_ITH_DIR + "post")
#define RANGERS_HQ_POST          (RANGERS_HQ_DIR  + "post")

#define RANGERS_NOR_TRAIN        (RANGERS_NOR_DIR + "north_train")
#define RANGERS_ITH_TRAIN        (RANGERS_ITH_DIR + "train")
#define RANGERS_HQ_TRAIN         (RANGERS_HQ_DIR  + "ch_train")

#define RANGERS_NOR_START        (RANGERS_NOR_DIR + "start")
#define RANGERS_ITH_START        (RANGERS_ITH_DIR + "start")
#define RANGERS_HQ_START         (RANGERS_HQ_DIR  + "start")
#define RANGERS_START            (({ RANGERS_NOR_START, \
                                     RANGERS_ITH_START, \
                                     RANGERS_HQ_START }))

/* Board directories */

#define RON_BOARD                (RANGERS_BOARD + "ron_board")
#define RON_COUNCIL_BOARD        (RANGERS_BOARD + "ron_cboard")
#define ROI_BOARD                (RANGERS_BOARD + "roi_board")
#define ROI_COUNCIL_BOARD        (RANGERS_BOARD + "roi_cboard")
#define HQ_BOARD                 (RANGERS_BOARD + "hq_board")
#define HQ_COUNCIL_BOARD         (RANGERS_BOARD + "hq_cboard")


/* Ranger skills */

#define SKILLS                                                              \
({ SS_WEP_SWORD, SS_WEP_POLEARM, SS_WEP_MISSILE, SS_PARRY, SS_DEFENCE,      \
   SS_HERBALISM, SS_ALCHEMY,                                                \
   SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_CONJURATION, SS_FORM_ABJURATION, \
   SS_SNEAK, SS_HIDE, SS_AWARENESS, SS_TRACKING, SS_FR_TRAP,                \
   SS_LOC_SENSE, SS_HUNTING, SS_ANI_HANDL,                                  \
   SS_HEARING, SS_BRAWLING, SS_AMBUSH })

#define APPRENTICE_SKILLS        ({ 50, 30, 30, 10, 50, \
                                    35, 20,             \
                                    30, 30, 20, 10,     \
                                    50, 50, 70, 40, 20, \
                                    30, 30, 30,         \
                                    50, 50, 50 })
#define APPROVED_APP_SKILLS      ({ 50, 30, 30, 10, 50, \
                                    35, 20,             \
                                    30, 30, 20, 10,     \
                                    50, 50, 70, 40, 20, \
                                    30, 30, 30,         \
                                    50, 50, 50 })
#define NORTH_SKILLS             ({ 80, 30, 80, 10, 75, \
                                    70, 20,             \
                                    70, 65, 35, 30,     \
                                    80, 80, 85, 75, 30, \
                                    30, 30, 30,         \
                                    100, 100, 100 })
#define ITHILIEN_SKILLS          ({ 90, 90, 30, 75, 75, \
                                    60, 20,             \
                                    50, 55, 20, 15,     \
                                    70, 70, 75, 60, 20, \
                                    30, 30, 30,         \
                                    100, 100, 100 })
/* Because rangers have to choose between sword and polearm/missiles, they
 * cannot reach the total maximum. Therefore there is a delta from the
 * total. */
#define TRAIN_CHOICE_DELTA ({ -20, -20, -50, -60 })

#define COMPANIES                ({ "the Ranger Apprentices",         \
                                    "the Trusted Ranger Apprentices", \
                                    "the North",                      \
                                    "Ithilien"})
#define COMPANY_TITLE            ({ "the Ranger Apprentices",         \
                                    "the Trusted Ranger Apprentices", \
                                    "North",                          \
                                    "Ithilien" })
#define COMPANY_SKILLS           ({ APPRENTICE_SKILLS, APPROVED_APP_SKILLS, \
                                    NORTH_SKILLS, ITHILIEN_SKILLS })

/* Skills with training limited by the guild stat SS_OCCUP */

#define SUBTERFUGE_SKILLS        ({ SS_SNEAK, SS_HIDE, SS_HEARING, \
                                    SS_FR_TRAP, SS_AWARENESS })
#define NATURE_SKILLS            ({ SS_HERBALISM, SS_ALCHEMY, SS_TRACKING, \
                                    SS_HUNTING, SS_LOC_SENSE })
#define COMBAT_SKILLS            ({ SS_BRAWLING, SS_WEP_SWORD, SS_DEFENCE, SS_AMBUSH })
#define LEARN_FACTOR             3


/* Ranger looks */
#define RANGER_LOOKS   ({ "young and energetic", \
              "fresh and spirited", \
              "young but thoughtful", \
              "slightly tattered", \
              "fairly well-travelled", \
              "dusty and windblown", \
              "disheveled and care-worn", \
              "hardened and wind-swept", \
              "weather-beaten and grim-faced", \
              "weary and stone-faced", \
              "wary and scarred", \
              "aged and storm-blown", \
              "worn by years of travel", \
              "grim and terrible, yet wise", \
               })

#define RANGER_S_SUBLOC "_ranger_s_subloc"

#define OBJ_O_BELONGS_TO_RANGER   "_obj_o_belongs_to_ranger"

/* Reward and Punishment definitions */

#define SLIGHT_REWARD            1
#define MODERATE_REWARD          5
#define GENEROUS_REWARD          8

/* Lowest sword skill level to remain in blademasters. */
#define BLADEMSTR_SWRD           75

#define NO_BRAWL                 1
#define NO_SPELLS                2
#define NO_SKILLS                3
#define PUNISHMENTS              ([ "no brawl" : NO_BRAWL, \
                                    "no spells" : NO_SPELLS, \
                                    "no skills" : NO_SKILLS ])

/* Miscellaneous definitions */

#define RAN_ALIGN_MIN            100
#define ALIGN_WARN               (RAN_ALIGN_MIN + 50)
#define ALIGN_JOIN               (ALIGN_WARN + 50)
#define BANNED_RACE              ({"goblin", "half-orc", "hobgoblin", \
                                   "kender", "orc", "uruk", "minotaur"})
#define BANNED_GUILDS            ({ "Morgul Mages", "Dragonarmy", \
                                    "Priests of Takhisis",\
                                    "Vampires of Emerald",\
                                    "Templars of Takhisis",\
                                    "Necromancers Of Vile Darkness",\
                                    "Army of Darkness",\
                                    "Warlocks of Faerun"\
                                  })
#define APPRENTICE_MAX           3

/* Task defines */
#define TASK_HERBS               ({ "lothore", "redweed", "athelas", \
                                    "foxglove", "attanar", "alfirin" })
#define TASK_RANDOM              867530
#define RANGER_S_MADE_POTION     "_ranger_s_made_potion"
#define RANGER_I_TASK            "_ranger_i_task"
#define RANGER_I_SUCCESS_CURE    "_ranger_i_success_cure"
#define RANGER_I_FAILED_CURE     "_ranger_i_failed_cure"
#define RANGER_O_FIRE_TASK       "_ranger_o_fire_task"
#define RANGER_O_COOK_TASK       "_ranger_o_cook_task"
#define RANGER_O_ROASTED         "_ranger_o_roasted"
#define RANGER_S_ROASTED         "_ranger_s_roasted"
#define RANGER_I_RABBIT          "_ranger_i_rabbit"
#define RANGER_S_POTION          "_ranger_s_potion"
#define WARG_S_TEAM              "_warg_s_team"
#define FIRE_TASK                1
#define COOK_TASK                2
#define TRACK_TASK               3
#define SPELL_TASK               4
#define HERB_TASK                5
#define POTION_TASK              6
#define CURE_TASK                7
#define WARRIORS_TASK            8

/* Valid Ranger test */

#define NON_RANGER_LEVEL          0
#define APPRENTICE_LEVEL          1
#define APPROVED_APP_LEVEL        2
#define NORTH_LEVEL               3
#define ITHILIEN_LEVEL            4
#define CAPTAIN_POSITION          0
#define LIEUTENANT_POSITION       1
#define SERGEANT_POSITION         2

/* Voting related defines */
#define NO_ELECTIONS              0
#define NOMINATION_VOTE           1
#define CAPTAIN_ELECTION          2
#define IMPEACHMENT_VOTE          3

/* Time related defines */
/* 16 weeks max to become a Ranger */
#define APPRENTICE_TIME_OUT    9676800

/* 14 weeks */
#define FOURTEEN_WEEKS         8467200

/* 4 weeks rejoin time (28 days) */
#define REJOIN_TIME            2419200

/* 1 year outlaw time out */
/* adjusted upward per council request */
#define OUTLAW_TIME_OUT        31449600

/* 1 year notorious outlaw time out */
#define NOTORIOUS_TIME_OUT     31449600

/* Have regular elections every 24 weeks */
#define REGULAR_ELECTION_TIME  14515200

/* Election length  1 week */
#define ELECTION_TIME_OUT      604800

/* 3 days impeach grace time */
#define IMPEACH_GRACE_TIME     259200

/* How often to backup files, in days */
#define BACKUP_DAYS            7

/* How often to clean up old backup files, in days */
#define BACKUP_CLEANUP          182


/* Ranger member macros */
#define RANGERS_MEMBER(x)         ((x)->query_guild_name_occ() ==    \
                                        RANGERS_GUILD_NAME)
#define RANGERS_FULL_MEMBER(x)    (RANGERS_MEMBER(x) &&              \
                                        (x)->query_ranger_level() >  \
                                        APPROVED_APP_LEVEL)
#define APPRENTICE_MEMBER(x)      (RANGERS_MEMBER(x) &&              \
                                        (x)->query_ranger_level() == \
                                        APPRENTICE_LEVEL)
#define APPROVED_APP_MEMBER(x)    (RANGERS_MEMBER(x) &&              \
                                        (x)->query_ranger_level() == \
                                        APPROVED_APP_LEVEL)
#define NORTH_MEMBER(x)           (RANGERS_MEMBER(x) &&              \
                                        (x)->query_ranger_level() == \
                                        NORTH_LEVEL)
#define ITHILIEN_MEMBER(x)        (RANGERS_MEMBER(x) &&              \
                                        (x)->query_ranger_level() == \
                                        ITHILIEN_LEVEL)

#define MASTER_RANK                80
/* Lowered required rank to assign a speciality */
/*
#define SPECIALTY_RANK             60
*/
#define SPECIALTY_RANK             40
#define COMP_REQUIREMENT           40
#define APP_RANK_REQUIREMENT       40
#define LEG_STAT                   150        /* required guild-stat */
#define LEG_AGE                    4320000    /* 100 days of playing age */

/* Spell-related definitions */

#define GENESIS_SPELL_DIR          "/d/Genesis/newmagic/"
#define RANGER_SPELL_OBJ_DIR       (RANGERS_SPELL + "obj/")
#define RANGER_SPELL_TXT           (RANGERS_SPELL + "txt/")
#define SPELL_INHERIT              (RANGERS_SPELL +"spell_inherit")
#define VIRTUE_SPELL_INHERIT       (RANGERS_SPELL +"virtue_spell_inherit")
#define SPELL_OBJECT               (GENESIS_SPELL_DIR + "spell_effect_object")
#define GENESIS_SPELL_LIB          (GENESIS_SPELL_DIR + "spell")
#define SPELLBOOK                  (RANGERS_SPELL + "spellbook")
#define COPY_SCROLL                (RANGER_SPELL_OBJ_DIR + "copy_scroll")

#define SPELL_WHISTLE              1
#define SPELL_HEAL                 2
#define SPELL_REST                 4
#define SPELL_CLEANSE              8
#define SPELL_NIGHTVISION          16
#define SPELL_ELBERETH             32
#define SPELL_SPEEDGROW            64
#define SPELL_BLESS               128
#define SPELL_CONCEAL             256

#ifndef SS_RANGER_SPELL_LIST
#define SS_RANGER_SPELL_LIST       118214
#endif  SS_RANGER_SPELL_LIST

#ifndef SS_RANGER_DISFAVOUR
#define SS_RANGER_DISFAVOUR        118215
#endif  SS_RANGER_DISFAVOUR

#ifndef SS_RANGER_TEAM
#define SS_RANGER_TEAM             118216
#endif  SS_RANGER_TEAM

#ifndef SS_RANGER_PRI_WEP
#define SS_RANGER_PRI_WEP         118217
#endif  SS_RANGER_PRI_WEP

#define AMBUSH_TOHIT                95
#define AMBUSH_PREP                 9
#define AMBUSH_COOLDOWN             1
#define AMBUSH_SKILLS              ({ SS_AMBUSH })
#define AMBUSH_STATS               ({ SKILL_AVG, TS_STR, TS_DEX, TS_WIS, SKILL_END })

#define RANGER_MAJOR_CAID          75
#define RANGER_MINOR_CAID          25
#define RANGER_MAJOR_GROUP         "ranger_major"

#define BRAWL_TOHIT                95
#define BRAWL_PREP                  5
#define BRAWL_COOLDOWN              5
#define BRAWL_SKILLS              ({ SS_BRAWLING })
#define BRAWL_STATS               ({ SKILL_AVG, TS_DEX, TS_WIS, TS_DIS, SKILL_END })

#define STAT_WEIGHTING               ({ SKILL_WEIGHT, 60, TS_WIS, SKILL_WEIGHT, 20, TS_INT, SKILL_WEIGHT, 20, TS_DIS })


// This should allow three opponents to be brawled.
// 30 seconds is the maximum cycle time for various abilities.
#define BRAWL_CYCLE_TIME           30


#ifndef HE
#  define HE(x)  (x)->query_pronoun()
#endif
#ifndef HIS
#  define HIS(x) (x)->query_possessive()
#endif
#ifndef HIM
#  define HIM(x) (x)->query_objective()
#endif
/* Definitions to make combat messages easier */
#define ME(x)   me->catch_msg(x+"\n")
#define YOU(x)  target->catch_msg(x+"\n");
#define TW(x)   me->tell_watcher(x+"\n", target);
#define TWM(x)  me->tell_watcher_miss(x+"\n", target);


#define RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST     1
#define RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING      2
#define RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW   3
#define RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS  4
#define RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN    5
#define RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH 6
#define RANGER_MAJOR_VIRTUE_OLD_HATRED            7

#define RANGER_MAJOR_VIRTUE_DEFAULT   RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST

#define RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR 1
#define RANGER_MINOR_VIRTUE_DEEP_SONGS            2
#define RANGER_MINOR_VIRTUE_WARDEN_OF_PELENNOR    3
#define RANGER_MINOR_VIRTUE_DEADLY_ARCHERS        4
#define RANGER_MINOR_VIRTUE_ART_OF_DISAPPEARING   5
#define RANGER_MINOR_VIRTUE_NOBLE_LINEAGE         6
#define RANGER_MINOR_VIRTUE_FRIEND_OF_ROHAN       7
#define RANGER_MINOR_VIRTUE_GIFTS_OF_ESTE         8

#define RANGER_MINOR_VIRTUE_DEFAULT   RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR

#define RANGER_MAJOR_VIRTUE_CHANGE_TIME  (86400 * 28)
#define RANGER_MINOR_VIRTUE_CHANGE_TIME  (86400 * 14)

#define SPELL_MANAGER_SOUL       ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define MANA_SHADOW              ("/d/Genesis/specials/guilds/shadows/mana_shadow")

#define MAJOR_VIRTUES_TO_NAME  ([ \
    RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST : "Enemy of the East", \
    RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING : "Hand of the King", \
    RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW : "Enemy of the Shadow", \
    RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS : "Sentinel of Imladris", \
    RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN : "Dauntless Guardian", \
    RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH : "Defender of Osgiliath", \
    RANGER_MAJOR_VIRTUE_OLD_HATRED : "Supporter of the Old Hatred" ])

#define MINOR_VIRTUES_TO_NAME ([ \
  RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR : "Blessing of the Eldar", \
  RANGER_MINOR_VIRTUE_DEEP_SONGS : "Deep Songs", \
  RANGER_MINOR_VIRTUE_WARDEN_OF_PELENNOR : "Ways of the Warden of Pelennor", \
  RANGER_MINOR_VIRTUE_DEADLY_ARCHERS : "Art of Deadly Archery", \
  RANGER_MINOR_VIRTUE_ART_OF_DISAPPEARING : "Art of Disappearing", \
  RANGER_MINOR_VIRTUE_NOBLE_LINEAGE : "Noble Lineage", \
  RANGER_MINOR_VIRTUE_FRIEND_OF_ROHAN : "Teachings of Rohan", \
  RANGER_MINOR_VIRTUE_GIFTS_OF_ESTE : "Gifts of Este" ])

#endif RANGERS_DEFS

