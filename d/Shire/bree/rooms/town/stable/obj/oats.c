/*
* Oats for the bag of oats sold in Bree tack shop
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

    set_name("oats");
    set_pname("oats");
    set_adj("healthy");
    set_short("handful of oats");
    set_pshort("handfuls of oats");
    set_long("Healthy, harty oats. Horses love them.\n");
    set_amount(20);
    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
}

init()
{
    ::init();
}
