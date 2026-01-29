
/*  
    Short spear for the water krougs

    Coded by Digit and Maniac
*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("spear");
    set_adj(({"short", "black"}));
    set_short("short black spear"); 
    set_long("A short black spear.\n");
    set_hit(11);
    set_pen(11);
    set_hands(W_ANYH); 
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 2500);
}
