/* A steel axe. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("axe");
    set_short("steel axe");
    set_long("It's a steel axe.\n");
    set_adj("steel");
    set_hit(25);
    set_pen(25);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 700);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
}
