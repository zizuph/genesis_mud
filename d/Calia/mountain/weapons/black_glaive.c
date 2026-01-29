/* A glaive wielded by regular kroug warriors

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
    set_name("glaive"); 
    set_adj("black"); 
    set_short("black glaive"); 
    set_pshort("black glaives"); 
    set_long("A nasty looking weapon used by regular kroug warriors. " + 
             "It consists of a black steel single-edged blade at the " + 
             "end of a long pole.\n"); 
    set_hit(25);
    set_pen(31);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 4000);
}

