/*
 * An order confirmation for the delivery system of Thornlin
 * -- Finwe, November 2005
 *
 */

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>

inherit "/std/object";

create_object()
{
    set_name("paper");
    add_name("piece");
    add_adj("piece of");

    set_pname("papers");
    add_pname("pieces");

    set_short("piece of paper");
    set_pshort("pieces of paper");
    set_long("This is a piece of paper from the Thornlin Delivery Office. " +
        "It looks like an order  confirmation for items to be delivered.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_VOLUME, 4);
}
