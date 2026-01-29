/*
 * /d/Gondor/clubs/storytellers/obj/cheese.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit FOOD_BASE;

void
create_st_food()
{
    set_amount(1000);
    set_name("elf");
    add_name("snack");
    add_name("corpse");
    set_adj(({ "warm", "dead", "elf" }));
    set_short("still-warm corpse of an elf");
    set_pshort("still-warm corpses of elves");
    set_long("This is the corpse of an elf, that has been recently killed "+
	"because it is still warm. You have an urge to 'nibble' on it.\n");

    set_nibble_max_amount(10);
}
