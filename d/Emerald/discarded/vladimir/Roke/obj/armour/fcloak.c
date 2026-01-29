
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
   set_long("A thick dark blue cloak, used to keep the elements out.\n");

    set_default_armour(5, A_ROBE, ({-1,1,0}), 0);

    add_prop(OBJ_I_WEIGHT,900);
    add_prop(OBJ_I_VOLUME,2000);
}

query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

init_recover(arg)
{
    init_arm_recover(arg);
}



