/*
 *	/d/Gondor/common/arm/releather.c
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/rescout.c
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
    set_name("leather armour");
    add_name("armour");
    set_pname("armours");
    set_short("leather armour");
    set_pshort("leather armours");
    set_adj("leather");
    set_adj("poor");
    set_long("The standard armour of a normal Orc, poor of quality and design.\n"+
        "Upon the front of the armour you see a crest; a red eye upon a black field.\n");
    set_default_armour(7, A_BODY, ({ 0, 1, -1}), 0);
    add_prop(OBJ_I_WEIGHT, 3800);
    add_prop(OBJ_I_VOLUME, 1100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(7) + random(24));
}
