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
    set_adj("tattered");
    add_adj("black");
    set_short("tattered black cloak");
    set_long("This is a dirty, well-worn, black cloak. There are a few "+
    "holes in it, and it is torn in many places. It looks like it was dug "+
    "out of the ground, as it is rather filthy. However, embroidered on the "+
    "back, you see a rather intricate picture of a grim looking skull.\n");
    set_default_armour(5,A_ROBE,0,0);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,10);
}

