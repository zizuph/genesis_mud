/*
 * Chocolate egg for easter
 * -- Finwe, April 2007
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

inherit "/std/food";

void
create_food()
{
    set_name("egg");
    add_name("chocolate egg");
    set_pname("chocolate eggs");
    set_short("chocolate egg");
    set_pshort("chocolate eggs");
    set_long("This is a large chocolate egg. It is decorated with intricate " +
        "designs and full of sweet syrup.\n");
    set_amount(50);

}
