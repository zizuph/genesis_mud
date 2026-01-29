/*
 * /d/Gondor/common/dwarf_guild/obj/shandy.c
 *
 * Shandy that can be bought in the pub in the dwarven race guild.
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

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "shandy")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("shandy");
    add_name("mug");
    add_name("soda");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("drinks");
    add_pname("mugs");
    add_pname("soda");
    add_pname("shandy");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("sweet");
    add_adj("mug");
    add_adj("mugs");
    add_adj("of");

    set_short("mug of sweet shandy");
    set_pshort("mugs of shandy");

    set_long(BSN("It is a mug of shandy. Shandy is made by mixing beer and " +
	"soda on a 50-50 basis. The beer is of dwarvish origine. Shandy is " +
	"a drink that is drunk by children to have the taste of beer " +
	"without the full amount of alcohol."));

    set_soft_amount(300);
    set_alco_amount(  3);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 1000);
    add_prop(HEAP_I_UNIT_VOLUME,  800);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}
