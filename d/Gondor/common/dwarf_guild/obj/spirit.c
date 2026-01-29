/*
 * /d/Gondor/common/dwarf_guild/obj/spirit.c
 *
 * Spirit that can be bought in the pub in the dwarven race guild.
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

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "spirit")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("glass");
    add_name("spirit");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("glasses");
    add_pname("spirits");
    add_pname("drinks");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("firebreathing");
    add_adj("fire");
    add_adj("breathing");
    add_adj("hot");
    add_adj("glass");
    add_adj("glasses");
    add_adj("of");

    set_short("glass of firebreathing spirit");
    set_pshort("glasses of spirit");

    set_long(BSN("You wonder why this spirit is called firebreathing spirit " +
	"and you suspect that it has nothing to do with the painting of a " +
	"dragon on the bottle this spirit is sold in, or is it? Try it to " +
	"find out whether it is as hot as its name wants you to believe."));

    set_soft_amount(100);
    set_alco_amount( 40);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 400);
    add_prop(HEAP_I_UNIT_VOLUME, 200);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}