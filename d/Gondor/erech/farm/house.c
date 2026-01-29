/*
 * house.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "inside.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#include TERRAIN_TYPES

#define CHAIR_NAME "table"

/* Globale variables */
object ob;

/* Prototypes */
public void         create_gondor();
public void         leave_inv(object ob, object dest);
public string       look_at(string arg);

/*
 * Function name:    create_gondor()
 * Definition   :    Creates the room.
 */
public void
create_gondor()
{
    set_short("A Gondorian house.");
    set_long("You stand inside a Gondorian house. This is the kitchen " +
        "and living room of the house, and is much used. A large door " +
	"leads to the yard and a smaller door leads to the garden. The " +
	"house is old, but well maintained.\n");

    add_chair(CHAIR_NAME, "[down] [behind] [the] 'table'", 3, "behind");
    add_item("table", &look_at(CHAIR_NAME));

    add_item( ({"door","doors"}), "What door do you want to examine? " +
        "The large or the small one?\n");
    add_item(({"small door", "red door"}), "This is a small door leading " +
        "to the garden. The door is painted red.\n");
    add_item(({"large door", "green door"}), "This large door leads to " +
        "the front yard. The door is painted green.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(E_FARM + "yard.c", "south", 0, 3, 0);
    add_exit(E_FARM + "garden.c", "west", 0, 3, 0);

    reset_room();

}

void
reset_room()
{
    if (!present("cat"))
    {
        ob=clone_object(E_NPC + "fcat");
	ob->move(this_object());
    }
    if (!present("plate"))
    {
	ob=clone_object(E_OBJ + "fplate");
	ob->set_filled("water");
	ob->move(this_object());
    }
}

public void
init()
{
    ::init();
    init_room_chairs();
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

public string
look_at(string arg)
{
    switch(arg)
    {
    case CHAIR_NAME:
        return "The table is large and made from solid wood. Some seats " +
  	    "are set around the table. " + 
            sitting_on_chair(CHAIR_NAME, this_player(), 0) + "\n";
    }
}
