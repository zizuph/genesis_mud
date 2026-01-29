/*
 *	/d/Gondor/common/wep/orcscim.c
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reorc.c
 *	/d/Gondor/common/npc/reorc2.c
 *	/d/Gondor/common/npc/rescout.c
 *	/d/Gondor/common/npc/whorc.c
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon() 
{
    set_name("scimitar");
    add_name("sword");
    set_pname("scimitars");
    add_pname("swords");
    set_adj("iron");
    set_short("iron scimitar");
    set_pshort("iron scimitars");
    set_long(BSN("This scimitar was forged by orcs, as the crude workmanship "
        + "reveals, but it is a dangerous weapon nevertheless. The blade " 
        + "and the crosspiece are made from iron, while the hilt is "
        + "made from dark charred wood."));
    set_default_weapon(18, 12, W_SWORD, W_SLASH | W_IMPALE, W_NONE, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(12, W_SWORD) + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18, 12) + random(37));
}
