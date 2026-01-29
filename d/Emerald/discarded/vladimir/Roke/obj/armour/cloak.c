
inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_armour()
{
    set_name("cloak");
   set_adj("blue");
    add_adj("thick");
   set_short("blue cloak");
   set_long("A thick old cloak, it seems to have many holes in it.\n");

    set_default_armour(4, A_ROBE, ({-1,1,0}), 0);

    add_prop(OBJ_I_WEIGHT,900);
    add_prop(OBJ_I_VOLUME,2000);
}
