/* 
 * f-hjam.c
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
    set_name("ham");
    set_adj("steaming");
    add_adj("hot");
    set_short("piece of steaming hot ham");
    set_pshort("pieces of steaming hot ham");
    set_long("This is a piece of ham fried over red hot charcoal. It smells " +
        "like it was  fried over charcol mixed with hickory chips. It looks " +
        "crisp and delicious.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 560);
    add_prop(OBJ_I_VOLUME, 480);
}
