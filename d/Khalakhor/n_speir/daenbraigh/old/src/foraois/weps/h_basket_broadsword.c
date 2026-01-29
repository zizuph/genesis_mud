/* Torqual
*/


inherit "/d/Khalakhor/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

//hit/pen for this weapon
#define PEN 26 + random(3)
#define HIT 28 + random(3)

void
create_khalakhor_weapon()
{

    set_name("broadsword");
    add_name("sword");
    set_short("basket-hilt broadsword");
    set_long("Shorter then Claidh-mhors the broadsword is one of the " +
             "most recognizable swords used by clansmen. Well " +
             "balanced, the broad blade with sharp tip makes it " +
             "excellent cut and thrust weapon, capable of beheading " +
             "enemy while still being single-handed. The basket of steel "+
             "bars does an excellent job of protecting the hand, yet " +
             "does not add a great amount of weight. This sword is "+
             "made right-handed.\n");

    set_adj("basket-hilt");

    set_default_weapon(HIT,PEN,W_SWORD,W_SLASH|W_IMPALE,W_RIGHT);
    
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN));

}
