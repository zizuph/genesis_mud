inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_default_armour(10, A_FEET);
    add_adj("leather");
     set_long("A pair of soft leather boots, they seem to fit you well.\n");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    add_prop(OBJ_I_VOLUME, 250);
}

