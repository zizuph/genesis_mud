/*
 *   meat.c:  Meat for the random orc
 */

inherit "/std/food";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_food() 
{
    set_name("meat");
    set_adj("dry");
    add_adj("white");
    set_short("piece of dry and white meat");
    set_pshort("pieces of dry and white meat");
    set_long(BSN(
    "The meat is dried, and has a white colour, so it won't spoil "+
    "while travelling."));
    set_amount(50);
    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 76);
    add_prop(OBJ_I_VALUE, 0);
}
