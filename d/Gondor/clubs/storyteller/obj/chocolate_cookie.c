/*
 * /d/Gondor/clubs/storytellers/obj/chocolate_cookie.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(100);
    set_name("cookie");
    set_adj(({ "chocolate" }));
    set_short("chocolate cookie");
    set_pshort("chocolate cookies");
    set_long("A delicious chocolate cookie, ready to be eaten!\n");

    set_nibble_max_amount(5);
}
