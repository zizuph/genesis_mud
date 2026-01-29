inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 25

void
create_armour()
{
    set_name("shield");
    set_pname("shields");

    set_adj("reinforced");
    add_adj("wooden");

    set_short("reinforced wooden shield");
    set_long("This large circular shield has been " +
      "crafted out of hardwood and reinforced with iron " +
      "bands. In the center of the shield is the symbol " +
      "of two twin peaks, the symbol of Iron Delving.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}
