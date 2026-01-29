/* 
 *  /d/Gondor/std/drink/beer.c:  
 *
 *  Soft 200 ml, alco 11 ml, price 24 cc.
 *  Drink for the Seven Stars Inn (common/guild/gondor/rangerinn.c)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_drink() 
{
    set_name( ({ "beer", "mug" }) );
    set_pname( ({ "beers", "mugs" }) );
    set_adj("prime");
    set_short("mug of prime beer");
    set_pshort("pints of prime beer");
    set_long(break_string(
        "The Ranger beer is of prime quality. It was brewn in the "
      + "stronghold of the Gondorian Rangers.\n",70));

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(200);
    set_alco_amount(11);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
