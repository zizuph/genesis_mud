/*
 * /d/Gondor/clubs/storytellers/obj/nuts.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(300);
    set_name("nuts");
    add_name(({ "bowl" }));
    set_adj(({ "mixed", "nut" }));
    set_short("bowl of mixed nuts");
    set_pshort("bowls of mixed nuts");
    set_long("A small bowl filled with nuts of various types.\n");

    set_nibble_max_amount(15);
}
