inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
    set_name("boots");
    set_adj("leather");
    add_adj("short");
    set_short("pair of smelly boots");
    set_pshort("pairs of smelly boots");

 set_long("These boots are well worn, and very dirty, it's "
         +"no surprise they belong to a goblin.\n");


    set_default_armour(8, A_FEET | A_LEGS, ({-2,2,1}), 0);

    add_prop(OBJ_I_WEIGHT,2300);
    add_prop(OBJ_I_VOLUME,1200);
   add_prop(OBJ_I_VALUE,300);
}

query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

init_recover(arg)
{
    init_arm_recover(arg);
}
