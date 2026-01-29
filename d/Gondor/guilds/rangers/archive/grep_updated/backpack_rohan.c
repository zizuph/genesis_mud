/*
 * /d/Gondor/rohan/edoras/obj/backpack.c
 *
 * A backpack to carry stuff in. It has sell-protection.
 *
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Modified for the Rangers by Elessar, May 1994.
 * Modified to use create_backpack() by Gnadnar, Nov 1997.
 */

inherit "/d/Gondor/guilds/rangers/obj/backpack";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include "/d/Gondor/defs.h"

void
create_backpack()
{
    set_name("backpack");
    add_name("pack");
    add_name("rucksack");
    add_name("knapsack");

    set_pname("backpacks");
    add_pname("packs");
    add_pname("rucksacks");
    add_pname("knapsacks");

    add_adj("large");
    add_adj("brown");
    add_adj("canvas");

    set_short("large canvas backpack");
    set_pshort("backpacks");

    set_backpack_long("The backpack is rather large and made of canvas. ");

    add_prop(OBJ_I_VALUE, 576);
}
