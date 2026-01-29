/* Torqual
*/


inherit "/d/Khalakhor/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

//hit/pen for this weapon
#define PEN 22 + random(3)
#define HIT 23 + random(3)

void
create_khalakhor_weapon()
{

    add_name("sword");
    set_short("bronze hilted short sword");
    set_long("The always favored weapon of all times is craftily made " +
             "of quality iron. Richly decorated bronze hilt is shaped " +
             "after human figure with outstretched arms-like protectors "+
             "and a head as counterweight. The short, quick blade is "+
             "well-suited for the hand-to-hand combat.\n");

    set_adj("short");
    add_adj("bronze hilted");

    //those weapons were extremely useful in dealing damage
    //including breaking armour and bones
    //mostly by slashing 
    set_default_weapon(HIT,PEN,W_SWORD,W_SLASH,W_ANYH);
    
    add_prop(OBJ_I_VOLUME, 2600);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN));

}
