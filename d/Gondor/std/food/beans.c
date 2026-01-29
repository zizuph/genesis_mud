/*
 *  /d/Gondor/std/food/beans.c
 *  Amount 200, price 72 cc.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food() 
{
    set_name("bacon");
    add_name("plate");
    add_name("beans");
    set_pname("bacons");
    add_pname("plates");
    add_pname("beanses");       /* ugh.  but don't want to use "beans" */
    set_adj("hot");
    set_short("hot plate of beans and bacon");
    set_pshort("hot plates of beans and bacon");
    set_long("The hot plate of beans and bacon smells so delicious that you "+
	     "feel like eating it right away.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(200);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 150);
}
