/* Crude uniforms worn by Grum and Hepp
 * by Teth, April 25, 1996
 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("splint mail");
    add_name("mail");
    add_name("splint");
    set_ac(21);
    set_am( ({ 1, 1, -2}) );
    set_at(A_BODY);
    set_adj("sturdy");
    add_adj("crude");
    set_short("sturdy crude splint mail");
    set_pshort("sturdy crude splint mails");
    set_long("This armour is sturdy, but crude. It is made of vertical " +
             "strips of metal rivetted to hard leather. This armour " +
             "hasn't been well-maintained, and it smells like goblin.\n");
    add_prop(OBJ_I_VOLUME, 3100);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(21, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21));
}

