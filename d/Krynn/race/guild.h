/* The include file for the guild specific things */
/* Aridor 12/96 */

#include "local.h"


#define GUILD_NAME          "The Krynn race guild"
#define KRYNN_RACE_SUBLOC   "krynn_race_subloc"
#define MEMBER(x)           ((x)->query_guild_name_race() == GUILD_NAME)

#define RACE_SHADOW         (KRGOBJ + "race_shadow")
#define KRYNN_RACE_SOUL     (KRGOBJ + "race_soul")

#define JOINPATH            (KRGLOG + "joined")
#define LEAVEPATH           (KRGLOG + "left")

#define DEFAULT_TITLE       "of Krynn"
#define DEFAULT_REGION      "krynnish being"

#define HELP_DIR            KRGDIR + "help/"


#define SUBLOC_MISCEXTRADESC 	"_subloc_misc_extra"
#define MISC_SUBLOC             ("/cmd/live/state")
