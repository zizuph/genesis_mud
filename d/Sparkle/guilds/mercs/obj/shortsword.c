/*
 * Steel shortsword crafted by Tarn in the Mercenary guild.
 *	by Morrigan, 11 / 01
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../merc.h"

#define HIT 35
#define PEN 29

public void
create_weapon()
{
    set_name("shortsword");
    add_name(({"weapon","sword"}));
    add_name("_mercenary_shortsword_");
    set_pname("shortswords");
    add_pname(({"swords","weapons"}));
    set_adj(({"short", "steel"}));
    set_short("steel shortsword");
    set_pshort("steel shortswords");
    set_long("The shortsword is favoured for its quick striking speed and "+
	"small size, which can be easily concealed. The blade tapers gradually "+
	"to a point, and a concave groove has been carved "+
	"into the center of the blade to allow blood to escape from a wound "+
	"that the sword still fills. Though primarily a thrusting weapon, the short"+
	"sword can also be used in a slashing manner."+
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
    
    set_default_weapon(HIT,PEN, W_SWORD, W_SLASH || W_IMPALE, W_ANYH);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,30) + random(30) - 15);
}
