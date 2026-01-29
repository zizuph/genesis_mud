/*
 * /d/Gondor/common/dwarf_guild/obj/juice.c
 *
 * Orange juice that can be bought in the pub in the dwarven race guild.
 *
 * /Mercade, May 5 1995
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/drink";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "juice")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("juice");
    add_name("mug");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("drinks");
    add_pname("mugs");
    add_pname("juice");
    add_pname(DRINK_PID);

    set_adj("orange");
    add_adj("mug");
    add_adj("mugs");
    add_adj("of");

    set_short("mug of orange juice");
    set_pshort("mugs of juice");

    set_long(BSN("It is a mug of orange juice, made of oranges brought in " +
	"from the Shire. Properly chilled it is a refreshing drink."));

    set_soft_amount(200);
    set_alco_amount(  0);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 1000);
    add_prop(HEAP_I_UNIT_VOLUME,  800);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}