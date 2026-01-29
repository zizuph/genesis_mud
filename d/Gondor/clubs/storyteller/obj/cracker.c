/*
 * /d/Gondor/clubs/storytellers/obj/cracker.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(100);
    set_name("cracker");
    set_adj(({ "salty" }));
    set_short("salty cracker");
    set_pshort("salty crackers");
    set_long("A big salty cracker, ready to be eaten.\n");

    set_nibble_max_amount(5);
}
