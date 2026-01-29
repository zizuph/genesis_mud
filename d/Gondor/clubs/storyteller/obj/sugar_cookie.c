/*
 * /d/Gondor/clubs/storytellers/obj/sugar_cookie.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(100);
    set_name("cookie");
    set_adj(({ "sugar" }));
    set_short("sugar cookie");
    set_pshort("sugar cookies");
    set_long("A delicious sugar cookie, ready to be eaten!\n");

    set_nibble_max_amount(5);
}
