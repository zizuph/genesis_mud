/*
 * On the roof of the AG in Bree.
 * 
 * Raymundo, Jan 2020
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit "/d/Shire/std/room.c";



void
create_shire_room()
{
	set_short("On the roof of the Adventurer's Guild in Bree");
	set_long("You stand on the roof of the Adventurer's Guild "
		+ "in Bree. You notice an open window here leading, "
		+ "presumably, into the attic. The roof has a steep "
		+ "pitch peaking at the exact center of the building, "
		+ "on top of which is a weathervane.\n");
		
	add_item("roof", "The roof is covered in cedar shingles. It "
		+ "has a very steep pitch. On the south side of the roof, "
		+ "a window extends out. It is open.\n");
	add_item( ({"shingle", "shingles", "cedar shingle", "cedar shingles"}),
		 "The shingles have been cut from cedar.\n");
	add_item( ({"window", "windows"}), "The window leads into the attic. "
		+ "It's open.\n");
	add_item( ({"weathermane", "weathervane"}), "The weathervane looks "
		+ "like a rooster standing on an arrow. It points east, "
		+ "because that's the direction the wind is blowing.\n");
	add_cmd_item( ({"window", "windows"}), ({"close", "shut"}), "The "
		+ "window must be open for a reason. You wouldn't feel right "
		+ "closing it!\n");
	add_cmd_item( ({"window", "windows"}), "enter", "@@enter_window@@");
	add_cmd_item( ({"weathermane", "weathervane"}), ({"take", "get"}),
		 "The weathervane is securely attached to the roof!\n");
	add_cmd_item( ({"path", "down path", "down to path", "down"}), "jump",
		 "No! You don't dare! You'd hurt yourself, or worse, damage "
		+ "your armours!\n");
	add_item( ({"street", "road"}), "Down below you see the streets "
		+ "of Bree.\n");
	add_item( ({"path", "paths"}), "Looking back you see the path "
		+ "you followed to get here. It's probably a bit too far "
		+ "to jump down to, though.\n");
	
    add_exit(ROAD_DIR + "path3", "down");
	remove_prop(ROOM_I_INSIDE);

    reset_shire_room();
}



void
reset_shire_room()
{

}

int
enter_window()
{
	write("You enter the attic through the window!\n");
	say(QCTNAME(TP) + " enters the attic through the window!\n");
	tell_room( (ROAD_DIR + "attic1"), QCTNAME(TP) + 
		" arrives through the open window.\n");
	TP->move_living("M", ROAD_DIR + "attic1");
	return 1;
}
