/* 
 * steak.c
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
    set_name("steak");
    add_name("whale");
    add_name("plate");
    set_pname("steaks");
    add_pname("whales");
    add_pname("plates");
    set_adj("hot");
    set_short("plate of whale steak");
    set_pshort("plates with whale steaks");
    set_long("This is a plate of whale steak from off the coast of Dol " +
        "Amroth. it is crimson colored and was cooked in butter.\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 560);
    add_prop(OBJ_I_VOLUME, 480);
}
