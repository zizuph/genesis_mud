/*
 * Holiday food from Bree
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

    set_name("dropping");
    add_name("reindeer dropping");
    add_pname("reindeer droppings");
    add_pname("droppings");
    set_adj("brown");
    set_short("brown reindeer dropping");
    set_pshort("brown reindeer droppings");
    set_long("This is a reindeer dropping. It is really a large chocolate " +
        "covered raisin. The dropping is large, about thumb-size and " +
        "covered with dark chocolate. It is a holiday favorite.\n");
    set_amount(9); 
}
