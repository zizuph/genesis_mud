/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/spells/fake/f_weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    ::create_weapon();
    
    set_name("club");
    set_adj("heavy");
    add_adj("steel");
    set_short("heavy steel club");
    set_long("It's a very heavy steel club. It is decorated with "+
             "mystic runes and symbols.\n");

    set_hit(41);
    set_pen(43);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 2500);
}
