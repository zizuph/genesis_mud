#include "defs.h"

#include <stdproperties.h>
inherit MONASTERY_BASE;

void
create_m0_room()
{
}

void
create_monastery_room()
{
    set_short("Inside the monastery crypt");

    set_em_long("This is apparently where the crypt where the " +
        "remains of the monastery's monks are laid to rest.  " +
        "The walls of this dank, dusty room are lined with " +
        "long compartments which are draped with sections " +
        "of red silk.\n");

    add_item(({ "remains", "bones", "skeletons", "corpses" }),
        "You peek into one of the compartments and see some " +
        "skeletal remains laid out, undisturbed.\n");

    add_item(({ "compartments", "compartment", "long compartments" }),
        "A series of compartments line the walls, each about two " +
        "meters long and one-half a meter high.  Most are draped " +
        "with red silk, but several are not, the fabric torn down " +
        "and tossed to the ground.\n");

    add_item(({ "silk", "red silk", "sections of silk", 
        "sections of red silk" }),
        "Red silk panels are hung over the compartments.  A few " +
        "compartments, though, have been uncovered, their silk " +
        "drapings ripped off and thrown to the floor.\n");

    add_prop(ROOM_I_INSIDE, 1);
    remove_prop(ROOM_I_LIGHT);

    create_m0_room();
}
