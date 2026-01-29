#pragma strict_types
 
#include "../esg_defs.h"
 
inherit ENHANCE_ARMOUR;
 
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
 
public void
create_armour()
{
    set_name("pair of soft leather boots");
    set_pname("pairs of soft leather boots");
    set_short("pair of soft leather boots");
    set_pshort("pairs of soft leather boots");
    add_name("boots");
    set_adj("soft");
    add_adj("leather");
    set_long("This pair of leather boots is very soft and has padded " +
        "leather soles.\n");
 
    set_af();
    set_at(A_FEET);
    set_ac(0);
    set_enhancement(SS_SNEAK, 4);
    set_enhancement(SS_SWIM, -1);
    set_enhancement(SS_CLIMB, -2);
    set_enhancement(SS_UNARM_COMBAT, -2);
 
    add_prop(OBJ_S_WIZINFO, "These boots add 4 to the sneak skill when " +
        "worn. This is not a magical effect, just a side effect of the " +
        "padded soles.");
}
