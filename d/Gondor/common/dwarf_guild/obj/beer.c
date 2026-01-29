/*
 * /d/Gondor/common/dwarf_guild/obj/beer.c
 *
 * A beer that can be bought in the pub in the dwarven race guild.
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

#define DRINK_ID  (DWARVEN_RACE_GUILD_PREFIX + "drink")
#define DRINK_PID (DRINK_ID + "s")

void
create_drink()
{
    set_name("beer");
    add_name("mug");
    add_name("drink");
    add_name(DRINK_ID);

    set_pname("beers");
    add_pname("mugs");
    add_pname("drinks");
    add_pname("booze");
    add_pname(DRINK_PID);

    set_adj("tasteful");
    add_adj("light");
    add_adj("mug");
    add_adj("mugs");
    add_adj("of");

    set_short("mug of tasteful light beer");
    set_pshort("mugs of beer");

    set_long(BSN("This mug of beer is of dwarvish origin. It is a light, " +
        "tasteful beer, brewed to drink when you are thirsty."));

    set_soft_amount(300);
    set_alco_amount(  6);

    remove_prop(OBJ_I_VALUE);
    remove_prop(HEAP_I_UNIT_VALUE);
    add_prop(HEAP_I_UNIT_WEIGHT, 1000);
    add_prop(HEAP_I_UNIT_VOLUME,  800);
    add_prop(OBJ_M_NO_SELL, BSN("Drinks are not to be re-sold."));
}
