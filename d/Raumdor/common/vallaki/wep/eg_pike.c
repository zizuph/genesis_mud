inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */

void
create_weapon()
{
    ::create_weapon();
    set_name("pike");
    set_adj("silver-edged");
    add_adj("holy");
    set_short("holy silver-edged pike");
    set_long("This pike has a long wooden haft, with a large, gleaming "+
    "blade on the top. It radiates an aura of holiness.\n");
    set_dt(W_IMPALE);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_VALUE,1100);
}
