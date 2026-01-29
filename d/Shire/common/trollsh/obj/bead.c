/*
 * Miscellaneous junk found in the Trollshaws
 * Designed for no purpose other than to be sold
 * -- Finwe, September 2001
 */
inherit "/std/object";
#include "/d/Shire/common/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("bead");
    add_name("_glass_bead");
    set_pshort("chipped colored beads");
    set_short("chipped colored bead");
    set_adj(({"chipped","colored"}));
    set_long("This is a chipped colored bead. It was once smooth " +
        "but now has various cracks on its surface. A hole runs " +
        "through the middle, of the bead.\n");

    add_prop(OBJ_I_WEIGHT, 7);
    add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE, 20+random(17));
}
