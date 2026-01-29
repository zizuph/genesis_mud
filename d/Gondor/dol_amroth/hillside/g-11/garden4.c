/*
 * hillside/m-11/garden1.c
 *
 * Skippern 20(c)01
 *
 * A luxury estate in Dol Amroth
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/lib/unique";

#include "../../defs.h"
#include "../defs.h"
#include <stdproperties.h>

inherit DOL_LIB + "garden";

/* Global variables */
        object    o;


void
create_gondor()
{

    set_short("a path through a garden");
    set_long("This is a beautiful garden, filled with bushes, flowers " +
	     "and trees. Near the house you find four statues, and in " +
	     "the middle of the garden stands a fountain in the middle " +
	     "of a small pound. From the gate in east to the door in " +
	     "goes a paved path.\n");

    /* Flowers: lilly, rose, tulip */
    add_item( ({ "flower", "flowers", "flower bed", "flower beds" }),
        "Both sides along the path beautiful beds with flowers. " +
	"There are all kinds of beautiful flowers in all colors.\n");
    /* Bushes: */
    add_item( ({ "bush", "bushes" }), "Bushes covers the base of the " +
	      "statues giving a sweet sent in the air.\n");
    add_item( ({ "tree", "trees" }), "As collumns reaching for the sky " +
	      " is some large trees scatered in the garden. You see some " +
	      "maples, oaks and aspen trees here.\n");
    add_tree( ({ "maple", "oak", "aspen" }) );
    add_item("fountain", "In the middle of the garden a marble godess " +
	     "stands and pours water out of a vase and into a small pound.\n");
    add_item("pound", "In the middle of the garden there is a small pound. " +
	     "In the pound small waterlillys float, and when you look " +
	     "closely you notices fish swiming under the surface.\n");
    add_item( ({ "statue", "statues" }), "Four stout men carved out of " +
	      "white marble guards the front door.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_AMROTH_GARDEN);
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({"pool", "pound", "fountain"}) );

    add_exit(DOL_HILLS + "g-11/garden1", "northeast", 0, 1);
    add_exit(DOL_HILLS + "g-11/garden3", "northwest", 0, 1);

    reset_room();
}

void
init()
{
    ::init();
    init_drink();
}

void
reset_room()
{
    ::reset_room();

}

