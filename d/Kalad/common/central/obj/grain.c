/*
 * Some grain for a coffee quest
 *
 * This is what the beans turn into
 *
 * Korat    Additions by Napture
 *
 */
 
inherit "/std/food";

#include "/d/Kalad/defs.h"
#include <stdproperties.h>

void
create_food()
{
    set_name("grains");
    set_short("handful of coffee grains");
    set_long("It's a handful of coffee grains.\n");
    set_adj("handful");
    add_adj("of");

 /* All of these values need to be less than the beans!!! */
    set_amount(50);
    add_prop(OBJ_I_WEIGHT, 60); 
    add_prop(OBJ_I_VOLUME,120);
    add_prop(OBJ_I_VALUE, 10);
 
   add_prop("_korat_quest_grains", 1);
}




