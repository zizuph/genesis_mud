
inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("ring");
    set_adj("mithril");
    add_adj("shiny");
    set_short("mithril ring");
    set_long("This shining mithril ring looks quite valuable, as it is " +
    "made of pure silver. It is a simple band that has been polished and " +
    "brushed with a satin finish. A small, golden, raised holly branch encircles " +
    "the center of ring.\n");
    
    set_default_armour(1, A_ANY_FINGER, ({0,0,0}), 0);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 550 + random(150));

}

