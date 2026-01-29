/*
 * Slippers for Faerie Leather Shop
 * Finwe, April 2005
 *
 * Modification log:
 *   Lavellan (2011/07/11) - changed value (endless money bug otherwise)
 */

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>

inherit FOOTWEAR_BASE;

void
create_shoes()
{
    setuid(); seteuid(getuid());

    set_name("slippers");
    set_short("pair of slippers");
    set_pshort("pairs of slippers");
    add_adj(({"brown"}));
    set_long("They are made of tanned leather, which is soft and supple. " +
        "The inside of the slippers are lined with a soft fleece. The " +
        "tops are turned down exposing the ankles.\n");
    add_item(({"soft fleece", "fleece"}),
        "It is from the coat of a sheep. It is very soft and lines the " +
        "inside of the slippers. \n");
    add_prop(OBJ_I_VALUE, 30 );

}

void
leave_env(object from, object to)
{
    ::leave_env();

}

