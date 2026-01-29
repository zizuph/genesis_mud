/*
 * Holiday foods for Bree
 * Finwe, December 2002
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("fruitcake");
    set_adj("sweet");
    set_short("slice of fruitcake");
    set_long("This is a slice of fresh fruitcake. It is dark " +
        "and cake-like, made from dried cherries, currents, and " +
        "cranberries and chopped pecans.\n");
    set_amount(50); 
}
