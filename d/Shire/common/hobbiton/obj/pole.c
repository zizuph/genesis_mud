inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
void
create_weapon()
{
set_name("pole");
set_pname("poles");
set_adj("long");
set_adj("old");
set_short("long old pole");
set_long("This is a well-worn pole. It seems to have been put to light use "+
"in the past, either as an axe or shovel handle. It is rather long for that "+
"use, though you notice it is notched like an axe handle.\n");
set_hit(10);
set_pen(15);
set_wt(W_POLEARM);
set_dt(W_IMPALE);
set_hands(W_BOTH);
add_prop(OBJ_I_VALUE, 75);
add_prop(OBJ_I_VOLUME, 600);
add_prop(OBJ_I_WEIGHT, 600);
}
