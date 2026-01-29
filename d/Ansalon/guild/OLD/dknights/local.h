/*
 * File Name        : local.h
 * By               : Elmore.
 * Date             : April - 2001.
 *
 */ 

#define GUILD_NAME               "Death Knight of Krynn"
#define GUILD_STYLE              "fighter"
#define GUILD_STYLE2             "magic"

#define SQUIRE_TAX         30
#define CROWN_TAX          35
#define SWORD_TAX          40
#define ROSE_TAX           45
#define TAX_ARRAY          ({ SQUIRE_TAX,CROWN_TAX, SWORD_TAX, ROSE_TAX })

#define MAX_GUILD_LEVEL_SQUIRE   2
#define MAX_GUILD_LEVEL_CROWN    6
#define MAX_GUILD_LEVEL_SWORD    10
#define MAX_GUILD_LEVEL_ROSE     15

#define GUILD_WIZARD              "elmore"
#define LAST_WARNING              "_i_have_dknights_warning"
#define I_SOLVED_STEP_0           "_i_have_solved_dknights_step_0"
#define I_SOLVED_STEP_1           "_i_have_solved_dknights_step_1"
#define I_SOLVED_STEP_2           "_i_have_solved_dknights_step_2"
#define I_SOLVED_STEP_3           "_i_have_solved_dknights_step_3"
#define I_SOLVED_STEP_4           "_i_have_solved_dknights_step_4"
#define I_SOLVED_STEP_5           "_i_have_solved_dknights_step_5"

#define GUILD_DIR                 "/d/Ansalon/guild/dknights/"
#define GUILD_SHADOW              GUILD_DIR + "shadow/occ_shadow"
#define GUILD_SHADOW2             GUILD_DIR + "shadow/lay_shadow"
#define GUILD_CMDSOUL             GUILD_DIR + "soul/dknight_soul"
#define GUILD_ROOM                GUILD_DIR + "room/"
#define GUILD_OBJ                 GUILD_DIR + "obj/"
#define GUILD_ARM                 GUILD_OBJ + "armour/"
#define GUILD_WEP                 GUILD_OBJ + "weapon/"
#define GUILD_EMBLEM              GUILD_OBJ + "ring"
#define GUILD_NPC                 GUILD_DIR + "npc/"
#define GUILD_LOG                 GUILD_DIR + "log/"
#define DKNIGHT_BOARD             GUILD_LOG + "boards/normal/"
#define GUILD_EMBLEM_ID           GUILD_OBJ + "ring"
#define GUILD_IN                  GUILD_DIR + "std/i_room_base.c"
#define GUILD_STARTLOC            GUILD_ROOM + "dknight_start"
#define GUILD_SUBLOC              GUILD_NAME + " subloc"

#define DKNIGHT_PLATEMAIL         "_krynn_dknights_platemail"
#define SW                        shadow_who
#define REGEN_OBJ                 "dknight_regen_obj"
#define ONLY_DKNIGHT              "only_worn_by_dknights"
#define DKNIGHT_ARMOUR            "_dknight_armour"

#define SS_GUILD_SPECIAL_REAP     666666
#define SS_GUILD_SPECIAL_DASSAULT 666667
#define DK_SPELLS                 (143005)

#define SPELLS                    (GUILD_DIR + "spells/spells")
#define SPELL_DIR                 GUILD_DIR + "spells/"
#define WEAPON_SPEC_SKILL         666667
#define FEAR_OBJ                  GUILD_OBJ + "dknight_fear"
#define BLIND_OBJ                 GUILD_OBJ + "dknight_blind"
#define STUN_OBJ                  GUILD_OBJ + "dknight_stun"

#define IS_DK(ob) (ob->query_guild_name_occ() == "Death Knight of Krynn")

#define DK_JOIN_ADJS      "_death_knights_krynn_join_adjs"
#define DK_ADJ_LIST     ({ "eyeless", "deathly", "glowing-eyed",    \
                           "ember-eyed", "zombie-like",             \
                           "empty-eyed",  "rancid", "unholy",       \
                           "ghastly", "foul", "decaying", "cruel",  \
                           "skeletal", "gloomy", "sullen",          \
                           "ominous", "ashen", "grim", "eerie",     \
                           "haggard", "spectral", "ghostly",        \
                           "macabre", "soul-less", "gaunt",         \
                           "horrible", "cold", "ancient",           \
                           "ashen", "atrocious", "baleful",         \
                           "blackened", "burned", "charred",        \
                           "cruel", "demonic", "depraviated",       \
                           "disgraced", "disliked", "fabled",       \
                           "feared", "gaunt", "grisly",             \
                           "gruesome", "harmful", "horrible",       \
                           "intense", "loyal", "mythical",          \
                           "ominous", "orange-eyed", "osseously",   \
                           "potent", "puissant", "reticent",        \
                           "rotten", "scragy", "scrawny",           \
                           "silent", "skinny", "soul-less",         \
                           "suffering", "sullen", "taciturning",    \
                           "tall", "thin", "tormented",             \
                           "towering", "unholy" })









