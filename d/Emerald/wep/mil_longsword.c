/*Standard elvish armies longsword
*By Mhyrkhaan, November 1998.
*/
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    set_short("thin longsword");
    add_adj( ({"thin"}) );
    set_long("This thin lightweight longsword is the standard weapon of the "+
             "elven armies. The blade is polished to a shine, and the hilt "+
             "is wrapped in lambskin for added grip.\n");
    add_item( ({"blade"}),
            "The blade is thin and grey.\n");
    add_item( ({"hilt"}),
            "The hilt is wrapped in soft lambskin for extra grip..\n");
    set_hit(23);
    set_pen(24);
    set_pm(({ -2, 2, 0 }));
    add_prop(OBJ_I_WEIGHT, 1300); 
    add_prop(OBJ_I_VOLUME,  550);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
