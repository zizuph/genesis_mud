/* 
    a broadsword wielded by high ranking krougs.

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
    set_name("broadsword"); 
    add_name("sword"); 
    set_adj("gold"); 
    set_short("gold broadsword"); 
    set_pshort("gold broadswords"); 
    set_long("An impressive looking weapon used by high ranking " + 
             "kroug warriors, a broadsword with a gold blade.\n"); 
    set_hit(28);
    set_pen(28);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 3500);
}

