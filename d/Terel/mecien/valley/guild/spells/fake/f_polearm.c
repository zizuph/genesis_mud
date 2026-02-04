/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/spells/fake/f_weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    ::create_weapon();
    
    set_name("polearm");
    set_adj("deadly");
    add_adj("steel");
    set_short("deadly steel polearm");
    set_long("It's a very deadly polearm made of steel. It is decorated "+
             "with mystic runes and symbols.\n");

    set_hit(40);
    set_pen(43);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 2300);
}
