/* A main gauche used by regular and high ranking krougs to backup their
   sword.

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
    set_name("gauche");
    add_name("knife");
    add_pname("knives"); 
    set_adj("main");
    set_short("main gauche"); 
    set_pshort("main gauches"); 
    set_long("A nasty looking weapon used by regular and high " +
             "ranking kroug warriors, and used in conjunction with " +
             "a sword. It is a dagger with a large downward curved " +
             "crossguard.\n"); 

    set_hit(17);
    set_pen(17);

    set_wt(W_KNIFE); 
    set_dt(W_IMPALE | W_SLASH); 

    set_hands(W_LEFT);

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
}

