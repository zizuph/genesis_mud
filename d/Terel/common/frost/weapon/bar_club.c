inherit "/std/weapon";
#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("morningstar");
    add_name("club");
    set_adj("spiked");
    set_adj("iron");
    set_short("spiked iron morningstar");
    set_pshort("spiked iron morningstars");
    set_long(BSN("The "+short()+" big, not meant to be wielded by "+
                 "children and little folk. The morningstar is heavy, but "+
                 "strong, wielding it will be a problem for those "+
                 "of small stature"));
    set_default_weapon(20,30,W_CLUB,W_BLUDGEON,W_BOTH,TO);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(20,W_CLUB));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,30));
    add_prop(OBJ_I_VOLUME,2000);
}



