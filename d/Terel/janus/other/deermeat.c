/* corpse from a deer */
/* janus 920701 */

inherit "/std/food";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_food()
{
    set_name("meat");
    set_decay_time(300);
    set_adj("deer");
    set_long("It is bloody hunks of meat from an animal. Looks OK to eat, but\n"+
             "better prepare it first.\n");
    set_amount(500); /* 500 grams of food. */
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
}

