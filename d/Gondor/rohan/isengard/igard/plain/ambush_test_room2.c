/*
 *  IGARD_PLAIN + "ambush_test_room.c"
 *
 *  Testing out the ambush traps.
 *
 *  Last modified by Alto, 30 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "plain_funcs.c";

public void        create_gondor();
public string      long_desc();
public int         spring_trap();
public int	        catch_all(string str);

int distance = 3;
static object  Squad;

public void
create_gondor()
{
    set_short("A room for testing out the ambush code.");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    add_plain_tells();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_PLAIN  + "ambush_test_room.c",          "north");

    reset_room();
}


string
long_desc()
{
    return "This is a room built specifically to test out the ambush code "
      + "on the plain of Isengard." + sky_desc() + plain_tower_desc(distance)
      + "\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
     start_room_tells();

}

/* Note to self: make this a switch based upon player stat size
 * so that different sized teams ambush them.
 * Also need to stick a property on the player that will keep them
 * from exiting the room.
 *
 */
public void
spring_trap()
{
    if (!objectp(Squad))
    {
        Squad = clone_object(IGARD_NPC + "igard_ambush_uruk.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("say Aha! A spy!\n");
        Squad->ambush_retreat();
    }
}

public int 
catch_all(string str)
{
    string  vb = query_verb();

    if (!AMBUSHED) 
        return 0;
    
    switch (vb)
    {
    case "north":
    case "northeast":
    case "northwest":
    case "southwest":
    case "southeast":
    case "west":
    case "up":
    case "down":
    case "south":
    case "east":
        WRITE("You cannot seem to break away!");
        return 1;
        break;
    default:
        return 0;
    }
}
