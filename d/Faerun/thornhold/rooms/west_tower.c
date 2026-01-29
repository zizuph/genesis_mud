/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;
object guard_npc;

void
create_house()
{
    set_short("The West Tower");
    set_long("You are in the West Tower of Thornhold. " +
    		"The tower room is a spartan stone room, " +
    		"with no furnishings or decor. Narrow " +
			"arrow slits encircle the tower, allowing " +
			"one to view the courtyard, cliffside, and " +
			"the road leading to Thornhold. In the " +
			"southwest corner, a narrow set of spiral " +
			"stone stairs descends down into the " +
			"guardroom, and to the east you may walk " +
			"out a narrow door onto the battlement.\n");
             
    add_item(({ "slit", "slits", "arrow slits" }),
			"You can look through the slits towards the " +
			"sea, the courtyard, or the road.\n");
			
	add_item(({ "door", "narrow door" }),
			"A narrow door leads to the east.\n");
	
	add_item(({ "stairs", "spiral stairs" }),
			"The spiral stairs lead to the level " +
			"below.\n");
                
    add_item(({ "sea", "west" }), "@@cliff_glint");
                
    add_item(({ "something", "glint" }),
			"Something on the edge of the cliff occasionally " +
			"glints as it catches the light. You can't tell " +
			"what it is from here.\n");

	add_item(({ "thornhold", "Thornhold", "hold", 
			"fortress", "fort" }),
			"You are standing in the west tower of " +
			"Thornhold.\n");

    add_item(({ "courtyard", "north" }),
			"Peering through the slits in the north wall, " +
			"you can peer down on the courtyard. It bustles " +
			"with activity.\n");
	
    add_item(({ "road", "gate", "gates", "south" }),
			"Peering through the slits in the south wall, " +
			"you can see the gates of the hold and part of " +
			"the road as it winds down a ridge to the east.\n");
                
    add_exit(ROOM_DIR + "battlement",  "east");
    add_exit(ROOM_DIR + "guardroom",  "down");

    reset_room();
}

string
cliff_glint() {
    object qp = this_player();
    string base = "Peering through the slits in the west wall, you can " +
			"see the Sea of Swords stretching out beyond the " + 
			"horizon. A steep cliff ascends towards Thornhold, " +
			"with only a small rim of earth beyond the hold " +
			"wall before it drops precipitously.";
    
    if(objectp(present("_thq_spice_tin", qp)) || 
    		QUEST_MASTER->check_spice(qp))
        return base + "\n";
    else
        return base + " Something small, catches the light and " +
			"glints off the cliffside.\n";
}


void
reset_faerun_room()
{
   set_searched(0);
    
   setuid(); 
   seteuid(getuid());
 
    if ((!guard_npc))
    {
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
        guard_npc = clone_object(NPC_DIR + "dwarf_guard");
        guard_npc->move(this_object()); 
    }
}
