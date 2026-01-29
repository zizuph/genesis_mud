/*
 * /d/Gondor/mordor/obj/raw_meat.c
 *
 * This is a piece of raw meat, found in the 'kitchen' at Cirith Ungol
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/std/food";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_food()
{
    set_name("meat");
    add_name("piece");
    set_adj("raw");
    add_adj("deer");
    set_short("piece of raw meat");
    set_pshort("pieces of raw meat");
    set_long("@@long_description");

    set_amount(300);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VOLUME,500);
}

/*
 * Long description
 */
string
long_description()
{
    return (BSN("This is a piece of raw meat. You have no idea what kind " +
        "of creature was slaughtered to obtain it. It looks like the meat " +
        "of a deer, but could also be from " +
        LANG_ADDART(TP->query_race_name()) + ". You realize that orcs are " +
        "not that picky about their food."));
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER;
}

void
init_recover(string arg)
{
}
