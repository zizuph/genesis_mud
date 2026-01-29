/*broadsword.c
*Broadsword for elite elven warriors.
*By Mhyrkhaan, November 1998.
*/
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    set_short("polished broadsword");
    add_adj( ({"polished"}) );
    set_long("This broadsword is very sharp and well made. The blade " +
        "is polished to a steely shine, and the hilt is wrapped in " +
        "lambskin for better grip.\n");
    add_item( ({"blade"}),
        "The blade is wide and very sharp.\n");
    add_item( ({"hilt"}),
        "The hilt is wrapped in soft lambskin for a better grip.\n");
    set_hit(28);
    set_pen(27);
    set_pm(({ -2, 2, 0 }));
    add_prop(OBJ_I_WEIGHT, 1400); 
    add_prop(OBJ_I_VOLUME,  600);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
