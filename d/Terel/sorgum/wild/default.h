/*
 * The 2.2 CD Game Driver doesn't allow function prototypes before
 * inherit commands.  However, <std.h> has a function prototype in it!
 * Rather than remove <std.h>, I've put in a #define to take it out only
 * if specified - so that any files using it will still (hopefully) work.
 * If you want to #include this file BEFORE using inherit, then you
 * need to put the following line before #including this file :
 *      #define NO_SECURE_STD 1
 *
 * Napture.
 */
 
#ifndef NO_SECURE_STD
#include <std.h>
#endif
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#include <formulas.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <tasks.h>

/*
 * Define 'SHORT_DEFS' in your own files/headers if you don't want
 * the shorthand definitions included.  For example, if you define
 * your own short versions that would otherwise clash with these.
*/

/* break string length - second argument to break_string */
#define BSL   75

#ifndef SHORT_DEFS
#include "short_defs.h"
#endif
   
#define DOMAIN_NAME     "Emerald"

#define DOMAIN_DIR      "/d/Emerald/"

#define SERVICE_OBJ     (DOMAIN_DIR + "common/service")

#define COMMON_DIR      DOMAIN_DIR + "common/"
#define ROOM_DIR        DOMAIN_DIR + "room/"
#define OBJECT_DIR      DOMAIN_DIR + "obj/"
#define NPC_DIR         DOMAIN_DIR + "npc/"
#define SOUL_DIR        DOMAIN_DIR + "soul/"
#define HELP_DIR        DOMAIN_DIR + "help/"

#define PLUGH_DIR       DOMAIN_DIR + "plugh/"
#define HALGOR_DIR      DOMAIN_DIR + "halgor/"
#define MYLOS_DIR       DOMAIN_DIR + "mylos/"
#define KARATH_DIR      DOMAIN_DIR + "karath/"
#define KAT_DIR         DOMAIN_DIR + "kat/"
#define NAPTURE_DIR     DOMAIN_DIR + "napture/"
#define PALDIN_DIR      DOMAIN_DIR + "paldin/"
#define PHASE_DIR       DOMAIN_DIR + "phase/"
#define TEDDY_DIR       DOMAIN_DIR + "teddy/"
#define TULIX_DIR       DOMAIN_DIR + "tulix/"
#define ZAPPA_DIR       DOMAIN_DIR + "zappa/"
#define ZEEROX_DIR      DOMAIN_DIR + "zeerox/"
#define FREYJA_DIR      DOMAIN_DIR + "freyja/"

#define QUEST_FILE      DOMAIN_DIR + "common/quests"

#define GUILD_GROUP     0
#define GUILD_BIT       0

#define FLOWER_GRP      0
#define FLOWER_BIT      1
#define FLOWER_XP     200

#define GRUNTS_BIT      2

#define SYBILLE_GROUP   0
#define SYBILLE_BIT     3
#define SYBILLE_XP    750

#define VAMP_GROUP      0
#define VAMP_BIT        4

#define LORE_BIT        17

#define BLOOD_BIT	18

#define ORC_GRP         0
#define ORC_BIT         5
#define ORC_XP        300


#define ELF_BIT         6

#define HUMANISTS_BIT   13

#define PIRATE_QUEST_GROUP  3
#define YES_BIT             0
#define CYCLOPS_BIT         1
#define HORN_BIT            2
#define FOUND_CHEST         3
#define DONE_QUEST_YES      4
#define DONE_QUEST          5
 
#define CRYSTAL_QUEST              2
#define XP_CRYSTAL_QUEST_1      1500
#define XP_CRYSTAL_QUEST_1_CUBE  100
#define XP_CRYSTAL_QUEST_2       800
#define XP_CRYSTAL_QUEST_2_TAL   175
#define XP_CRYSTAL_QUEST_2_WAND  175
#define XP_CRYSTAL_QUEST_3      1000
#define XP_CRYSTAL_QUEST_3_MGEM  500
#define XP_CRYSTAL_QUEST_3_PYR   750
#define XP_CRYSTAL_QUEST_3_SAPP 1500
#define XP_CRYSTAL_QUEST_4      5000
#define XP_CRYSTAL_QUEST_4_SAPH 1700
#define XP_CRYSTAL_QUEST_5      6000
#define XP_CRYSTAL_QUEST_5_PYR   750
#define XP_CRYSTAL_QUEST_6     35000

#define ROYALTY_QUEST              2
#define XP_ROYALTY_QUEST_1      3000
#define XP_ROYALTY_QUEST_2      3000
#define XP_ROYALTY_QUEST_3      3000
#define XP_ROYALTY_QUEST_4      6000

#define SHIELD GROUP    0
#define SHIELD_BIT      7
#define SHIELD_XP    1000

#define XP_MONK_QUEST 750

#define SWORD_QUEST          2
#define XP_SWORD_QUEST_1  9000
#define XP_SWORD_QUEST_2  1500
#define XP_SWORD_QUEST_3 12000
#define XP_SWORD_QUEST_4  1500
#define XP_SWORD_QUEST_5  1000
#define XP_SWORD_QUEST_6 12000
#define XP_SWORD_QUEST_7  5000
#define XP_SWORD_QUEST_8 42250

#define CHALICE_QUEST       2
#define XP_CHALICE_QUEST  500

#define STAFF_QUEST       2
#define XP_STAFF_QUEST  300

#define WAT_GRP         0
#define WAT_BRE_BIT     11

#define PIRATE_GUILD       12

#define PET_GROUP               0
#define PET_BIT                 9
#define PET_XP                250

#define OAK_GROUP               0
#define OAK_BIT                10
#define OAK_XP               1250
