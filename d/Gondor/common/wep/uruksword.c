/* 
 *	/d/Gondor/common/wep/uruksword.c
 *
 *	Olorin, Nov 1992
 *
 *	Cloned by:
 *	/d/Gondor/common/npc/reuruk.c
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon() 
{
    set_name( ({ "longsword", "sword", "weapon", }) );
    set_pname("longswords");
    add_pname("swords");
    set_short("orkish longsword");
    set_pshort("orkish longswords");
    set_long(BS("This is an longsword forged of steel, evidently by some orc smithies. "
        + "But the crude design and workmanship do not make it any less dangerous. "
        + "The blade is very sharp, and it is well balanced. The hilt is adorned "
        + "with what looks like a crude depiction of an eye.\n"));
    // removed adjective "orc" on purpose, Olorin, 9-Feb-1997
    set_adj( ({ "orkish", "long", "sharp", "crude" }) );
    set_default_weapon(25,30,W_SWORD,W_SLASH|W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,30) + random(501));
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(25, W_SWORD) + random(1000)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
}
