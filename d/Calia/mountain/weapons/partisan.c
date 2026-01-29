/* A partisan wielded by lesser kroug warriors

    coder(s):   Maniac

    history:   
             4/8/95        Created                     Maniac

*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("partisan"); 
    set_adj("black"); 
    set_short("black partisan"); 
    set_pshort("black partisans"); 
    set_long("A nasty looking weapon used by lesser kroug warriors. " +
             "It's a polearm with a broad black spear-head which has " +
             "two small blades projecting out at its base.\n");
    set_hit(19);
    set_pen(29);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 3500);
}

