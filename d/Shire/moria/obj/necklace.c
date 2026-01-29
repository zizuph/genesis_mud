
inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("necklace");
    set_adj("thin");
    add_adj("gold");
    set_short("thin gold necklace");
    set_long("This thin gold necklace looks valuable, even though it seems to be "+
     "missing its gems.\n");
    
    set_default_armour(1, A_NECK, ({0,0,0}), 0);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 150 + random(150));

}

