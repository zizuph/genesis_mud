/*
 *  /d/Gondor/std/food/stew.c
 *  Amount 135, price 36 cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food.c";

#include <stdproperties.h>

public void
create_food() 
{
    set_name("stew");
    add_name("bowl");
    set_pname("stews");
    add_pname("bowls");
    set_adj("vegetable");
    set_short("bowl of hot vegetable stew");
    set_pshort("bowls of hot vegetable stew");
    set_long(break_string(
	"The vegetable stew looks really delicious (for those who love "+
        "vegetables), with green and red vegetable pieces stewed "+
        "together and cooked en masse.\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(135);
    add_prop(OBJ_I_WEIGHT, 135);
    add_prop(OBJ_I_VOLUME, 100);
}
