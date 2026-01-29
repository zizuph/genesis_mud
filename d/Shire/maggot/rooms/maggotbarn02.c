
/* 
	*A stall in Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

#define PROP_E			"_found_e_bead"
#define BRACE_PROP 		"_finding_bracelets_beads"
#define LOOK_ONE		"_checked_dirt_found_print"
#define LOOK_TWO		"_checked_print_once"

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("An animal stall inside a sturdy barn");
	
	set_long(short() + ". This stall is empty, but the floor " +
	"looks like it is in need of a good mucking, evidence that it " +
	"was recently occupied.\n");
	
	add_item(({"floor"}), "The floor is littered with old hay, " +
	"dirt and manure.\n");
	add_item(({"hay", "old hay"}), "The hay is disgusting. " +
	"A rather musty, dank smell is coming from it, or is it " +
	"coming from the manure?\n");
	add_item(({"manure"}), "The manure is smashed into " +
	"the hay and all over the floor inside the stall.\n");
	add_item(({"dirt"}), "@@look_dirt");
	add_item(({"footprint"}), "@@look_print");
	
	set_add_rtells_barn();
	set_add_barn();
	
	add_exit(ROOM_DIR + "maggotbarn01", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	
}

string look_dirt()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "The dirt was probably tracked in by whatever animal occupied this stall. It is mixed with the manure.\n";
	}
	
	if(TP->query_prop(PROP_E))
	{
		return "The dirt was probably tracked in by whatever animal occupied this stall. It is mixed with the manure.\n";
	}
	
	if(!TP->query_prop(LOOK_ONE))
	{
		TP->add_prop(LOOK_ONE, 1);
		return "The dirt was probably tracked in by whatever animal occupied this stall. You notice a footprint in the dirt.\n";
	}
	
	if(TP->query_prop(LOOK_ONE))
	{
		return "The dirt was probably tracked in by whatever animal occupied this stall. You notice a footprint in the dirt.\n";
	}
}

string look_print()
{
	if(TP->query_prop(LOOK_TWO))
	{
		TP->remove_prop(LOOK_TWO);
		TP->add_prop(PROP_E, 1);
		clone_object("/d/Shire/maggot/obj/bead_e.c")->move(TP);
		return "There was something smashed into the dirt! You find a small bead and quickly pick it up, smudging out the footprint as you do so.\n";
	}
	
	if(!TP->query_prop(BRACE_PROP))
	{
		return "You find no footprint.\n";
	}
	
	if(!TP->query_prop(LOOK_ONE))
	{
		return "You find no footprint.\n";
	}
	
	if(TP->query_prop(LOOK_ONE))
	{
		TP->add_prop(LOOK_TWO, 1);
		TP->remove_prop(LOOK_ONE);
		return "The footprint is rather small. You think you might see something smashed into the dirt of the footprint. Perhaps a closer look is needed.\n";
	}
}