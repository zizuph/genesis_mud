/*
 *   bread.c:  bread for the random orc
 */

inherit "/std/food";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_food() 
{
    set_name("bread");
    set_adj("hard");
    add_adj("grey");
    set_short("piece of hard and grey bread");
    set_pshort("pieces of hard and grey bread");
    set_long(BSN(
    "This bread must have been baked weeks ago. It is hard and dry. "+
    "Still, it will be nourishing for a famished traveller."));
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 73);
    add_prop(OBJ_I_VALUE, 0);
}

