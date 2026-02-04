/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/spells/fake/f_weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    ::create_weapon();
    
    set_name("knife");
    set_pname("knives");
    set_adj("sharp");
    add_adj("steel");
    set_short("sharp steel knife");
    set_pshort("sharp steel knives");
    set_long("It's a very sharp steel knife. The blade is decorated with "+
             "mystic runes and symbols.\n");

    set_hit(26);
    set_pen(27);

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE, 500);
}
