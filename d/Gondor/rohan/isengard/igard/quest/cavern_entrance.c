/*
 *  IGARD_QUEST + "cavern_entrance.c"
 *
 *  Entrance to caverns for Isengard Quest.
 *
 *  Last modified by Alto, 26 December 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();
public int         crawl_space();

object             actor;

string
long_desc()
{
    return "You stand before the large entrance to a cavern. The stone "
        + "here is unlike any you have seen in the region of Isengard, "
        + "flecked with glimmering obsidian crystals. The entrance itself "
        + "is blocked with numerous fallen boulders, although you can "
        + "detect a faint flickering of light through the small spaces "
        + "between them.\n";
}


public void
create_gondor()
{
    set_short("Before the entrance to a cavern");
    set_long(long_desc());

    sky_add_items();
    outside_add_items();

    add_item(({"room", "area", "surroundings", "place", "landscape"}), 
        long_desc());

    add_item(({"entrance", "cave", "cavern"}), "The cavern opens here "
        + "through a large gaping entrance. A recent shifting of the earth "
        + "has caused numerous heavy boulders to fall across the entrance, "
        + "blocking your passage.\n");
    add_item(({"boulder", "boulders", "fallen boulder", "fallen boulders",
        "heavy boulder", "heavy boulders"}), "The boulders blocking the "
        + "entrance to the cavern are far too heavy to move, yet you can "
        + "see the faint flickering of light through the spaces between "
        + "the boulders. Perhaps you could crawl through them.\n");
    add_item(({"space", "spaces", "space between boulders",
        "spaces between boulders"}), "Some of them look big enough to "
        + "crawl through.\n");        
    add_item(({"stone"}), "The stone around the entrance to the cavern is "
        + "flecked with glimmering obsidian crystals.\n");
    add_item(({"crystals", "crystal", "obsidian crystals", "obsidian crystal",
        "glimmering crystal", "glimmering crystals"}), "The crystals around "
        + "the entrance to the cavern are obsidian and glimmer under the sky.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_PLAIN  + "west_road1.c",           "east");

    add_cmd_item(({"space", "spaces", "through space", "through spaces",
        "between boulders", "through boulders"}), "crawl", &crawl_space());

    reset_room();
}


public void
reset_room()
{
}


int
crawl_space()
{
    actor = TP;

    if (!SIC)
    {
        set_alarm(0.0, 0.0, &write("You cannot seem to find a space "
            + "wide enough to crawl through.\n"));
        return 1;
    }

    write("You squeeze between a space in the "
        + "boulders that seems large enough to crawl through.\n");
    tell_room(environment(actor), QCTNAME(actor) + " crawls between "
        + "a space in the boulders.\n", 
        ({actor}));
    tell_room(IGARD_QUEST + "cavern.c", QCTNAME(TP)
        + " arrives crawling between the boulders.\n");
    TP->move_living("M", IGARD_QUEST + "cavern.c", 1, 0);

    return 1;
}


