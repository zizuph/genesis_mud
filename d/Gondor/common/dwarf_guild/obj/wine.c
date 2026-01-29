/*
 * /d/Gondor/common/dwarf_guild/obj/wine.c
 *
 * A glass of wine that can be bought in the pub in the dwarven race guild.
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

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "wine")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("glass");
    add_name("wine");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("glasses");
    add_pname("wine");
    add_pname("wines");
    add_pname("drinks");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("sparkling");
    add_adj("white");
    add_adj("glass");
    add_adj("glasses");
    add_adj("of");

    set_short("glass of sparkling white wine");
    set_pshort("glasses of wine");

    set_long(BSN("It is a glass of white wine. The wine is sparkling and " +
	"imported from some country far away. The bubbles in the wine " +
	"sparkle all around your head when you drink it. Properly chilled " +
        "it is a great beverage when you have something to celebrate."));

    set_soft_amount(100);
    set_alco_amount( 13);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 500);
    add_prop(HEAP_I_UNIT_VOLUME, 250);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}
