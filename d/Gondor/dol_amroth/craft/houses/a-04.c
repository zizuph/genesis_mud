/*
 * craft/houses/a-04
 *
 * A common house in Dol Amroth, somebody must have forgotten to lock the
 * door.
 *
 * By Skippern
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/*
 * Function name:    create_inside()
 * Description  :    Creates the inside room.
 */
public void
create_inside()
{
    set_short("inside a common house");
    set_long("This is the inside of a common house. The walls are of sturdy " +
	     "lumber, the floor boards are broad, and the ceiling is low. " +
	     "The room is lightly furnished, with a small cupboard, a " +
	     "table, a bench and a few chairs. Everything here has a dull " +
	     "and matted colour, as if nobody have bothered by painting " +
	     "for several years.\n");

    add_item( ({ "wall", "walls" }), "The walls are made out of sturdy " +
	      "lumber.\n");
    add_item("furniture", "The furniture seems worn, the colours are pale " +
	     "and dull.\n");
    add_item("cupboard", "At one of the walls a small cupboards stands, " +
	     "containing most of the house's kitchen utensils.\n");
    add_item("table", "The table is small, but large enough to seat a few " +
	     "persons around it. There are a few stains on the table, and " +
	     "the top plate is worn down after many years of usage.\n");
    add_item("floor", "The floor consists of broad boards with almost no " +
	     "cracks in them. The boards must have come from a realy big " +
	     "three.\n");

    clone_object(DOL_OBJ + "doors/a-04-door")->move(this_object());
}
