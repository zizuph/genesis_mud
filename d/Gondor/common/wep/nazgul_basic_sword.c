/*
 *	/d/Gondor/common/wep/nazgul_sword.c
 *	Nazgul's non-magical sword
 *	--Raymundo, March 2020
 *	 
 */


#pragma strict_types

inherit "/std/weapon";
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"


void
create_weapon()
{
    set_name("shortsword");
    add_name( ({ "sword", "_nazgul_shortsword" }) );

    set_adj("black");
    add_adj("nazgul");
	add_adj("short");

    set_short("black shortsword");
    set_long("The shortsword is black as a moonless night, and yet if you look "
		+ "closely at it, you see it shines brightly. The sword is "
		+ "forged from a rare black metal, which is extremely strong. "
		+ "The pommel is in the shape of a crown, indicating that this "
		+ "blade is the personal property of a Nazgul!\n");

    set_default_weapon(50, 50, W_SWORD, W_SLASH | W_BLUDGEON, W_LEFT, TO);

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 25, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO,({
    BSN("This sword is both lightweight and powerful."), 10,
    BSN("Blessed with magical powers, it is more effective than a regular sword!"),50,
     }));
    add_prop(OBJ_S_WIZINFO, "The basic sword of the nazgul (/d/Gondor/common/npc/blackrider).\n"
      + "It's light weight and has good stats\n");

}
