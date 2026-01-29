/*
 *   /d/Gondor/ithilien/poros/obj/silver_sword.c
 *
 *   This is the sword that is used by the corsair 1st mate.
 *
 *   Talisan  January 1996
 *   Modification log:
 *   Gwyneth - Added more verbose set_pshort 4/1/01
 *   Alto - fixed typo in set_long()
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
    set_name(({"longsword", "long sword", "sword", "ithilnaur"}));
    set_short("silver longsword");
    set_pshort("silver longswords");
    set_long("This is an exceptionally well crafted longsword. "
      + "The blade is an alloy composite of mithril and other metals, "
      + "giving the weapon a silvery appearance. "
      + "Along the weapon's blade, ancient Quenya "
      + "runes have been delicately inscribed.\n");
    set_adj(({"silver", "quenya", "exceptional", "elvish", "elven"}));

   set_default_weapon(32,30, W_SWORD,W_SLASH|W_IMPALE,W_ANYH, 0);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(32,30) + random(250) + 400);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(32, W_SWORD) - 500));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);

    add_item(({"rune", "runes", "quenya runes"}), BSN(
        "// ITHILNAUR //"));
}
