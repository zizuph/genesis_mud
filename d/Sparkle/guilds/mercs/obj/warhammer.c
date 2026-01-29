/*
 * Steel warhammer crafted by Tarn in the Mercenary guild.
 *	by Morrigan, 11 / 01
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../merc.h"

#define HIT 29
#define PEN 35

public void
create_weapon()
{
    set_name("warhammer");
    add_name(({"weapon","warhammer"}));
    add_name("_mercenary_warhammer_");
    set_pname("warhammers");
    add_pname(({"clubs","weapons"}));
    set_adj(({"heavy", "steel"}));
    set_short("steel warhammer");
    set_pshort("steel warhammers");
    set_long("The warhammer is a weapon favoured for its powerful striking "+
	"power which comes from the hammer-shaped head being much heavier than "+
	"the rest of the weapon. This warhammer has a large brick-shaped head "+
	"that can be used to strike in either direction. "+
        "The hilt is fashioned of "+
	"dark wood, surrounded by brass rings at each end. The end of the hilt "+
	"has a brass sphere attached, which has a dragon etched into its "+
	"surface. The base of the blade has some small letters which have been "+
	"burned on.\n");

    add_item(({"hilt", "handle", "wood", "rings"}), "The hilt is made from carved "+
	"dark wood, which has a ring of polished brass on each end of it.\n");
    add_item(({"sphere", "dragon"}), "Etched into the sphere at the base of the "+
	"weapon is a dragon with wings spread wide.\n");
    add_item(({"letters", "lettering"}), "The letters spell plainly: Tarn "+
	"Stonehammer.\n");
    
    set_default_weapon(HIT,PEN, W_CLUB, W_BLUDGEON, W_ANYH);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,30) + random(30) - 15);
}
