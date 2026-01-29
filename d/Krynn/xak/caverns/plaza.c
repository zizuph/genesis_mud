/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>
#include RND_MEET

inherit  XAKINROOM

#define  TABLE "/d/Krynn/common/rndtables/tbldraconians"

	object guard1, guard2;

create_xak_room()
{
        set_short("The city plaza");
        set_long(BS(
           "You are standing in the main city plaza of Xak Tsaroth deep underground in"
	 + " a huge cavern. The buildings"
	 + " are in pretty good shape considering the stresses the cataclysm"
	 + " must have placed on them though many of the walls are leaning"
	 + " dangerously. Two rivers come together here, one from the east"
	 + " and another from the west. They join together and flow south"
	 + " making travel in that direction impossible.", 70));

	add_exit(DDIR + "street2.c", "east", 0);
	add_exit(DDIR + "fall.c", "west", 0);

	add_item(({"water", "river", "rivers"}), "@@river");

	INSIDE
        DARK
	reset_room();
}

reset_xak_room()
{
	if (!guard1)
	{
            guard1 = RANDOM_MEET(TABLE);
              /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
	    if (guard1->query_prop(OBJ_I_COLORABLE))
	        guard1->set_color("black");
            guard1->move_living(0,TO);
	    guard1->set_aggressive(1);
	}

	if (!guard2)
	{
            guard2 = RANDOM_MEET(TABLE);
              /*clone_object("/d/Krynn/neraka/monster/draconian.c");*/
	    if (guard2->query_prop(OBJ_I_COLORABLE))
	        guard2->set_color("black");
            guard2->move_living(0,TO);
	    guard2->set_aggressive(1);
	}
}

river()
{
	write("The river is quite wide and flowing fast here.\n");
	return "";
}
