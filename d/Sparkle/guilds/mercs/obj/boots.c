inherit "/std/armour";

#include <wa_types.h>
#include <formulas.h>
#include "../merc.h"

public void
create_armour()
{
    set_name("boots");
    add_name("armour");
    add_name("pair");
    set_pname("boots");
    add_pname("armours");
    add_pname("pairs");
    set_adj("leather");
    set_short("pair of black leather boots");
    set_pshort("pairs of black leather boots");
    set_long("The boots are made of thick, black leather. Engraved on the "+
	"sturdy sole is the emblem of a dragon.\n");
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    set_at(A_FEET);
    set_ac(20);
}

