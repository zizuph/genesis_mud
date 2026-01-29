/* 
 *	/d/Gondor/common/arm/reshield.c
 *	Shield of the Mordor (Red Eye) Uruk-hai
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reorc.c
 *	/d/Gondor/common/npc/reorc2.c
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
    set_name("shield");
    add_name("Mordor_Shield");
    set_pname("shields");
    set_short("iron shield");
    set_pshort("iron shields");
    set_adj("normal");
    set_adj("iron");
    set_long("This is a normal iron shield. On the front is a crest; a small red\n"+
	     "lidless eye in the centre of a black field.\n");
    set_default_armour(8, A_SHIELD, ({ -2, 1, 1, }), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( 8, A_SHIELD) + random(501));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(25));
}
