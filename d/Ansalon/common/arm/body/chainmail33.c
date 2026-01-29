inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("chainmail");
    set_adj("alloyed");
    add_adj("steel");
    set_short("alloyed steel chainmail");
    set_long("This alloyed steel chainmail is of good " +
      "quality and has been well taken care of. Its design and " +
      "craftsmanship lead you to believe it is of dwarven make.\n");
    set_ac(33);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 2500);
}
