/*******************************************************************\
| DEFS.H                                                            |
\*******************************************************************/

#define S_DOMAIN                "sparkle"

#define S_DOMAIN_DIR		"/d/Sparkle/"

#define S_DOMAIN_LIB_DIR        (S_DOMAIN_DIR + "lib/")
#define S_DOMAIN_LOG_DIR        (S_DOMAIN_DIR + "log/")
#define S_DOMAIN_STD_DIR	(S_DOMAIN_DIR + "std/")
#define S_DOMAIN_SYS_DIR	(S_DOMAIN_DIR + "sys/")
#define S_DOMAIN_VAR_DIR        (S_DOMAIN_DIR + "var/")
#define S_DOMAIN_AREA_DIR	(S_DOMAIN_DIR + "area/")
#define S_DOMAIN_CLUBS_DIR      (S_DOMAIN_DIR + "clubs/")
#define S_DOMAIN_GUILD_DIR      (S_DOMAIN_DIR + "guilds/")
#define S_DOMAIN_PIERS_DIR      (S_DOMAIN_DIR + "piers/")
#define S_DOMAIN_START_DIR      (S_DOMAIN_DIR + "start/")
#define S_DOMAIN_COMMON_DIR	(S_DOMAIN_DIR + "common/")

#define S_LOG_BOARD_DIR         (S_DOMAIN_LOG_DIR + "board/")

#define S_STD_OBJ_DIR		(S_DOMAIN_STD_DIR + "obj/")
#define S_STD_ROOM_DIR		(S_DOMAIN_STD_DIR + "room/")

#define S_VAR_BOARD_DIR         (S_DOMAIN_VAR_DIR + "board/")

#define S_COMMON_NPC_DIR	(S_DOMAIN_COMMON_DIR + "npc/")
#define S_COMMON_OBJ_DIR	(S_DOMAIN_COMMON_DIR + "obj/")
#define S_COMMON_WEP_DIR	(S_DOMAIN_COMMON_DIR + "wep/")
#define S_COMMON_HELP_DIR	(S_DOMAIN_COMMON_DIR + "help/")
#define S_COMMON_ROOM_DIR	(S_DOMAIN_COMMON_DIR + "room/")

// Logs

#define S_LOG_DEBUG_FILE        (S_DOMAIN_LOG_DIR + "debug")
#define S_LOG_QUEST_FILE        (S_DOMAIN_LOG_DIR + "quest")

// Includes

#define S_DOMAIN_SYS_LINKS              "/d/Sparkle/sys/links.h"
#define S_DOMAIN_SYS_CONFIG		"/d/Sparkle/sys/config.h"
#define S_DOMAIN_SYS_QUESTS             "/d/Sparkle/sys/quests.h"
#define S_DOMAIN_SYS_MASTERS		"/d/Sparkle/sys/masters.h"

// Libraries

#define S_LIB_TEXT                      (S_DOMAIN_LIB_DIR + "libs_text")
#define S_LIB_CLOCK                     (S_DOMAIN_LIB_DIR + "libs_clock")
#define S_LIB_OBJECT                    (S_DOMAIN_LIB_DIR + "libs_object")
#define S_LIB_PLAYER                    (S_DOMAIN_LIB_DIR + "libs_player")
#define S_LIB_LOGGING                   (S_DOMAIN_LIB_DIR + "libs_logging")
#define S_LIB_DEVELOPMENT               (S_DOMAIN_LIB_DIR + "libs_development")

// Ancestors

#define S_BASE_ROOM                     (S_STD_ROOM_DIR + "room")
#define S_BASE_BOARD                    (S_STD_OBJ_DIR + "board")

// Boards

#define S_DOMAIN_BOARD                  (S_COMMON_OBJ_DIR + "board_domain")
#define S_DOMAIN_BOARD_DIR              (S_VAR_BOARD_DIR + "domain")

//--------------------------------------------------------------------------
// Common definitions

#ifndef FALSE
#define FALSE           0
#define TRUE            1
#endif

#ifndef NULL
#define NULL            0
#endif

#define BIT(i)          (1 << (i))
#define ALLONES         (~0)

#define S_TERMINAL_WIDTH        80
#define S_TERMINAL_LENGTH       25

//--------------------------------------------------------------------------
// Common library shortcuts

#define TO              this_object ()
#define TP              this_player ()
#define TI              this_interactive ()

#define S_IS_DIR(sPath) (file_size (sPath) == -2)
#define S_IS_FILE(sPath) (file_size (sPath) >= 0)

#define S_LOAD(sObj) \
  { S_FIXUID; (sObj)->get_this_object (); }

#define S_FIXUID \
  { setuid (); seteuid (getuid (this_object ())); }

//--------------------------------------------------------------------------
// Common library constants

#define MOVE_SUBLOC_ALWAYS      1

//--------------------------------------------------------------------------

