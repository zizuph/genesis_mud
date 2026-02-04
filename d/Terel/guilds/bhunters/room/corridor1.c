/*
 Bounty hunters training room,
 by Udana 05/06
 temp also join room.
*/

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../bhunters.h"

inherit STDROOM;

public void create_terel_room()
{
	set_short("Corridor in 'Hook & Dagger'");
	set_long("Narrow corridor on first floot of 'Hook & Dagger' tavern. The corridor continues to the "+
		"south, on your right and left doors lead to tavern rooms.\n");
	add_exit(BHROOM + "boris_room", "east", 0, 1, 0);
	add_exit(BHROOM + "karl_room", "west", 0, 1, 0);
	add_exit(BHROOM + "corridor2", "south", 0, 1, 0);
	add_exit(BHROOM + "join", "staircase", 0, 1, 0);
}

