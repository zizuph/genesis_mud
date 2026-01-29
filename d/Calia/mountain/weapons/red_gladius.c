/* a gladius wielded by regular kroug warriors.

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
    set_name("gladius");
    set_pname("gladii");
    add_name("sword"); 
    add_pname("swords"); 
    set_adj("red");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("red gladius"); 
    set_pshort("red gladii"); 
    add_pname("gladiuses");
    add_name("weapon");
    add_pname("weapons");
    set_long("A nasty looking weapon used by regular kroug warriors. " +
             "This gladius has a red blade and hilt which makes it " +
             "look permanently bloodied.\n");
    set_hit(22);
    set_pen(20);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
}

