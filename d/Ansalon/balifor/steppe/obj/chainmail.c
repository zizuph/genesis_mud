inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 33

void
create_armour()
{
    set_name("armour");
    add_name("chainmail");
    set_pname("armours");

    set_adj("alloyed");
    add_adj("steel");
    set_short("alloyed steel chainmail");
    set_pshort("alloyed steel chainmails");
    set_long("This alloyed steel chainmail is of good " +
      "quality and has been well taken care of. Its design and " +
      "craftsmanship lead you to believe it is of dwarven make.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 21000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
