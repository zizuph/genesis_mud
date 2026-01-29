/*
 *  IGARD_ARM + "i_largeaxe.c"
 *  Larger Isengard Axe
 *    Modified from: /d/Gondor/morgul/obj/mattock.c
 *	   Olorin, Nov 1992
 *    Last modified by Alto, 11 October 2001
 *
 */

#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public void
create_weapon() 
{
    set_name("waraxe");
    set_pname("waraxes");
    set_short("spiked steel waraxe");
    set_pshort("spiked steel waraxes");
    add_name("axe");
    set_adj("spiked");
    add_adj("steel");
    set_long("This spiked steel waraxe was forged in the smithies of Isengard. "
        + "Judging by the scent of oak still present on its handle, this "
        + "axe is almost new. The steel blade is polished to the shine of a "
        + "mirror. One side of the blade forms a long sweeping curve with "
        + "a razor edge. The other side forms a slender tapering spike.\n");
    set_default_weapon(35,38,W_AXE,W_SLASH|W_BLUDGEON,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,38)+random(600)-150);
    add_prop(OBJ_I_WEIGHT,
	       (F_WEIGHT_DEFAULT_WEAPON(35,W_AXE) + random(1000) + 500));

}
