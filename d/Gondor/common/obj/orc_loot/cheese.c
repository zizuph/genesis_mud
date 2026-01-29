/*
 *   cheese.c:  Cheese for the random orc
 */

inherit "/std/food";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_food() 
{
    set_name("cheese");
    set_adj("smelly");
    add_adj("moldy");
    set_short("smelly cheese");
    set_long(BSN(
    "A smelly and somewhat moldy cheese. You must be real hungry before "+
    "you eat this one."));
    set_amount(20);
    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 76);
    add_prop(OBJ_I_VALUE, 0);
}

