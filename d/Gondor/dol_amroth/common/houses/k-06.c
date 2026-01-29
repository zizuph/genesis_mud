/*
 * k-06
 *
 * By Skippern 20(c)02
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

void
create_inside()
{
    set_short("a living room");
    set_long("This is the living room of a common house. " +
	     "The room is scarcly furnished, with the " +
	     "main object occupying the room a table, " +
	     "a bench by the far wall behind the table, " +
	     "and a few chairs infront of it.\n");

    add_item("table", "A large table occupy the main part " +
	     "of the room.\n");
    add_item("bench", "A bench is seated between the table and " +
	     "the far wall.\n");
    add_item( ({ "chair", "chairs" }), "A few chairs are infront " +
	      "of the table.\n");

    clone_object(DOL_OBJ + "doors/k-06-door")->move(this_object());
}
