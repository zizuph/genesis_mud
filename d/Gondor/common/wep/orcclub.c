/* 
 *	/d/Gondor/olorin/obj/orcclub.c
 *	A very heavy orc mace
 *	Olorin, Nov 1992
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reorc.c
 *	/d/Gondor/common/npc/reorc2.c
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon() 
{
    set_name("mace");
    set_pname("maces");
    set_short("heavy mace");
    set_pshort("heavy maces");
    set_long("A heavy orc mace.\n");
    set_adj("orc");
    add_adj("heavy");
    set_default_weapon(22, 22, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(22, 22) + random(200));
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(22, W_CLUB) + 1000 + random(1001)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
