/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*
 * Local definitions file.                              ~solace/puzzle/defs.h *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*
 * All code in this and the tributary directories by and copyright Mucalytic. *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#include "../../mucalytic/master_defs.h"

/* Area directory paths. */

#define P_STD		PUZZLE_QUEST + "std/"
#define NPCS		PUZZLE_QUEST + "npcs/"
#define MISC		PUZZLE_QUEST + "misc/"
#define DOORS		PUZZLE_QUEST + "doors/"
#define ARMOUR          PUZZLE_QUEST + "armour/"
#define OBJECTS		PUZZLE_QUEST + "objects/"
#define WEAPONS		PUZZLE_QUEST + "weapons/"
#define LOCATIONS	PUZZLE_QUEST + "locations/"
#define CREATURES	PUZZLE_QUEST + "creatures/"

/* Standard room definitions. */

#define ROOM_DEFS	P_STD + "puzzle_room"

/* Link room from the entrance. */

#define LINK_ROOM	DOMAIN + "solace/guild/shop"

/* Key numeral definitions. */

#define CAGE_KEY        507

/* Quest group and bit definitions. */

#define BIT             15
#define GROUP           3

/* Properties. */

#define PLAYER_I_COMPLETED_PUZZLE_QUEST "_player_i_completed_puzzle_quest"

/* Standard exit commands. */

#define CENTRAL_ROOMS ({ "takhisis", "zeboim", "hiddukel", "paladine", \
			 "morgoin", "nuitari", "chemosh", "lunitari",  \
			 "solinari"				       })

#define EXIT_CMDS ({ "u", "d", "n", "s", "e", "w", "ne", "nw", "se", "sw", \
                     "up", "down", "north", "south", "east", "west",       \
                     "northeast", "northwest", "southwest", "southeast"    })

#define ROOM_OPPOSITES ({ ({	"east",		"west"		}),	\
			  ({	"west",		"east"		}),	\
			  ({	"north",	"south"		}),	\
			  ({	"south",	"north"		}),	\
			  ({	"northeast",	"southwest"	}),	\
			  ({	"southwest",	"northeast"	}),	\
			  ({	"northwest",	"southeast"	}),	\
			  ({	"southeast",	"northwest"	})	})

