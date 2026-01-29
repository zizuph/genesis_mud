/*
 * /d/Gondor/morgul/obj/backpack.c
 *
 * A backpack to carry stuff in. It has sell-protection.
 *
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Modified for the Rangers by Elessar, May 1994.
 */

#pragma save_binary

inherit "/d/Gondor/common/guild/obj/backpack";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_backpack()
{
    set_name("backpack");
    add_name("pack");
    add_name("rucksack");
    add_name("knapsack");

    set_pname("sacks");
    add_pname("backpacks");
    add_pname("packs");
    add_pname("rucksacks");
    add_pname("knapsacks");

    add_adj(({"black", "canvas"}));
    set_short("black canvas backpack");
    set_pshort("backpacks");

    set_backpack_long("The backpack is rather large and made of black canvas.");

    add_prop(OBJ_I_VALUE,             720);
}
