/*
 *  NCAMP_ROOM + "dock6.c"
 *
 *  A dock. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 22 November 2002
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
    set_short("a small dock on the Anduin");
    set_long(&long_desc());

    sky_add_items();
    dock_add_items();
    add_dock_tells();

    add_item(({"room", "area", "surroundings", "place", 
        "dock"}), long_desc);
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 0;

    add_exit(NCAMP_ROOM + "camp21.c", "west");

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
    return "You have stepped out onto a small dock built along "
        + "the west bank of the mighty river Anduin. The strong "
        + "current of the river rocks the dock back and forth."
        + sky_desc() 
        + " Several crude rafts have been moored to the dock, "
        + "and any watercraft that might have been stored here "
        + "by the settlers have been cut loose and sunk. Leaving "
        + "the dock will take you west, where many huts now "
        + "lie in smoking ruins.\n";
}
