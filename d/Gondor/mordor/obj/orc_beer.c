/*
 * /d/Gondor/mordor/obj/orc_beer.c
 *
 * A small beer that orcs drink.
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
    set_name("beer");
    add_name("mug");
    set_pname("beers");
    add_name("mugs");
    set_adj("dark");
    set_adj("orkish");
    set_short("mug of dark orkish beer");
    set_pshort("mugs of dark orkish beer");
    set_long(BSN("This mug of beer is of orkish origine. You didn't know " +
        "that orcs brew beer, but it seems they do. It looks rather strong " +
        "for beer, but orcs probably like it anyway."));

    set_soft_amount(450);
    set_alco_amount(9);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 450);
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
