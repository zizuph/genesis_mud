/* 
	*A room inside Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

#define LOOK_ONE	"_checked_beam_once"
#define BRACE_PROP 	"_finding_bracelets_beads"
#define DROPPED_BEAD "_dropped_bead_to_floor"
#define PROP_A		"_found_a_bead"

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("Up in the rafters of a barn");
	
	set_long(short() + ". Your position is quite precarious here. The rafters aren't small, but they certainly don't offer much room to walk. There is no room to stand up here, even for the smallest of people.\n");

	add_item(({"rafters", "beams", "boards"}), "@@look_rafters");
	add_item(({"roof"}), "The roof is sloped and made of wood. It seems better suited to keeping out the elements than do the walls.\n");
	add_item(({"walls", "wall"}), "The walls are harder to see from this position. It might be best if you climb down before looking at them in greater detail.\n");
	add_item(({"floor"}), "The floor looks quite distant from here.\n");
	
	set_add_rtells_barn();
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

string look_rafters()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "The sloped beams and cross boards support the roof of the barn. They don't offer much maneuverability up here.\n";
	}
	
	if(TP->query_prop(DROPPED_BEAD))
	{
		return "The sloped beams and cross boards support the roof of the barn. They don't offer much maneuverability up here.\n";
	}
	
	if(TP->query_prop(PROP_A))
	{
		return "The sloped beams and cross boards support the roof of the barn. They don't offer much maneuverability up here.\n";
	}
	
	if(!TP->query_prop(LOOK_ONE))
	{
		TP->add_prop(LOOK_ONE, 1);
		return "The sloped beams and cross boards support the roof of the barn. They don't offer much maneuverability up here. You notice something small on the beam you are holding. Perhaps you need a closer look.\n";
	}
	
	if(TP->query_prop(LOOK_ONE))
	{
		TP->remove_prop(LOOK_ONE);
		TP->add_prop(DROPPED_BEAD, 1);
		return "It's a small bead! It is just out of reach, so you inch along the beam in an attempt to reach it. But as you stretch out your arm, you slip and knock the bead onto the floor below!\n";
	}
}

void init()
{   
	::init();
	add_action("climb_down", "climb");
}

int climb_down(string str)
{
	if(str == "down")
	{
		this_player()->catch_msg("You scamper down off the rafters.\n");
		say(QCTNAME(this_player()) + " scampers down out of the rafters.\n");
		tell_room(ROOM_DIR + "maggotbarn05", QCTNAME(this_player()) + " arrives.\n");
		this_player()->move_living("M", ROOM_DIR +"maggotbarn05",1);
                return 1;
	}	
	
	else
	{
		this_player()->catch_msg("Climb where?\n");
		return 1;
	}
}
