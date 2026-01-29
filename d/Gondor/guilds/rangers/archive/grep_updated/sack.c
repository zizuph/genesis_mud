/*
 * /d/Gondor/morgul/obj/sack.c
 *
 * A sack to carry stuff in. It has sell-protection.
 *
 * Inherited file by
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Modified for the Rangers by Elessar, May 1994.
 */
inherit "/d/Gondor/guilds/rangers/obj/backpack";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_backpack()
{
    set_name("sack");
    add_name("pack");

    set_pname("sacks");
    add_pname("packs");

    add_adj("large");
    add_adj("brown");

    set_short("large brown sack");

    add_prop(OBJ_I_VALUE,             720);
	add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    set_fill_verb("fillsack");
    set_empty_verb("emptysack");

    set_backpack_long("The sack is rather large and made from "
      + "the hide of a hobbit.");
}

