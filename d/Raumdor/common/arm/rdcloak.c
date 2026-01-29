/* by Sarr */

inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

void
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("dirty");
    add_adj("golden");
    set_short("dirty golden cloak");
    set_long("This filthy looking cloak looks like it was once a "+
    "beautiful, golden cloak. Now it is in tatters, and covered with "+
    "dirt and grime. Looking along the back of the cloak, however, "+
    "you can still make out a large golden sun with rays.\n");
    set_default_armour(10,A_ROBE,0,0);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,10);
}

