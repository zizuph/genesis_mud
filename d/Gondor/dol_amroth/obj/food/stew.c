/* 
 *  stew.c
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
    set_name("stewed");
    add_name("vegetable");
    add_name("vegetables");
    set_pname("stewed");
    add_pname("vegetables");
    set_short("stewed vegetables");
    set_pshort("stewed vegetables");
    set_adj("stewed");
    set_long("This is a bowl of stewed vegetables. It is a common meal in " + 
        "the inns in Dol Amroth. The dish is made from a large variety of " + 
        "vegetables, and mixed together with sour cream and parsley. This " + 
        "meal is known by young as well as old.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 560);
    add_prop(OBJ_I_VOLUME, 480);
}
