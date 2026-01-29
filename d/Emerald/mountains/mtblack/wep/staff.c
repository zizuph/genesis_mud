inherit "/std/weapon.c";
#include "/d/Emerald/defs.h";
#include <wa_types.h>;

create_weapon()
{
    set_long("This staff is about 8 feet tall and is "+
       "inlayed with silver and inscribed with runes. "+
       "the bottom of it is spiked while the top has a "+
       "rounded top with the emblem of a hawk on it.\n");
    set_short("silver inlayed staff");
    set_name("staff");
    add_adj(({"silver", "inlayed", "silver inlayed"}));
    set_hit(20);
    set_pen(20);
    set_dt(W_BLUDGEON);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
}
