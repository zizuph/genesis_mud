/*
 * Northern side of the Haradrim camp
 * -- Finwe, July 2005
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Haradrim = allocate(1 + random(2));

public void
create_camp()
{
    set_short("A well travelled road in the Ithilien forest");
    set_long("The road travels south into the forest from stonelaid road " +
        "north of here. It is wide and cleared of vegetation and looks " +
        "well used. A foul stream passes before you.\n");
    add_item("forest", 
        "The forest extends in all directions, hiding all activity and " +
        "muffling the sounds.\n");
    add_item(({"tents", "tent"}),
        "They are square shaped and nicer than most. They line the paths " +
        "and appear in better condition than most.\n");
    add_item("road",
	    "The path leads heads south into the forest. It seems to be well " +
        "used.\n");
    add_item(({"stream", "foul stream"}),
        "The stream looks foul, and smells horrid. It runs east and west.\n");

    add_exit(ITH_DIR+"road/er6", "north", 0);
    add_exit(ITH_DIR+"forest/haradpath2", "south", 0);

    reset_room();

//    add_harad_camp_tells();
}

public void
reset_room()
{
    ::reset_room();
//    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
