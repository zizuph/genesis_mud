/* head_pot: Well, they protect flowers don't they? */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("helm");
    set_short("pot helm");
    set_long("This ugly pot shaped monstrosity won't win anybody fashion "+
             "points, but it should deflect the less solid hits.\n");
    set_adj("pot");

    set_ac(25);
    set_am(({ 3, 3, -6}));
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 1350);
    add_prop(OBJ_I_VOLUME, 675);
}
