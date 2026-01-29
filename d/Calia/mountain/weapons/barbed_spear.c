/*  Barbed spear wielded by some elite kroug warriors
    
    coder(s):  Maniac

    history:   
           4/8/95              Created                 Maniac
*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("spear");
    set_adj(({"long", "barbed"}));
    set_short("long barbed spear");  
    set_pshort("long barbed spears"); 
    set_long("A powerful looking weapon used by elite kroug warriors. " +
	"This long spear has nasty looking barbs to inflict larger " +
        "wounds.\n");
    set_hit(32);
    set_pen(38);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 4500);
}

