/* 
 *  /d/Gondor/std/drink/rum.c:  
 *
 *  Soft 100 ml, alco 24 ml, price 72 cc.
 *  Drink for the Restful Hearth Inn (common/guild/north/inn.c)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_drink() 
{
    set_name("rum");
    add_name(({"rumtoddy","toddy"}));
    set_adj("hot");
    set_short("cup of rumtoddy");
    set_pshort("cups of rumtoddy");
    set_long("The rumtoddy smells sweet and is hot.\n");
    set_soft_amount(100);
    set_alco_amount(24);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,    0);
}

