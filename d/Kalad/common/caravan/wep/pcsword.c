#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("sword");
    add_name("longsword");
    set_adj("keen");
    set_pname("swords");
    set_short("keen longsword");
    set_pshort("keen longswords");
    set_long("This long sword possesses a keen, razor-sharp edge that looks "+
      "perfect for cutting someone up into ribbons of tattered flesh.\n");
    set_hit(25);
    set_pen(24);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2500);
}
