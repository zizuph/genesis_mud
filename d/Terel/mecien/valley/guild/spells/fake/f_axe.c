/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/spells/fake/f_weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    ::create_weapon();
    
    set_name("axe");
    set_adj("sharp");
    add_adj("steel");
    set_short("sharp steel axe");
    set_long("It's a very sharp steel axe. The blade is decorated with "+
             "mystic runes and symbols.\n");

    set_hit(36);
    set_pen(37);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 1500);
}
