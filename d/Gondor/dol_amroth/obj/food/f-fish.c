/* 
 *  f-fish.c
 *
 * By Skippern 20(c)02
 *  Amount 570, price 576 cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("fish");
    add_name("fried");
    set_pname("fried");
    add_pname("fish");
    set_adj("greasy");
    add_adj("strip");
    add_adj("strip of");
    add_adj("fried");
    add_adj("fish");
    set_short("strips of greasy fried fish");
    set_pshort("strips of greasy fried fish");
    set_long("This is a basket of fish strips. They were fried in oil and " +
        "are golden brown. Each fish strip is golden brown and wrapped in " +
        "parchment.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 560);
    add_prop(OBJ_I_VOLUME, 480);
}
