/*
 * Steel mace crafted by Tarn in the Mercenary guild.
 *	by Morrigan, 11 / 01
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../merc.h"

#define HIT 32
#define PEN 32

public void
create_weapon()
{
    set_name("mace");
    add_name(({"weapon","club"}));
    add_name("_mercenary_mace_");
    set_pname("maces");
    add_pname(({"clubs","weapons"}));
    set_adj(({"slender", "steel"}));
    set_short("steel mace");
    set_pshort("steel maces");
    set_long("The mace is the most common club, consisting of a slender shaft "+
	"at the end of which is a striking surface of some sort. This mace "+
	"has a six-sided, diamond-shaped, flared head which is somewhat sharp "+
	"at its broadest points. "+
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
