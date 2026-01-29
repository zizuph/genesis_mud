inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    add_name("battleaxe");
    set_adj("gigantic");
    set_short("gigantic battleaxe");
    set_long("A gigantic battleaxe with a head almost twice " +
      "the size of a horses head, attached to a sturdy piece " +
      "of timber. Decorated with grotesque trophies, you gather " +
      "this huge weapon was once owned by a powerful goblinoid.\n");
    set_hit(33);
    set_pen(40);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 12000);
}
