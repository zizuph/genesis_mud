/*
 * /d/Gondor/clubs/storytellers/obj/cheese.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(50);
    set_name("cheese");
    set_adj(({ "piece" }));
    set_short("piece of cheese");
    set_pshort("pieces of cheese");
    set_long("A small piece of cheddar cheese.\n");

    set_nibble_max_amount(3);
}
