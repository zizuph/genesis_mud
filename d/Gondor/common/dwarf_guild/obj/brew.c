/*
 * /d/Gondor/common/dwarf_guild/obj/brew.c
 *
 * Some brew that can be bought in the pub in the dwarven race guild.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/drink";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "brew")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("mug");
    add_name("brew");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("mugs");
    add_pname("brew");
    add_pname("drinks");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("mindblasting");
    add_adj("mind");
    add_adj("blasting");
    add_adj("dark");
    add_adj("mug");
    add_adj("mugs");
    add_adj("of");

    set_short("mug of mindblasting brew");
    set_pshort("mugs of brew");

    set_long(BSN("Brew! There is no other way to describe this particular " +
	"type of liquid. It is dark and there some froth on it. However, " +
	"it is not beer of any kind. It is called mindblasting for the " +
	"effect it has on your level of intoxication upon drinking."));

    set_soft_amount(450);
    set_alco_amount( 50);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 900);
    add_prop(HEAP_I_UNIT_VOLUME, 450);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}