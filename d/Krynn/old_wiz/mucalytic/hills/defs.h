/* Definitions file contains all necessary def procs. Mucalytic. */

#include "../master_defs.h"

/* Directory definitions. */

#define ARMOUR		HILLS + "armour/"
#define CREATURES	HILLS + "creatures/"
#define DATA		HILLS + "data/"
#undef GUILD
#define GUILD		HILLS + "guild/"
#define LOCATIONS	HILLS + "locations/"
#define MISC		HILLS + "misc/"
#define NPCS		HILLS + "npcs/"
#define OBJECTS		HILLS + "objects/"
#define WEAPONS		HILLS + "weapons/"

#define HILL_CONTROL	HILLS + "hill_control"

/* Other directories. */

#undef OUTSIDE
#define OUTSIDE		SHAANGSEI + "outside/"
#define HELP_FILES	OPEN + "language_help_files/"

/* String definitions. */

#define LANGUAGE_GUILD  "Secret Signaller's Guild"

/* This is the order in which the fog bank enters and recedes from the hills. */

#define ORDER ({ ({ "path23", "path24", "path27" }), \
                 ({ "path25", "path22", "path26", "path21", "path30" }), \
                 ({ "path19", "path18", "path20", "path28" }), \
                 ({ "path29", "path17", "path16" }), \
                 ({ "path10", "path7",  "path15", "path14" }), \
                 ({ "path12", "path9",  "path8",  "path5",  "path13" }), \
                 ({ "path11", "path3",  "path2",  "path4",  "path6"  }), \
                 ({ "path1" }) })
