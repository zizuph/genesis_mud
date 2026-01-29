/*
 * Steel longsword crafted by Tarn in the Mercenary guild.
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
    set_name("longsword");
    add_name(({"weapon","sword"}));
    add_name("_mercenary_longsword_");
    set_pname("longswords");
    add_pname(({"swords","weapons"}));
    set_adj(({"long", "steel"}));
    set_short("steel longsword");
    set_pshort("steel longswords");
    set_long("The longsword is the most common of all swords, being favoured "+
	"for its exceptional reaching distance and light weight. The blade "+
	"tapers gradually to a point, and a concave groove has been carved "+
	"into the center of the blade to allow blood to escape from a wound "+
	"that the sword still fills. "+
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
