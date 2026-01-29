/*
 * /d/Gondor/clubs/storytellers/obj/fruit.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(300);
    set_name("fruit");
    add_name(({ "bowl" }));
    set_adj(({ "fresh", "fruit" }));
    set_short("bowl of fresh fruit");
    set_pshort("bowls of fresh fruit");
    set_long("A small bowl filled with fresh fruit.\n");

    set_nibble_max_amount(15);
}
