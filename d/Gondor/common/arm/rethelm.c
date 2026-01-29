/*
 *	/d/Gondor/common/arm/rethelm.c
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reorc.c
 *	/d/Gondor/common/npc/reuruk.c
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_armour() 
{
    set_name("helm");
    set_pname("helms");
    set_short("tabarded helm");
    set_pshort("tabarded helms");
    set_adj("iron");
    set_adj("tabarded");
    set_long(BSN("This iron helm with a tabard was wrought by orcs. On the " + 
        "front just above the tabard it bears a strange device: A red lidless " +
	"eye on a black field."));
    set_default_armour(19, A_HEAD, ({ -1, 1, 0}), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( 19, A_HEAD) + random(501));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19)+random(10)-20);
}
