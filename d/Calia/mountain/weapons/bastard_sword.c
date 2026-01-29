/* a silver bastard sword wielded by some elite krougs.

    coder(s):  Maniac

    history:   
          4/8/95       Created                          Maniac

*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj(({"silver", "bastard"}));
    set_short("silver bastard sword");  
    set_pshort("silver bastard swords"); 
    set_long("An impressive looking weapon used by some higher ranking " +
             "kroug warriors. This silver bastard sword is long, broad " +
             "and double-edged.\n");
    set_hit(33);
    set_pen(31);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
}

