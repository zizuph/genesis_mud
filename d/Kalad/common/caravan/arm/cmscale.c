#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("polished scalemail");
    add_name("scalemail");
    add_name("mail");
    set_long("This armour has been polished to a brilliant shine. The "+
      "two crossed swords at the front of the armour indicate this is the "+
      "standard suit of armour for the Kabal militia.\n");
    set_ac(19);
    set_am(({0,5,-5}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 340);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 4000);
}
