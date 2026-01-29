/* 
 * File: dog_pelt_b.c
 * A pelt of cooshee. Increases player's ability to hide a bit.
 * 
 * Blizzard, 02/2003
 *
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * An unlimited amount of armours that improve hide is not acceptable.
 * It is coded as a leftover, and the magical abilities has been removed.
 */

inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("pelt");
    add_name("cloak");
    set_short("warm dark-brown pelt");
    add_adj(({ "warm", "dark-brown", "brown" }));
    set_ac(10);
    set_at(A_ROBE);
    set_af(TO);
    set_keep(1);
    
    set_long("This is a warm dark-brown pelt. It was cut from the corpse " +
        "of a wild dog. The hound, thanks to his natural coloration, could " +
        "camouflage in woodlands very well.\n");
       
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) + random(200) + 300);
}
