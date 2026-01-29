/* 
    a steel two-handed sword wielded by some elite krougs.

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
    set_adj(({"steel", "two-handed"})); 
    set_short("steel two-handed sword"); 
    set_pshort("steel two-handed swords"); 
    set_long("A powerful looking weapon used by elite kroug warriors. " + 
             "It's a heavy steel sword with a long razor-sharp blade.\n"); 
    set_hit(36); 
    set_pen(36); 
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 6000);
}

