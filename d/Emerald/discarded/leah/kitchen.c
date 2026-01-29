inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
add_prop(ROOM_I_INSIDE, 1);
	set_short("Kitchen in Elven House");
	set_long("   You are standing in the kitchen of the elven "+
		"house. It looks like a typical kitchen. In the center "+
		"of the room is a large table, and off in the corner is "+
		"a large cookstove. Above the stove you see a note. Off "+
		"to the north you see a storeroom, and to the east a "+
		"dining room.\n\n");

	add_item(({"table", "pots", "pots and pans", "pans"}), "The table "+
		"if littered with pots and pans.\n");
	add_item(({"cookstove", "stove"}), "It is a normal stove used "+
		"for cooking.\n");
	add_item("storeroom", "The doorway is dark. To see more you will "+
		"have to go into the room.\n");
	add_item("dining room", "The dining room is off to the east.\n");
	add_item(("stove"), "Its a rather basic stove. Despite its age, "+
		"it has been well looked after, and looks ideal for "+
		"cooking a meal on.\n");
	add_item("note", "There is writing on it. Perhaps you should "+
		"read it.\n");

	add_exit(VILLAGE_DIR + "foyer", "south");
	add_exit(VILLAGE_DIR + "storeroom", "north");
	add_exit(VILLAGE_DIR + "diningroom", "east");
}

void
init()
{
    ::init();
    add_action("read", "read");
}

int
read(string arg)
{
    notify_fail("Read what?\n");
    if (arg != "note")
	return 0;
    write("The note reads:\n"+
      " bread\n"+
      " milk\n"+
      " jam\n\n"+
      "Sounds like a shopping list.\n");
    return 1;
}
