/* 
 *  /d/Gondor/std/drink/beer.c:  
 *
 *  Soft 100 ml, alco 8 ml, price 18 cc.
 *  Drink for The Restful Hearth Inn (common/guild/north/inn.c)
 */
#pragma strict_types

inherit "/std/drink.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_drink()
{
    set_name( ({ "beer", "mug" }) );
    set_pname("beers");
    add_pname("mugs");
    set_adj("prime");
    set_short("mug of prime beer");
    set_pshort("pints of prime beer");
    set_long(BSN("The Bree beer is of prime quality. "+
    "It was brewn in and imported from the village Bree."));
    set_soft_amount(100);
    set_alco_amount(8);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,   0);
}

