/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * This the mystic_defs.h file.
 * It contains mystic guild definitions, suitable for guild titles
 * and consecrations.
 * Mortricia, March 1994
 */

/* Useful stuffies */
#define GUILD          "The Ancient Mystic Order"
#define GUILD_TAX      20
#define GUILD_TYPE     "occupational"
#define GUILD_STYLE    "fighter"
#define GUILD_DIR      "/d/Terel/mecien/valley/guild/"
#ifndef SPELL_DIR
#define SPELL_DIR      (GUILD_DIR + "spells/")
#endif
#define GUILD_HELP_DIR (GUILD_DIR + "help/")
#define MYSTIC_SOUL    (GUILD_DIR + "mystic_soul")
#define MYSTIC_SHADOW  (GUILD_DIR + "mystic_sh")
#define MYSTIC_LAY_SHA (GUILD_DIR + "mystic_lay_sh")
#define SEEKER_SHADOW  (GUILD_DIR + "seeker_sh")
#define LAY_TAX        13
#define LAY_TYPE       "layman"
#define LAY_STYLE      "mage"
#define LAY_NAME       "The Ancient Mystic Mages"

/* Some log files */
#define BANNED         (GUILD_DIR + "banned")
#define SEEKERS        (GUILD_DIR + "seekers")
#define ABSOLVED       ("/d/Terel/mecien/log/absolved")
#define CONSECRATED    ("/d/Terel/mecien/log/consecrate")
#define JOINED         ("/d/Terel/mecien/log/joined")
#define CURSED_LOG     ("/d/Terel/mecien/log/cursed")
#define HERBS          ("/d/Terel/mecien/valley/guild/spells/herbs")

/* Mystic skills */
#define ENTRANCE_QUEST 130001         /* Contains statue number         */
#define SS_CHANNELING  130002         /* Special channeling skill       */
#define MYSTIC_RANK    130003         /* Determines the rank            */
#define BLESSED        130004         /* Person is blessed so can enter */
#define PIETY          130005         /* Piety level                    */
#define OFFICE         130006         /* Determines officers            */
#define CURSED         130007         /* Determines curse level         */
#define NOVICE         130008         /* Determines novices rank        */
#define EXALT          130009         /* Determines pre-title           */
#define FRIEND         130010         /* Determines if named a friend   */

/* Maximum values for the skills trained within the guild */
#define MYSTIC_MAX_DEFENCE        90      /* Trained in guild.c           */
#define MYSTIC_MAX_AWARENESS      65      /* Trained in guild.c           */
#define MYSTIC_MAX_PARRY          40      /* Trained in guild.c           */
#define MYSTIC_MAX_CLIMB          30      /* Trained in guild.c           */
#define MYSTIC_MAX_SWORD          80      /* Trained in academy.c         */
#define MYSTIC_MAX_KNIFE          65      /* Trained in academy.c         */
#define MYSTIC_MAX_APPR_MON       50      /* Trained in academy.c         */
#define MYSTIC_MAX_APPR_OBJ       50      /* Trained in academy.c         */
#define MYSTIC_MAX_LOC_SENSE      30      /* Trained in academy.c         */
#define MYSTIC_MAX_HERBALISM      50      /* Trained by e_dryad.c         */
#define MYSTIC_MAX_ABJURATION     50      /* Trained in abj_sec.c         */
#define MYSTIC_MAX_CONJURATION    90      /* Trained in conj_sec.c        */
#define MYSTIC_MAX_ENCHANTMENT    50      /* Trained in ench_sec.c        */
#define MYSTIC_MAX_SPELLCRAFT     90      /* Trained in gen_sec.c         */
#define MYSTIC_MAX_LANGUAGE       90      /* Trained in lang_sec.c        */
#define MYSTIC_MAX_AIR            40      /* Trained by at.c              */
#define MYSTIC_MAX_DEATH          50      /* Trained by dt.c              */
#define MYSTIC_MAX_FIRE           80      /* Trained by ft.c              */
#define MYSTIC_MAX_LIFE           80      /* Trained by lt.c & adragon.c  */
#define MYSTIC_MAX_DIVINATION     70      /* Trained by eyisti.c          */
#define MYSTIC_MAX_CHANNELING     90      /* Trained by chante.c          */
#define MYSTIC_MAX_TRANSMUTATION  20      /* Trained by gnome.c           */
#define MYSTIC_MAX_EARTH          20      /* Trained by gnome.c           */

/* A list of guild specific trainers */
#define MYSTIC_TRAINERS ({GUILD_DIR + "gnome",\
                          GUILD_DIR + "chante",\
                          GUILD_DIR + "eyisti",\
                          GUILD_DIR + "lt",\
                          GUILD_DIR + "ft",\
                          GUILD_DIR + "dt",\
                          GUILD_DIR + "at",\
                          "/d/Terel/enchanted/monster/e_dryad",\
                          GUILD_DIR + "academy",\
                          GUILD_DIR + "guild",\
                          GUILD_DIR + "lang_sec",\
                          GUILD_DIR + "gen_sec",\
                          GUILD_DIR + "ench_sec",\
                          GUILD_DIR + "conj_sec",\
                          GUILD_DIR + "abj_sec"})
                          
/* The office definitions, see skill OFFICE */
#define OFFICE_DATA  (GUILD_DIR + "offices")
#define OFFICES      ({"novices", "orator", "seal"})
#define OFFICE_TITLE ({" of Novices",\
                       "Orator of the Ancients",\
                       "Keeper of the Sacred Seal"})
#define OFFICE_ORATOR  2
#define OFFICE_NOVICES 1
#define OFFICE_SEAL    3

/* Mystic objects, suitable for present(MYSTIC_XX, this_player()) */
#define MYSTIC_RING    "Mystic_ring"
#define MYSTIC_PRING   "protector_ring"
#define MYSTIC_AMULET  "mystic_amulet"
#define MYSTIC_STAFF   "mystic_staff"
#define MYSTIC_ICON    "holy_icon"
#define MYSTIC_CROWN   "mystic_crown"
#define MYSTIC_SIGNET  "sacred_signet"
#define MYSTIC_CANE    "sacred_cane"
#define MYSTIC_VIAL    "mystic_vial"
#define MYSTIC_ROBE    "mystic_robe"
#define MYSTIC_MANTLE  "sacred_mantle"
#define MYSTIC_ALB     "holy_alb"
#define MYSTIC_SATCHEL "mystic_satchel"
#define MYSTIC_BEADS   "mystic_beads"
#define MYSTIC_LAMP    "mystic_lamp"
#define MYSTIC_EMBER   "mystic_ember"
#define MYSTIC_SOOT    "holy_soot"
#define MYSTIC_HCANDLE "_mystic_heal_candle"
#define MYSTIC_MCANDLE "_mystic_mana_candle"
#define MYSTIC_FCANDLE "_mystic_fatigue_candle"
#define MYSTIC_PENDANT "star_pendant"
#define MYSTIC_CHALICE "sacred_chalice"
#define MYSTIC_GRAPES  "_mystic_grapes"
#define MYSTIC_JUICE   "_mystic_juice"
#define MYSTIC_WINE    "_mystic_wine"
#define MYSTIC_FULL    "_mystic_full"
#define MYSTIC_HIGH    "_mystic_high"

#define MYSTIC_OBJS    ({MYSTIC_RING, MYSTIC_AMULET, MYSTIC_STAFF,\
                         MYSTIC_ICON, MYSTIC_CROWN, MYSTIC_VIAL,\
                         MYSTIC_ROBE, MYSTIC_MANTLE, MYSTIC_ALB,\
                         MYSTIC_BEADS, MYSTIC_LAMP})

/* Some mystic properties */
#define MYSTIC_WEAPON   "mystic_weapon"
#define MYSTIC_ARMOUR   "mystic_armour"
#define MYSTIC_BLESSED  "blessed"
#define MYSTIC_ANOINTED "anointed"

/* Alignment limit for joining the guild */
#define JOIN_LIM      100

/* Piety (a skill) limit for spells to work */
#define PIETY_SPELL_LIM   10

/* Mystic ranks */
#define MYSTIC_TRAITOR   -1
#define MYSTIC_NOVITIATE  0
#define MYSTIC_CIRCLE     1
#define MYSTIC_STAR       2
#define MYSTIC_CANTOR     3
#define MYSTIC_EXARCH     4
#define MYSTIC_ARCHON     5
#define MYSTIC_PATRIARCH  6

/* Alignment limit for the ARCHON rank to become "holy" */
#define HOLY_LIM      1000

/* Define ranks and subranks in terms of SS_OCCUP */
#define LEVELS        ({\
                        ({14, 25}),\
                        ({35, 45, 55}),\
                        ({65, 75, 85}),\
                        ({99}),\
                        ({109}),\
                        ({109}),\
                        ({999})\
                      })
/* Define the spell levels in terms of SS_WIS */
#define SLEVELS       ({29, 59, 89, 94, 99, 999, 999})

/* Titles */
#define TRAITOR       "traitor of the Ancients"   /* Used for banned */
#define NOVTITLE      ({"Mystic Novitiate", "Mystic Acolyte"})
#define PRETITLE      ({"", "Elder ", "High Elder "})
#define RANKTITLE     ({"",\
                        "Mystic of the White Circle",\
                        "Mystic of the Holy Star",\
                        "Mystic Cantor",\
                        "Mystic Exarch",\
                        "Mystic Archon",\
                        "Patriarch of the Ancients"\
                      })

/* Useful macros */
#define MEMBER(xx)     ((xx)->query_guild_member(GUILD))
#define QM_RANK(xx)    ((xx)->query_mystic_rank())
#define QPRE_RANK(xx)  ((xx)->query_present_rank())
#define QADV_RANK(xx)  ((xx)->query_advance_rank())
#ifndef T_WIZ
#define T_WIZ(xx)      ((xx)->query_wiz_level() &&\
             "/secure/master"->query_wiz_dom(xx->query_real_name())=="Terel")
#endif
