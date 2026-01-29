/*
* /d/Shire/trickster/trickster.h
*
* Some definitions for the Trickster layman guild
*/


#ifndef TRICKSTER_DEFINITIONS
#define TRICKSTER_DEFINITIONS

//  Locks
// Disabled until converted over to the standardised special
// system.
#define NO_TRICKSTER_SHINKICK 1

#ifndef TRICK_DIR
#define TRICK_DIR "/d/Shire/trickster/"
#endif
#define TRICK_HELP (TRICK_DIR + "help/")

#define TRICK_OBJECTS_DIR      (TRICK_DIR + "obj/")

#define TRICK_GUILD_TRAINER (TRICK_DIR + "train")

#define TRICKSTER_GUILD_SHADOW (TRICK_DIR + "trick_shadow")

#define TRICKSTER_GUILD_SOUL   (TRICK_DIR + "trick_soul")

#define TRICKSTER_GUILD_OBJ   (TRICK_DIR + "stick")

#define TRICKSTER_GUILD_LOG    "/d/Shire/log/trickster"

#define TRICKSTER_GUILD_ACCEPT_LOG (TRICK_DIR + "accept")

#define TRICKSTER_GUILD_FAIL_LOG   (TRICK_DIR + "failedaccept")

// #define TRICKSTER_GUILD_TAX    7
// Trickster tax reduced as shinkick disabled until converted to
// standardised special system.
#define TRICKSTER_GUILD_TAX    5

#define TRICKSTER_GUILD_NAME   "Tricksters"

#define TRICKSTER_GUILD_STYLE  "ranger"

#define TRICKSTER_GUILD_TYPE   "layman"

/* undefine this if you want the align restriction to kick members out */
#define TRICKSTER_NO_ALIGN_RESTRICTION

#define TRICKSTER_GUILD_ALIGN_MIN   -600

#define TRICKSTER_GUILD_ALIGN_MAX    600

#define TRICKSTER_GUILD_MASTER ({"Igneous"})

#define IS_MEMBER(p) ((p)->query_guild_name_lay() == TRICKSTER_GUILD_NAME)

#define TRICKSTER_STRING_PROP   "_i_have_placed_a_string_on_something"
#define TRICKSTER_TRAP_TYPE  "_live_s_trickster_trap_type"

#define TRICKSTER_NEWS TRICK_HELP + "news"

//  Guild member tracking defines
#define  MEMBER_TRACKER  "/d/Shire/trickster/tracker.c"
#define  MEMBER_SAVE     TRICK_DIR + "members"
#define HEX           TRICK_OBJECTS_DIR +"hex_shadow"
#define HOTFOOT       TRICK_OBJECTS_DIR +"hot_foot"
#define STRING_TRICK  TRICK_OBJECTS_DIR +"string_shadow"
#define ITCH_OBJ      TRICK_OBJECTS_DIR +"itchy_scratchy"
#define SNEEZE_OBJ    TRICK_OBJECTS_DIR +"sneezy"
#define STINK_OBJ     TRICK_OBJECTS_DIR +"stinky"
#define LAUGH_OBJ     TRICK_OBJECTS_DIR +"laughgas"
#define SMOKE_OBJ     TRICK_OBJECTS_DIR +"smokebomb"
#define TRICK_ARMOUR  TRICK_OBJECTS_DIR +"trick_armour_shadow"
#define DISGUISE      TRICK_OBJECTS_DIR +"disguise"
#define DISGUISE_KIT  TRICK_OBJECTS_DIR +"disguise_kit"
/* No definitions below this line */
#endif TRICKSTER_DEFINITIONS
