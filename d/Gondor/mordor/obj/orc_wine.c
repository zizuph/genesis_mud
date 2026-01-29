/*
 * /d/Gondor/mordor/obj/orc_beer.c
 *
 * A bottle of wine or blood that orcs drink.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/*
 * Called to create the beer
 */
void
create_drink()
{
    set_name("wine");
    add_name("bottle");
    set_pname("bottles");
    add_adj("orkish");
    add_adj("red");
    set_short("bottle of orkish red wine");
    set_pshort("bottles of orkish red wine");
    set_long(BSN("This is a bottle of red wine, found in the tower at " +
        "Cirith Ungol. You didn't know orcs made wine, so this could also " +
        "be blood from a some creature the orcs caught."));

    set_soft_amount(750);
    set_alco_amount(17);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 750);
}

/*
 * Revovery stuff
 */
string
query_recover()
{
    return MASTER;
}

void
init_recover(string arg)
{

}
