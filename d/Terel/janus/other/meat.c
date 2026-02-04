/* meat.c */
/* janus 920701 */

inherit "/std/food";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_food()
{
    set_name("meat");
    set_adj("bloody");
    set_long("This is bloody hunks of meat from an animal. Looks OK to eat, but\n"+
             "better prepare it first.\n");
    set_amount(100); /* 500 grams of food. */
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

