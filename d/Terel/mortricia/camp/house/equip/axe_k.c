/* A steel axe. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("axe");
    set_short("hardened steel axe");
    set_long("It's a hardened steel axe.\n");
    set_adj("steel");
    add_adj("hardened");
    set_hit(28);
    set_pen(28);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 1500);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
}
