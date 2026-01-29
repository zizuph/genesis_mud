/*
 * /d/Gondor/common/wep/dubsword.c
 * 
 * The typical broadsword of the Dunlendings 
 *
 * Coded by Olorin, December 1992
 * Modification log:
 * 29-Jun-1997, Olorin: general revision.
 */
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon() 
{
    set_name(({"sword","weapon","broadsword"}));
    set_short("dunlending broadsword");
    set_pname("broadswords");
    add_pname("swords");
    set_pshort("dunlending broadswords");
    set_long(BSN("This is a sword with a broad, black blade. " +
	"Swords like this are often used by the dunlendings, " +
        "but it is unknown in Rohan where they are made."));
    set_adj("dunlending");
    add_adj("black");
    add_adj("broad");
    set_default_weapon(28, 31, W_SWORD, W_SLASH|W_BLUDGEON, W_RIGHT, 0);
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(31, W_SWORD) * (110 - random(21)) / 100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 31) * (110 + random(21)) / 100);
}
