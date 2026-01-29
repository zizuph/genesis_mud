inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_armour()
{
    set_name("boots");
    set_adj("well-used");
    set_short("pair of well-used boots");
    set_pshort("pairs of well-used boots");

    set_long("These boots have appearently been used a lot. Apart from "+
      "that, they're also very dirty.\n");

    set_default_armour(7, A_FEET | A_LEGS, ({-1,1,0}), 0);

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1000);
}
