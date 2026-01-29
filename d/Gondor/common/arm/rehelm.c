/*
 *	/d/Gondor/common/arm/rehelm.c
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reorc.c
 *	/d/Gondor/common/npc/reorc2.c
 *	/d/Gondor/common/npc/rescout.c
 *	/d/Gondor/common/npc/reuruk.c
 */
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour() 
{
    set_name(({"helm","iron helm","helmet","iron helmet"}));
    set_pname("helms");
    add_pname("helmets");
    set_short("iron helm");
    set_adj("iron");
    set_pshort("iron helms");
    set_long("This iron helm is the standard helm for lesser Orcs.\n"+
	     "On the front you see a red eye, wrought of some red metal.\n");
    set_default_armour(8, A_HEAD, ({ -2, 1, 1, }), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( 8, A_HEAD) + random(501));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(25));
}
