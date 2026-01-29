/* Stralle @ Genesis 031109
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("mace");
    set_adj(({"small", "steel"}));
    set_short("small steel mace");
    set_pshort("small steel maces");
    set_long("This is nothing more than a rod of steel. Somewhat " +
        "small - the same diameter as that of a silver coin and " +
        "extending about two feet - looks can be decieving. A " +
        "simple handle has been made out of leather to allow for " +
        "a better grip whereas in the other end, sits a ball, no " +
        "bigger than a fist, with small spikes protruding from it.\n");
    
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(30);
    set_pen(32);
    set_wt(W_CLUB);
    
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 32));
}    
