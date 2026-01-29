#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include "/d/Gondor/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <composite.h>
#include "/d/Gondor/std/tell.c"

string query_forge_view();

public void
create_morgul_room()
{
    set_extraline("You are at the dead end of a dark and narrow street. " +
    "The street runs north from here. The city wall rises just south of you. " +
	"The ground is covered by cobblestones. To the east you can see the " +
	"entrance into a shop. On the wall over the entrance is a sign."); 
    add_item(({"sign",}), BSN(
        "The sign shows a sword and a shield. The shop is probably an " +
        "armoury trading in weapons and armours only."));
    add_item(({"ground", "cobblestone", "cobblestones",}), BSN(
        "The road here is composd of worn cobblestones. Off to one side, " +
        "a grate is set among the cobblestones."));
    set_road(3);
    set_side("south");

    add_tower();
    add_walls();

	add_item("grate", query_forge_view);

    add_exit(MORGUL_DIR + "city/darkstr1",        "north", "@@check_exit",1);
    add_exit(MORGUL_DIR + "city/rooms/armoury",   "east",  "@@block_npc@@",1); 
	
	set_tell_time(400);
    add_tell("A wisp of acrid smoke drifts up from a grate.\n");
    add_tell("A dull red glow emanates from somewhere below the grate.\n");
    add_tell("The dull clinking of metal on metal can be heard from "
	    + "somewhere nearby.\n");


}

string query_forge_view()
{
	object *inv, *live, room;
	int i;

	inv = ({ });
	if((room = find_object("/d/Shire/smiths/rooms/mage_forge")) && 
		CAN_SEE_IN_A_ROOM(TP, room))
		inv += all_inventory(room);

	if(sizeof(inv)) 
	{
		live = FILTER_LIVE(inv);
		live = FILTER_CAN_SEE(live, TP);
		if(sizeof(live))
			return "Looking through the grate, you see " + 
				COMPOSITE_LIVE(live) + ".\n";
	}
	return "You look through the grate, but see nothing special.\n";
}