/*
 * /d/Gondor/clubs/storytellers/obj/roll.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(200);
    set_name("roll");
    set_adj(({ "soft", "butter" }));
    set_short("soft butter roll");
    set_pshort("soft butter rolls");
    set_long("A roll that smells of bread and butter, and is very soft "+
	"and fluffy.\n");

    set_nibble_max_amount(10);
}
