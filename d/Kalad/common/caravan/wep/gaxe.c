#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("axe");
    set_adj("keen");
    add_adj("battle");
    set_pname("axes");
    set_short("keen battle axe");
    set_pshort("keen battle axes");
    set_long("An axe whose blade has been honed to razor sharpness, the "+
      "perfect tool for slashing flesh into ribbons.\n");
    set_hit(20);
    set_pen(29);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,3000);
}
