inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 28

void
create_armour()
{
    set_name("armour");
    add_name("chainmail");
    set_pname("armours");

    set_adj("dwarven");

    set_short("dwarven chainmail");
    set_long("This is a typical suit of dwarven " +
      "chainmail, made out of iron. It looks like " +
      "it would offer good protection.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
