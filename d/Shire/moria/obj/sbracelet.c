
inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("bracelet");
    set_adj("silver");
    add_adj("large");
    set_short("silver bracelet");
    set_long("This large silver bracelet looks as thought it is of dwarven make.\n");
    
    set_default_armour(1, A_R_ARM, ({0,0,0}), 0);

    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 150 + random(150));

}

