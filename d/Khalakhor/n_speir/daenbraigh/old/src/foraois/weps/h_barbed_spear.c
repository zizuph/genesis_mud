/* Torqual
*/

inherit "/d/Khalakhor/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

//hit/pen for this weapon
#define PEN 33 + random(3)
#define HIT 28 + random(3)

void
create_khalakhor_weapon()
{

    set_name("spear");
    add_name("polearm");
    set_short("flame-shaped ash-wood spear");
    set_long("One of the oldest and commonly used hand weapons - the spear. "+
             "The weavy, flame-shaped blade is almost 30 centimeters long "+
             "and the ash-wood shaft is ten times longer. This is "+
             "a spear which could have belonged to some heroes of legend.\n");

    set_adj("flame-shaped");
    add_adj("ash-wood");

    //those weapons were extremely useful in dealing damage
    //including breaking armour and bones
    //mostly by slashing 
    set_default_weapon(HIT,PEN,W_POLEARM,W_IMPALE,W_ANYH);
    
    add_prop(OBJ_I_VOLUME, 4400);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN));

}
