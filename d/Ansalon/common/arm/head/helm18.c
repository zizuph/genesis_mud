#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("hood");
    add_name("helm");
    set_adj("chainmail");
    add_adj("chain");
    add_adj("mail");
    set_short("chainmail hood");
    set_ac(18);
    set_am(({-1,2,-1}));
    set_at(A_HEAD);
    set_long("The hood is made of interwoven chains of steel on a soft " +
        "leather padding. It is more comfortable than a rigid helmet, but " +
        "offers less protection.\n");
    add_prop(OBJ_I_VOLUME, 1000);
}

