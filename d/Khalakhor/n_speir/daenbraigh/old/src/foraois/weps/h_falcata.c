/* Torqual
 * Falcata - one of more dreaded swords of that era
 * one or rarely two-edged weapon capable of breaking
 * armours and shields
*/


inherit "/d/Khalakhor/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

//hit/pen for this weapon
#define PEN 33 + random(3)
#define HIT 31 + random(3)

void
create_khalakhor_weapon()
{

    set_name("falcata");
    add_name("sword");
    set_short("sickle-shaped iron falcata");
    set_long("The falcata has a one edged blade that pitches forward " +
             "towards the point, the edge being concave on the lower " +
             "part of the sword, but convex on top. The hilt is " + 
             "hook-shaped, the end being stylized in the shape of " +
             "a horse. For better grip the hilt is wrapped with rough " +
             "piece of a leather and there is also a thin chain " +
             "connecting the tip of the hilt with the upper section.\n");

    set_adj("sickle-shaped");
    add_adj("iron");

    //those weapons were extremely useful in dealing damage
    //including breaking armour and bones
    //mostly by slashing 
    set_default_weapon(HIT,PEN,W_SWORD,W_SLASH,W_ANYH);
    
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));

}
