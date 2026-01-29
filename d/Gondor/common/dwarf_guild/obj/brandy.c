/*
 * /d/Gondor/common/dwarf_guild/obj/brandy.c
 *
 * A glass of brandy that can be bought in the pub in the dwarven race guild.
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

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "brandy")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("glass");
    add_name("brandy");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("glasses");
    add_pname("brandy");
    add_pname("drinks");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("hot");
    add_adj("lemon");
    add_adj("glass");
    add_adj("glasses");
    add_adj("of");

    set_short("glass of hot lemon brandy");
    set_pshort("glasses of brandy");

    set_long(BSN("It is a glass of brandy. Smelling the brandy you can " +
	"tell that it contains lemon and it has a rather strong smell."));

    set_soft_amount(150);
    set_alco_amount( 20);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 500);
    add_prop(HEAP_I_UNIT_VOLUME, 250);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}