/* Torqual
*/


inherit "/d/Khalakhor/std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

//hit/pen for this weapon
#define PEN 33 + random(3)
#define HIT 36 + random(3)

void
create_khalakhor_weapon()
{

    set_name("spear");
    add_name("polearm");
    set_short("long leaf-tipped spear");
    set_long("The spear consist of long, slender shaft made out of " +
             "hardened wood and leaf-shaped tip made of hammered iron. " +
             "This simple weapon is favoured for its lenght and accuracy.\n");

    set_adj("long");
    add_adj("leaf-tipped");

    set_default_weapon(HIT,PEN,W_POLEARM,W_IMPALE,W_BOTH);
    
    add_prop(OBJ_I_VOLUME, 4600);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN));

}
