/*
 *  NCAMP_ROOM + "camp3.c"
 *
 *  A dirt path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 17 November 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        create_gondor();
public string      long_desc();

static object *Man = allocate(2);
static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("in the western part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"woods", "woodland", "stand"}), "A dense stand "
        + "of trees grows to the west of the settlement.\n");
    add_item(({"hut", "shabby hut" }), "There is a very shabby "
        + "looking hut here, even by the standards of the rather "
        + "shabby looking settlement. Many boards are loose from "
        + "its roof, and the door hangs from only one hinge.\n");
    add_item(({"door", "hinge"}), "The door to the hut looks as "
        + "if it were kicked in by extreme force. From the looks "
        + "of things, however, this may have occurred long ago.\n");
    add_item(({"tower", "large tower", "watchtower"}), "The tall "
        + "structure rising above the huts to the east appears "
        + "to be some kind of watchtower. You would need to move "
        + "east to see it more clearly.\n");
    add_item(({"rooftop", "rooftops"}), "Looming over the tops "
        + "of the eastern huts stands a large watchtower.\n");

        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "camp4.c", "north");
    add_exit(NCAMP_ROOM + "camp2.c", "northwest");
    add_exit(NCAMP_ROOM + "camp7.c", "east");
    add_exit(NCAMP_ROOM + "camp8.c", "south");
    add_exit(NCAMP_ROOM + "hut3.c", "enter", 0, 0, 1);
    
    defence_status = 1;

    reset_room();
}

public void
reset_room()
{
    if(defence_status)
    {
    clone_npcs(Man, NCAMP_NPC + "ncamp_human_male", -1.0);
    return;
    }

    clone_npcs(Orc, NCAMP_NPC + "ncamp_orc", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}

string
long_desc()
{
    return "You have reached the western edge of the settlement "
        + "proper. Numerous huts lie nestled closely together, some "
        + "with smoke pouring from the windows. A tower of some sort "
        + "looms over the rooftops to the east."
        + sky_desc() 
        + " There is a particularly shabby hut nearby which you "
        + "could probably enter.\n";
}
