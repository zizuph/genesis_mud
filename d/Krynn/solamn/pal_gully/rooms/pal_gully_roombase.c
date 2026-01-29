/* 
 * The base indoor room for gully dwarves in caves past the moors
 * west of Palanthas.
 * Mortis 03.2015
 */
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include CLOCKH

/* Inherit the Ansalon room */
inherit R_FILE
inherit RDIR + "acave_tells.c";

#define CREATE "create_pal_gully_room"
#define RESET  "reset_pal_gully_room"

string smell_air(string str);

/*
 * This function is called from the main Krynn room. It checks
 * whether or not the room should be reset.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
	return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);

    add_item(({"walls", "wall", "the walls", "the wall"}), "Roughly hewn "
        + "using rudimentary tools, the walls are covered "
        + "in filth and muck from the ground.\n");
    add_item(({"lanterns","oil lantern","lantern", "oil lanterns",
	    "light", "lights", "lamps", "lamp"}),
        "Small and poorly made, these oil lanterns are attached to "
        + "the wall to provide light throughout the mine. They must be "
        + "manually filled by hand and seem to be tended to dutifully.\n");
    add_item(({"filth","muck","refuse", "garbage","mound",
	    "mounds", "scraps", "foodscraps", "scrap", "food scrap","bits",
		"bone", "bits of wood", "bits of bone", "bits of wood and bone",
		"dump","food","pile","piles"}),
		"Piles of food scraps, filth, muck, bits of wood and bone, "
		+"and other discarded items are strewn haphazardly all over the "
		+"floor. It is almost as if someone had been using this space as "
		+"a refuse dump.\n");
    add_item(({"ceiling", "ceilings", "beams", "thick wood", 
        "pieces of wood", "wood"}), "Average ceilings that are held up by beams "
        + "of thick wood to keep from collapsing. The wood is rotting, but "
        + "sturdy, and appears to have been repaired recently.\n");
    add_item(({"floor", "floors"}), "The floors of the cavern are covered "
        + "in muck and filth. Walking here not only stinks, but it "
        + "squishes underfoot.\n");
    
    set_tell_time(90);
    add_tell("@@get_tells@@" + "\n");
    
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_S_MAP_FILE, "pal_gully.txt");
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

int
smell_air(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area" && str != "garbage"   && str != "refuse")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them subtly before turning green and gagging.");
    write("You smell the air around you and immediately feel sick from the "
	+"putrid air. You feel yourself gag.\n");
    return 1;
}


public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}