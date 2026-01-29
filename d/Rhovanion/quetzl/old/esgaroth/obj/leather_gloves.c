#pragma strict_types
 
#include "../esg_defs.h"
 
inherit ENHANCE_ARMOUR;
 
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("pair of soft leather gloves");
    set_pname("pairs of soft leather gloves");
    set_short("pair of soft leather gloves");
    set_pshort("pairs of soft leather gloves");
    add_name("gloves");
    set_adj("soft");
    add_adj("leather");
    set_long("The pair of soft leather gloves is very soft; you barely " +
        "feel them against your skin.\n");
 
    set_af();
    set_at(A_HANDS);
    set_ac(0);
    set_enhancement(SS_PICK_POCKET, 4);
    set_enhancement(SS_WEP_SWORD, -2);
    set_enhancement(SS_WEP_AXE, -2);
    set_enhancement(SS_WEP_KNIFE, -2);
    set_enhancement(SS_WEP_CLUB, -2);
    set_enhancement(SS_WEP_MISSILE, -2);
    set_enhancement(SS_WEP_JAVELIN, -2);
    set_enhancement(SS_UNARM_COMBAT, -2);
    set_enhancement(SS_WEP_POLEARM, -2);
 
    add_prop(OBJ_S_WIZINFO, "This pair of gloves adds 4 to the pick pocket " +
        "skill when worn by (non-magical) virtue of their material.");
}
