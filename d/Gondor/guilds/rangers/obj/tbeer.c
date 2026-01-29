/*
 * /d/Gondor/guilds/rangers/obj/tbeer.c
 *
 * Coded by ?
 *
 * Modification log:
 *   Gwyneth, 6 May 2004, updated
 */
inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_name(({"mug", "beer"}));
    set_pname(({"mugs", "beers"}));
    set_adj("prime");
    set_short("mug of prime beer");
    set_pshort("pints of prime beer");
    set_long("The beer of the house is of prime quality. It was brewn in " +
        "the basement of the tavern.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(110);
    set_alco_amount(8);
    add_prop(OBJ_I_WEIGHT, 540);
    add_prop(OBJ_I_VOLUME, 540);
}
