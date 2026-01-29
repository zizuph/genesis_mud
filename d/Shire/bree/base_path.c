/*
 * Base file for roads and gates in Bree
 * Finwe, June 2001
 *
 * Stolen for the path behind the adventurer's guild.
 * Raymundo, Jan 2020
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit "/d/Shire/bree/base_common";
 


void create_path_room() {}


public void
create_area_room()
{

    set_area("near the Adventurer's");
    set_areaname("Guild");
    set_land("Bree");
    set_areatype(0);
    set_areadesc("path");
    add_item(({"path", "ground"}),
        "The path runs along the north and east sides "
		+ "of the Adventurer's Guild. It "
		+ "is narrow and more or less overgrown with tall grass.\n");
	add_item("grass", "The grass is about knee high here. Grasshoppers "
		+ "jump about as you shift your feet.\n");
	add_item( ({"adventurer's guild", "guild"}), "You could train many "
		+ "useful skills in that square building.\n");
	add_item( "roof", "The roof keeps water out of the building!\n");
	add_item( ({"vane", "weathervane", "weather vane"}), "Shaped like a "
		+ "rooster standing on an arrow, the weathervane shifts back "
		+ "and forth with the wind.\n");

    set_room_tell_time(90);
    add_room_tell("The weathervane moves slightly with the wind.");
	add_room_tell("Grasshoppers jump around you.");
	add_room_tell("You hear people walking down the road in Bree.");
	add_room_tell("You smell pipe smoke on the breeze.");
	add_room_tell("You hear hobbits laugh and chatter as they walk "
		+ "through Bree.");
	add_room_tell("A rabbit darts across the path.");
    
    create_path_room();
    set_add_sky();
    add_std_herbs("field");
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
}

void
add_AG(string dir, string extra)
{
	add_item( ({"square building", "building", "guild", "adventurers guild"}),
		"You are " + dir + " of the square building. Its walls are made "
		+ "of rough-hewen logs, fitted together without a gap. " + 
		extra + "\n");
	add_item(({"log", "rough-hewn logs", "logs", "rough logs"}),
		"The logs still have axe marks on them. Whoever build this building didso "
		+ "quickly and cheaply. Nevertheless, the logs are straight and the "
		+ "gaps between them have been patched up tight. This building "
		+ "will stand the test of time.\n");
	add_item("gaps", "There are no gaps. They have been patched.\n");
	add_item( ({"patch", "patched", "patches"}), "The patches seem to be "
		+ "made of mud and straw. They will bake hard in the summer sun and "
		+ "make a serviceable seal for many years.\n");
	add_item( ({"wall", "walls"}), "You see the outside wall of the "
		+ "building. It looks quite sturdy, being "
		+ "made of logs.\n");
}