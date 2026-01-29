/*
 * /d/Gondor/common/dwarf_guild/obj/liquor.c
 *
 * A glass of liquor that can be bought in the pub in the dwarven race guild.
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

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "liquor")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("glass");
    add_name("liquor");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("glasses");
    add_pname("liquor");
    add_pname("drinks");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("mellow");
    add_adj("green");
    add_adj("glass");
    add_adj("glasses");
    add_adj("of");

    set_short("glass of mellow green liquor");
    set_pshort("glasses of liquor");

    set_long(BSN("The liquor has a deep green colour. It looks rather " +
	"poisonous, however is has a very mellow taste and it will help " +
	"you to recover from whichever perils you have been through."));

    set_soft_amount(100);
    set_alco_amount( 30);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 400);
    add_prop(HEAP_I_UNIT_VOLUME, 200);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}