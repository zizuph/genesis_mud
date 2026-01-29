/*
 *  /d/Gondor/std/food/steak.c
 *  Amount 570, price 576 cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("steak");
    add_name("stag");
    add_name("plate");
    set_pname("steaks");
    add_pname("stags");
    add_pname("plates");
    set_adj("stag");
    set_short("plate of hot stag steak");
    set_pshort("plates with hot stag steaks");
    set_long(break_string(
        "On the plate is a large steak of wild stag meat, served with "+
        "delicious wild sauce, potatoes, salad and jam.\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 560);
    add_prop(OBJ_I_VOLUME, 480);
}
