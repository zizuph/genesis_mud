inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    set_adj("notched");
    add_adj("dull");
    set_long("This is an old, two-handed battleaxe that looks like it has seen better " + 
      "times. It has notches down its wooden grip, signifying the number of goblins the owner " +
      "has slain with it.\n");
    set_short("notched dull axe");
    set_hit(20);
    set_pen(27);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 12000);
}
