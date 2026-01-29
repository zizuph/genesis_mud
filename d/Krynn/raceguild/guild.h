/* The include file for the guild specific things */
/* Aridor 12/96 */

#include "local.h"


#define GUILD_NAME          "Krynn race guild"
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

/* Some races may be allowed to hide their subloc description. */
#define ALLOW_SUBLOC_HIDING
#define RACE_HIDER_NAME         "_krynn_race_hider_"
#define RACE_HIDER_OBJ          (KRGOBJ + "race_hider")
