/* A stiletto used by some lesser krougs.

   Coded by Maniac

   History:
       4/8/95          Created                 maniac 
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("stiletto");
    add_name("knife");
    set_adj("sharp");
    set_short("sharp stiletto"); 
    set_pshort("sharp stilettos");  
    set_long("A nasty looking weapon used by lesser kroug warriors. " +
             "This stiletto is a thin-bladed knife with a very sharp " +
             "point. Not exceptional, but if you stick this in someone " +
             "it's likely to make a nasty hole.\n"); 

    set_hit(15);
    set_pen(25);

    set_wt(W_KNIFE); 
    set_dt(W_IMPALE); 

    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
}
