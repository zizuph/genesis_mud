/*
 *  /d/Gondor/std/food/pheasant.c
 *  Amount 285, price 144 cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food() 
{
    set_name("pheasant");
    add_name("plate");
    set_adj("hot");
    set_short("hot plate of fried pheasant");
    set_pshort("hot plates with fried pheasants");
    set_long(break_string(
        "The pheasant has been fried, and is deliciously served with "+
        "potatoes, sauce and a tad of garlic.\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(285);
    add_prop(OBJ_I_WEIGHT, 285);
    add_prop(OBJ_I_VOLUME, 200);
}
