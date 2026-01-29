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
        "delivery": ({"delivery office"}),
        ]);

    coords = ([
        "shop": ({16,3}),
        "post": ({9,2}),
        "pub": ({14,8}),
        "bank": ({11,2}),
        "bladesmith": ({8,8}),
        "blacksmith": ({10,6}),
        "warrior crafthall": ({13,6}),
        "tracker crafthall": ({4,8}),
        "harbour master": ({10,8}),
        "fishmonger": ({17,8}),
        "adventurer's guild": ({10,2}),
        "town hall": ({9,4}),
        "jail": ({18,2}),
        "delivery": ({11,8}),
		]);

    area_name = "Port Macdunn";
    global_coords = VILLAGE_COORDS;
}
