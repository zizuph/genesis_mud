inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

void
create_weapon()
{
    ::create_weapon();
    set_name("katana");
    set_adj("steel");
    add_adj("silver-steel");
    set_short("silver-steel katana");
    set_long("This sword has a shiny silver blade. It seems to be some "+
    "kind of a silver and steel alloy. It looks razor sharp, and "+
    "deadly. The handle is wraped tightly with black cloth, and "+
    "not a speck marrs its perfect beauty.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hit(30); /* 5 points more since its awsomely crafted */
    set_pen(34); /* 6 points more for its enhanced sharpened blade */
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,2000);
}

