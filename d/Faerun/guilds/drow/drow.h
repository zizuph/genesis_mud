/*
 * - drow.h
 *
 * This file should be inherited by any drow-based guilds.
 * It should only contain basic defines that may be exported
 * to the rest of the domain without issue.
 */
#ifndef __FAERUN_DROW_GUILDS__
#define __FAERUN_DROW_GUILDS__

#include "/d/Faerun/defs.h"

/*
 * Guild names for the Drow guilds.
 * Use these to determine if someone is a member
 * or not.  (player->query_guild_name_race() == DROW_R_GUILD)
 */
#define DROW_R_GUILD    "Drow of Underdark"
//#define DROW_R_GUILD    "Racial Drow"
#define DROW_L_GUILD    "Layman Drow"
#define IS_MEMBER(p) ((p)->query_guild_name_race() == DROW_R_GUILD)


/*
 * Defines to the guild servers, should they be necessary
 * for some reason.
 */
#define DROW_R_SERVER   (P_DROW_RACIAL + "server")
#define DROW_L_SERVER   (P_DROW_LAYMAN + "server")

/*
 * Defines to members' guild objects.
 */
#define DROW_R_OBJECT   "drow::racial::object"
#define DROW_L_OBJECT   "drow::layman::object"

/*
 * Defines for paths
 */
#define DROW_DIR        "/d/Faerun/guilds/drow/"
#define ARM_DIR         (DROW_DIR + "arm/")
#define BOARD_DIR       (DROW_DIR + "boards/")
#define BOARD_LA_DIR    (BOARD_DIR + "lay")
#define BOARD_PU_DIR    (BOARD_DIR + "public")
#define BOARD_RA_DIR    (BOARD_DIR + "race")
#define CITIES_DIR      (HELP_DIR + "cities/")
#define DEITY_DIR       (HELP_DIR + "deities/")
#define HELP_DIR        (DROW_DIR + "race/help/")
#define JOIN_DIR        (HELP_DIR + "join/")
#define OBJ_DIR         (DROW_DIR + "obj/")
#define ROOMS_DIR       (DROW_DIR + "rooms/")
#define SPELLS_DIR      (DROW_DIR + "spells/")
#define SHADOWS_DIR     (DROW_DIR + "shadows/")
#define WEP_DIR         (DROW_DIR + "wep/")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")


#endif  __FAERUN_DROW_GUILDS__
