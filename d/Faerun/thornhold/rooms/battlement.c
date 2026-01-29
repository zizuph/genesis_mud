/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;
object durana_npc;

void
create_road()
{
	set_short("The Thornhold battlement");
    add_extra_string_end ("The battlement overlooks both the " +
    "courtyard and the road that leads to the gates of " +
    "Thornhold. The battlement walls are made with sturdy " +
    "stone, and deep crenellations are cut into both " +
    "parapets. Narrow doors lead east and west into " +
    "Thornhold's respective guard towers.");
	
    reset_faerun_room();

    add_exit(ROOM_DIR + "east_tower",    "east");
    add_exit(ROOM_DIR + "west_tower",   "west");

	add_item(({ "tower", "towers", "battlement", "guard tower" }),
		"The battlement is flanked by two tall towers, which " +
		"you can access to the east and west respectively.\n");
		
	add_item(({ "road", "down", "courtyard" }),
		"Looking down from the battlement you can see the road " +
		"to the south, and the courtyard to the north.\n");

	add_item(({ "wall", "walls", "battlement walls" }),
		"The walls are constructed of sturdy gray stone and are " +
		"sealed together with coarse mortar.\n");

	add_item(({ "parapets", "parapet"}),
		"Parapets line the battlement walkway to the north along " +
		"the courtyard interior, and south above the fortress " +
		"gate.\n");
		
	add_item(({ "crenellations", "merlons", "crenels", "stone",
		"sturdy stone" }),
		"Crenels provide openings between merlons of stone, " +
		"creating crenellations along the southern parapet.\n");
	
	add_item(({ "thornhold", "Thornhold", "hold",
		"fortress", "fort" }),
		"You are standing on the battlement of " +
		"Thornhold.\n");


}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
   set_searched(0);
    
   setuid(); 
   seteuid(getuid());
 
    if ((!durana_npc))
    {
        durana_npc = clone_object(NPC_DIR + "durana");
        durana_npc->move(this_object()); 
    }
}
