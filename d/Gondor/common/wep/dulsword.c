/* The typical longsword of the Dunlendings */
/*  General update, April 1997 by Gorboth. */
/*  Last update: April 16, 2000, bugfix by Stern */

#pragma strict_types;

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name( ({ "sword",  "longsword" }));
    set_pname( ({ "swords", "longswords" }));
    set_short("dunlending longsword");
    set_pshort("dunlending longswords");
    set_long(BSN("This is a heavy longsword with a black double-edged blade. "
      + "Swords such as this are often used by the dunlendings, yet it "
      + "is not known to the men of Rohan where they are made."));
    set_adj("dunlending");
    add_adj("long");
    add_adj("black");
    add_adj("double-edged");
    add_adj("heavy");
    set_default_weapon(35, 35, W_SWORD, W_SLASH | W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(35, W_SWORD) + 2000 + random(2000)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35) * (110 + random(21)) / 100);
}
