/*
* Bundles of hay sold in Bree tack shop
* Palmer
* Jan, 2003
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Shire/sys/defs.h"

void
create_food()
{
    ::create_food();

    set_name(({"hay", "bundle", "bundle of hay"}));
    set_pname("bundles of hay");
    set_adj("healthy");
    set_short("bundle of hay");
    set_pshort("bundles of hay");
    set_long("Healthy, hearty hay. Horses love it. It is golden brown " +
        "and smells sweet.\n");
    set_amount(1000);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}

init()
{
    ::init();
}
