/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/spells/fake/f_weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    ::create_weapon();
    
    set_name("sword");
    set_adj("sharp");
    add_adj("steel");
    set_short("sharp steel sword");
    set_long("It's a very sharp steel sword. The blade is decorated with "+
             "mystic runes and symbols.\n");

    set_hit(46);
    set_pen(47);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 2500);
}
