inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("breastplate");
    set_adj("hardened");
    add_adj("leather");
    set_short("hardened leather breastplate");
    set_long("This hardened leather breastplate is of fine make, " +
      "and looks like it was crafted for quite a muscular man. " +
      "It has been hardened in some natural juices that makes it " +
      "as tough to penetrate as chainmail.\n");
    set_ac(20);
    set_at(A_TORSO);
    add_prop(OBJ_I_VOLUME, 2500);
}
