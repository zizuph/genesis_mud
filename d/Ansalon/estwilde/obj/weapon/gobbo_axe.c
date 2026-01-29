inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    add_name("battleaxe");
    set_adj("primitive");
    set_short("primitive battleaxe");
    set_long("This primitive battleaxe is of goblin make, design " +
      "and quality.\n");
    set_hit(20);
    set_pen(27);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 12000);
}
