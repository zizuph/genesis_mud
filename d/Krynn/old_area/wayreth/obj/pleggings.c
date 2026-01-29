/* Practice leggings for Gelnor the Gruff 
 * of Wayreth Tower
 * Created by: Kentari 01/97
 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

void
create_armour()
{
    set_name("leggings");
    set_ac(16);
    set_at(A_LEGS);
    set_am( ({ 0, 2, -2 }) );
    add_adj("gray");
    add_adj("practice");
    set_short("pair of gray practice leggings");
    set_pshort("pairs of gray practice leggings");
    set_long("Made of a comfortable gray material, these are " +
		"perfect for hours of practicing and sweating. " +
		"You notice an extremely light, yet strong mesh " +
		"of metal on the inside of the leggings, which " +
		"must provide wonderful protection against blades.\n");
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(16) + 200);
}

