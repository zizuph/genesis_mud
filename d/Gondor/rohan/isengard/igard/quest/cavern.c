/*
 *  IGARD_QUEST + "cavern.c"
 *
 *  Cavern for Isengard Quest.
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
static object *Orc     = allocate(1);

string
long_desc()
{
    return "You are standing inside a pocket of space between and beneath "
        + "numerous massive boulders. The entrance to the cavern "
        + "is blocked on both sides by the fallen boulders, although you can "
        + "detect some light through the small spaces between them.\n";
}


public void
create_gondor()
{
    set_short("Beneath numerous fallen boulders");
    set_long(long_desc());

    add_item(({"room", "area", "surroundings", "place", "pocket"}), 
        long_desc());

    add_item(({"entrance", "cave", "cavern"}), "A recent shifting of the earth "
        + "has caused numerous heavy boulders to fall across the entrance, "
        + "blocking your passage further in or out.\n");
    add_item(({"boulder", "boulders", "fallen boulder", "fallen boulders",
        "heavy boulder", "heavy boulders"}), "The boulders blocking the "
        + "entrance to the cavern are far too heavy to move, yet you can "
        + "see some light through the spaces between "
        + "the boulders. Perhaps you could crawl through them and escape.\n");
    add_item(({"space", "spaces", "space between boulders",
        "spaces between boulders"}), "Some of them look big enough to "
        + "crawl through.\n");        

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_HIDE, -1);

    add_cmd_item(({"space", "spaces", "through space", "through spaces",
        "between boulders", "through boulders"}), "crawl", &crawl_space());

    reset_room();
}


public void
reset_room()
{
    clone_npcs(Orc,    IGARD_NPC + "i_quest_orc.c",  -1.0);
}


int
crawl_space()
{
    actor = TP;

    write("You squeeze between a space in the "
        + "boulders that seems large enough to crawl through.\n");
    tell_room(environment(actor), QCTNAME(actor) + " crawls between "
        + "a space in the boulders.\n", 
        ({actor}));
    tell_room(IGARD_QUEST + "cavern_entrance.c", QCTNAME(TP)
        + " arrives crawling between the boulders.\n");
    TP->move_living("M", IGARD_QUEST + "cavern_entrance.c", 1, 0);

    return 1;
}


