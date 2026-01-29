#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("shortsword");
    add_name("sword");
    add_adj( ({ "short", "metal", "polished" }) );
    set_short("polished shortsword");
    set_long("This sword has been polished to a brilliant shine. The image "+
      "of two crossed swords marks this as the standard issue sword for "+
      "the Kabal militia.\n");
    set_hit(19);
    set_pen(19);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE, 340);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 1500);
}
