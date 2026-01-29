/*
 * information.c
 *
 * This is a module which contains information on the
 * location of various places of interest in the village
 * of Port Macdunn, like shops or the town hall.
 *
 *
 * Khail - August 1, 1997
 */
#pragma strict_types
#pragma no_clone

#include "/d/Khalakhor/sys/paths.h"
#include "village.h"

inherit INFO_BASE;

public void
create_info()
{
    options = ([
        "smith": ({"blacksmith", "bladesmith"}),
        "crafthall": ({"warrior crafthall",
                       "tracker crafthall"}),
        "guild": ({"warrior crafthall",
                   "tracker crafthall",
                   "adventurer's guild"}),
        ]);

    aliases = ([
        "shop": ({"shop", "store"}),
        "post": ({"post", "post office"}),
        "pub": ({"pub","tavern","inn","bar"}),
        "bank": ({"bank","gnome deposit"}),
        "bladesmith": ({"bladesmithy","bladesmith forge"}),
        "blacksmith": ({"blacksmithy","blacksmith forge"}),
        "warrior crafthall": ({"warrior crafthall"}),
        "tracker crafthall": ({"tracker crafthall"}),
        "harbour master": ({"harbour master"}),
        "fishmonger": ({"fishmonger"}),
        "adventurer's guild": ({"adventurer's guild",
                                "adventurers guild",
                                "adventurer guild"}),
        "town hall": ({"town hall"}),
        "jail": ({"jail", "prison", "jail house"}),
        ]);

    coords = ([
        "pub": ({15,10}),
        "bank": ({11,9}),
        "blacksmith": ({15,5}),
        "inn": ({3,8}),
        ]);

    area_name = "Abhainn Ruith";
    global_coords = VILLAGE_COORDS;
}
