inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


void
create_armour()
{
    set_name("armour");
    add_name("_dont_react_to");
    add_name("platemail");
    set_pname("armours");

    set_adj("ornamental");
    set_short("ornamental platemail");
    set_long("This set of platemail is beautifully made, truly a work of art. Still, for "+
      "practical purposes this was probably made for the parade ground rather than the battle " +
      "field, and I am sure the previous owner would have balked at the idea of fighting while " +
      "wearing this expensive piece of armour!\n");

    set_ac(30);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 24000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(75));
}
