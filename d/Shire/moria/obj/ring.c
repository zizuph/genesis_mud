
inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("ring");
    set_adj("gold");
    add_adj("sparkling");
    set_short("gold ring");
    set_long("This sparkling gold ring looks quite valuable, as it is quite large.\n");
    
    set_default_armour(1, A_ANY_FINGER, ({0,0,0}), 0);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 350 + random(150));

}

