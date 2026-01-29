/*
 * Shoes for Faerie Leather Shop
 * Finwe, April 2005
 */

#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit FOOTWEAR_BASE;


void
create_shoes()
{
    setuid(); seteuid(getuid());

    set_name("shoes");
    set_short("pair of black shoes");
    set_pshort("pairs of black shoes");
    set_long("They are made from black leather and fit over the feet " +
        "and come up to the top of the ankle. A large " +
        "square brass buckle is on the front of each shoe. A short " +
        "heel is at the back and bottom of each shoe.\n");
    add_adj(({"black"}));
    add_item(({"buckle", "square buckle", "square brass buckle", 
            "brass buckle"}),
        "The buckle is square and made of brass. It is ornamental " +
        "and is attached at the top and front of each shoe.\n");
    add_item(({"heel", "short heel"}),
        "The heel is square and short It is made of wood, painted " +
        "black. It is attached to the bottom of each shoe.\n");
}

void
leave_env(object from, object to)
{
    ::leave_env();

}

