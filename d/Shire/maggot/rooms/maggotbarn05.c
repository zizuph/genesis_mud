
/* 
	*A room inside Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

#define LOOK_GAP	"_found_odd_gap"
#define FOUND_CLIMB	"_found_climbing_gap"
#define BRACE_PROP 	"_finding_bracelets_beads"
#define DROPPED_BEAD "_dropped_bead_to_floor"
#define PROP_A		"_found_a_bead"
#define FOUND_CRACKS "_found_floor_cracks"
#define FOUND_BIG	"_found_large_crack"
#define FOUND_BEAD	"_found_bead_in_crack"
#define PRIED_BEAD	"_pried_bead_from_crack"

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("Inside a sturdy barn");
	
	set_long(short() + ". There are bits of hay on the ground, as well as dirt that was probably tracked in by the farm hands and animals. Tools hang on walls and from the rafters. From the smell, the space to west appears to be a stall for animals.\n");

	add_item(({"rafters", "beams", "boards"}), "The sloped beams " +
	"and cross boards support the roof of the barn.\n");
	add_item(({"walls", "wall"}), "The walls of the barn are " +
	"only a single board-width thick and have small gaps " +
	"between the slats.\n");
	add_item(({"slats"}), "The slats of wood that form the " +
	"the walls of the barn are thin and have slight gaps " +
	"between them.\n");
	add_item(({"gaps"}), "@@look_gaps");
	add_item(({"floor"}), "@@look_floor");
	add_item(({"hay", "bits", "scraps"}), "The scant scraps " +
	"of hay look like spills from the many feedings the animals " +
	"in the barn must receive.\n");
	add_item(({"shelves"}), "They are holding a few assorted " +
	"farming implements.\n");
	add_item(({"animals"}), "You don't see any animals in the " +
	"immediate area, however, from the smell and sounds, there " +
	"are probably animals in some of the stalls.\n");
	add_item(({"tools", "implements"}), "The tools are hanging " +
	"from the walls and rafters. There are also a few sitting on the " +
	"shelves. They are the kinds of inexplicably odd implements " +
	"one would expect to find on a farm.\n");
	add_item(({"stalls", "stall"}), "The animal stalls are all " +
	"on the western side of the barn. They smell strongly of " +
	"manure and old hay.\n");
	add_item(({"cracks"}), "@@look_cracks");
	add_item(({"large crack"}), "@@look_large");
	
	set_add_rtells_barn();
	
	add_exit(ROOM_DIR + "maggotbarn03", "south");
	add_exit(ROOM_DIR + "maggotbarn06", "west");

	reset_shire_room();
}

void reset_shire_room()
{
	
}

string look_gaps()
{
	if(!TP->query_prop(LOOK_GAP))
	{
		TP->add_prop(LOOK_GAP, 1);
		return "The gaps in the walls are rather small, almost negligible, barely allowing any light to enter. Something looks odd about one of the gaps though.\n";
	}
	
	if(TP->query_prop(LOOK_GAP))
	{
		TP->add_prop(FOUND_CLIMB, 1);
		return "Yes, there is something odd here. One of the gaps is horizontal, and looks large enough to fit your foot in. You might be able to climb up from here to get into the rafters.\n";
	}
}

string look_floor()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "The floor is covered with bits of hay and dirt.\n";
	}
	
	if(TP->query_prop(PROP_A))
	{
		return "The floor is covered with bits of hay and dirt.\n";
	}
	
	if(!TP->query_prop(DROPPED_BEAD))
	{
		return "The floor is covered with bits of hay and dirt.\n";
	}
	
	if(TP->query_prop(DROPPED_BEAD))
	{
		TP->add_prop(FOUND_CRACKS, 1);
		return "Oh dear! Where could the bead have gone? There are so many cracks in the floor!\n";
	}
}

string look_cracks()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "You find no cracks.\n";
	}
	
	if(TP->query_prop(PROP_A))
	{
		return "You don't need to check in the cracks, you already found the bead.\n";
	}
	
	if(!TP->query_prop(DROPPED_BEAD))
	{
		return "You find no cracks.\n";
	}
	
	if(!TP->query_prop(FOUND_CRACKS))
	{
		return "You find no cracks.\n";
	}
	
	if(TP->query_prop(FOUND_CRACKS))
	{
		TP->add_prop(FOUND_BIG, 1);
		return "There are so many of them! The bead is small, but most of the cracks don't look big enough to fit the bead. There is one large crack in the middle of the floor; it might be big enough.\n";
	}
}

string look_large()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "You find no large crack.\n";
	}
	
	if(TP->query_prop(PROP_A))
	{
		return "You don't need to check in the cracks, you already found the bead.\n";
	}
	
	if(!TP->query_prop(DROPPED_BEAD))
	{
		return "You find no large crack.\n";
	}
	
	if(!TP->query_prop(FOUND_CRACKS))
	{
		return "You find no large crack.\n";
	}
	
	if(!TP->query_prop(FOUND_BIG))
	{
		return "You find no large crack.\n";
	}
	
	if(TP->query_prop(FOUND_BIG))
	{
		TP->add_prop(FOUND_BEAD, 1);
		return "Yes! There it is! The bead is stuck in the crack. Maybe you could pry it out.\n";
	}
}

void init()
{   
	::init();
	add_action("climb_gap", "climb");
	add_action("pry_bead", "pry");
}

int climb_gap(string str)
{
	if (this_player()->query_prop(LIVE_O_STEED))
        {
            write("You must dismount your steed before climbing.\n");
            return 1;
        }
	
	if(str == "up" || str == "gap")
	{
		if(this_player()->query_prop(FOUND_CLIMB))
		{    
			this_player()->catch_msg("You scamper up into the rafters.\n");
			say(QCTNAME(this_player()) + " scampers up into the rafters.\n");
			tell_room(ROOM_DIR + "maggotbarnrafters", QCTNAME(this_player()) + " arrives.\n");
			this_player()->move_living("M", ROOM_DIR +"maggotbarnrafters",1);
                       return 1;
		}
		
		else
		{
			this_player()->catch_msg("Climb what?\n");
			return 1;
		}
	}
	
	else
	{
		this_player()->catch_msg("Climb? What could you possibly climb here?\n");
		return 1;
	}
	return 1;
}

int pry_bead(string str)
{
	if(this_player()->query_prop(FOUND_BEAD))
	{
		if(str == "bead")
		{
			this_player()->catch_msg("You pry the bead out the crack, but you pried too hard! It shoots out at high speed and rolls into the stall to the west of here.\n");
			say(QCTNAME(this_player()) + " pries something out of a large crack in the floor and it flies away at high speed!\n");
			TP->add_prop(PRIED_BEAD, 1);
			return 1;
		}
		
		else
		{
			this_player()->catch_msg("Pry what?\n");
			return 1;
		}
	}
	
	else
	{
		this_player()->catch_msg("What?\n");
		return 1;
	}
}
