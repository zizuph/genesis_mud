/*
 *  /d/Gondor/std/food/porridge.c
 *  Amount 60, price 12cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_food() 
{
    set_name("cookies");
    add_name("cookie");
    add_pname("bowls");
    set_adj("chocolate");
    add_adj("chip");
    set_short("few chocolate chip cookies");
    set_pshort("several chocolate chip cookies");
    set_long(BS(
        "The chocolate chip cookies look really tempting, and the "
       +"chocolate chips are melting in your hand, so why not "
      + "eat them right away?\n"));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(60); 
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 60);
}
