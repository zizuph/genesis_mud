inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("shield");
    set_adj("great");
    add_adj("steel");
    set_short("great steel shield");
    set_long("This very large shield is made of a great deal " +
      "of steel, a commodity in great demand at the moment. For " +
      "someone to carry this around means that the owner is " +
      "either rather rich, or rather sure of his abilities to " +
      "keep hold of it in these days of darkness.\n");
    set_ac(25);
    set_at(A_SHIELD);
    add_prop(OBJ_I_VOLUME, 2500);
}
