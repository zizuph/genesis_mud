/*
 * Dwarven scalp, all that remains from the corpse of the dwarf
 * Kirk murdered for his shadow axe.  Will be part of a quest
 * to return his remains and punish his murderer.
 *
 * Mortis 09.2006
 *
 */

inherit "/std/object";

#include "../../local.h"
#include <stdproperties.h>

#define BRIX_DWARF_SCALP		"_brix_dwarf_scalp"

void
create_object()
{
    set_name("scalp");
	add_name("remains");
    set_adj("auburn");
	set_short("auburn scalp");
    set_long("The ear of the dwarf who wore this scalp still hangs from its "
	+ "stanky, leathery flesh.  The long, shoulder length hair is somewhat "
	+ "wavy, unmistakably auburn, and still has a healthy shine.\n");

    add_prop(OBJ_I_WEIGHT, 240);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE,    0);
	add_prop(OBJ_I_NO_SELL, "Nobody wants to buy a bloody scalp, yobber!\n");
	add_prop(BRIX_DWARF_SCALP, 1);
}
