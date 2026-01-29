/*
 * /d/Gondor/anorien/osgiliath/boatplace.c
 *
 * Original version by Elessar
 *
 * Modification log:
 *  3-Dec-1996, Olorin: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

// Prototypes
public string  long_func();
public void    add_boat();
public string  exa_ground();

public void
create_room()
{
    set_short("on the western riverbank of the mighty Anduin river");
    set_long(long_func);
    add_item( ({"river", "anduin", }), 
	"The river Anduin is a great river, quite wide at this point, and "
      + "long: It runs through large parts of Rhovanion, and through Gondor on "
      +	"its way to the sea.\n");
    add_item(({"bushes","shrubs"}),
	"Bushes and shrubs is all you see on the far side of the river.\n");
    add_item(({"ground","marks"}), exa_ground);
    add_exit(OSG_DIR + "wosg4",  "north", 0, 2);
    add_exit(OSG_DIR + "wbank1", "south", 0, 2);
    BEACH
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_boat();
}

public string
long_func()
{
    string longstr =
	"You are standing on the western riverbank of the River Anduin. "
      + "The river flows quietly past on its way south to the sea. Looking "
      + "across the river, you see nothing but flat, grassy fields.";
    if (!present("boat",TO))
	longstr += " You spot some marks in the muddy ground.\n";
    else 
	longstr += " There is a small wooden rowing boat here.\n";
    return longstr;
}

public void
add_boat()
{
    seteuid(getuid(TO));
    clone_object(OBJ_DIR + "boat_obj")->move(TO);
}

public string
exa_ground()
{
    string desc = "The ground is muddy, with a few sparse grass halms growing here.";
    if (!present("boat",TO))
	desc += " You can see some marks in the mud. It looks as if " +
	    "someone has pulled a small boat into the Anduin here. " +
	    "There are some footsteps, too, but you cannot make out more.\n";
    else
	desc += " From the small boat, some tracks go to the Anduin. " +
	    "It looks like someone recently pulled the boat from the river " +
	    "up the shore.\n";
    return desc;
}
