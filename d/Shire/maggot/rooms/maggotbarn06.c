
/* 
	*A stall in Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

#define BRACE_PROP 	"_finding_bracelets_beads"
#define DROPPED_BEAD "_dropped_bead_to_floor"
#define PROP_A		"_found_a_bead"
#define FOUND_CRACKS "_found_floor_cracks"
#define FOUND_BIG	"_found_large_crack"
#define FOUND_BEAD	"_found_bead_in_crack"
#define PRIED_BEAD	"_pried_bead_from_crack"

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void make_npcs();

object pony;

void create_shire_room()
{
	set_short("An animal stall inside a sturdy barn");
	
	set_long(short() + ". The floor is covered with fresh " +
	"hay, food and bedding for the animals in this particular " +
	"stall. A trough is built into the wall here.\n");
	
	add_item(({"trough"}), "Currently the trough is empty, " +
	"but it looks like it could be filled with food or water.\n");
	add_item(({"floor"}), "@@look_floor");
	add_item(({"hay", "fresh hay"}), "The hay looks like it " +
	"was recently tossed in here.\n");
	/*There is on bare spot in " +
	"the corner of the stall where the floor can be seen.\n");
	add_item(({"corner", "spot", "bare spot"}), "There be a " +
	"smudge of some sort on the floor in the corner.\n");
	add_item(({"smudge"}), "There isn't much left of " +
	"whatever it is, but you think you can see a pair of " +
	"wings, like those of a house fly. One of the animals " +
	"must have stepped on a bug here.\n");
	add_item(({"wings"}), "Not much is left of the wings, but they are very small, probably from a bee or fly.\n");*/
	add_item(({"bedding"}), "The bedding is mostly fresh hay, but there is some older hay underneath.\n");
	add_item(({"food", "lettuce", "alfalfa", "vegetables", "spillings"}), "Looks to be alfalfa and maybe some bits of lettuce and other leaf vegetables. The food is on the floor, and there is not much of it, so it must be spillings from the last feeding.\n");
	
	set_add_rtells_barn();
	set_add_barn();
	
	add_exit(ROOM_DIR + "maggotbarn05", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

string look_floor()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "The floor is covered by fresh hay.\n";
	}
	
	if(TP->query_prop(PROP_A))
	{
		return "The floor is covered by fresh hay.\n";
	}
	
	if(!TP->query_prop(PRIED_BEAD))
	{
		return "The floor is covered by fresh hay.\n";
	}
	
	if(TP->query_prop(PRIED_BEAD))
	{
		TP->remove_prop(PRIED_BEAD);
		TP->remove_prop(DROPPED_BEAD);
		TP->remove_prop(FOUND_CRACKS);
		TP->remove_prop(FOUND_BIG);
		TP->remove_prop(FOUND_BEAD);
		TP->add_prop(PROP_A, 1);
		clone_object("/d/Shire/maggot/obj/bead_a.c")->move(TP);
		return "Finally! You see the bead on the floor in the middle of the stall and quickly pick it up before you do something else clumsy to lose it.\n";
	}
}

void make_npcs()
{
    setuid();
    seteuid(getuid());
 
   if(!pony)
	{
		pony = clone_object(NPC_DIR + "pony");
		pony->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(pony->query_nonmet_name()))+ " waddles into the stall.\n");
	}
}
