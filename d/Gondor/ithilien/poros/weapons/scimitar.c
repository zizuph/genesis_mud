/*
 *   /d/Gondor/ithilien/poros/obj/scimitar.c
 *
 *   This is the scimitar used by the corsair's Haradan jailer.
 *
 *   Talisan,  January 1996
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"scimitar", "sword"}));
    set_short("high-steel scimitar");
    set_pshort("high-steel scimitars");
    set_long("This scimitar has been crafted from the finest of steels. "
      + "The blade is undoubtably a product of a superior smith, its "
      + "edge is razor sharp. An intricately engraved golden hilt, with "
      + "a dangling red tassle, marks this as a weapon of the Haradrim "
      + "Royal Guards.\n");
    set_adj(({"fine", "high steel", "high-steel", "steel", "haradrim",
        "haradan", "gold hilted", "sharp", "razor sharp", "razor edged"}));

    set_default_weapon(32,29, W_SWORD,W_SLASH,W_ANYH, 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(29, W_SWORD));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(32,29) + random(400) - 200);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
