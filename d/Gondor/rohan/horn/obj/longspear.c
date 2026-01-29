/* Weapon coded by Arren, June 93 */

inherit "/std/weapon"; 

#include <macros.h>      
#include <stdproperties.h>
#include <wa_types.h>      
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("spear");
    add_name(({"long-spear", "polearm" }));
    set_short("long spear");
    set_long(BSN("The spear has an eight foot shaft made "+ 
    "of ash. The head has an ox-tongue shape with two small wings added. "+
    "This spear is too heavy and unwieldy to throw with good result. "));

    set_adj("long");
    add_adj(({ "ox-tongue", "Rohirrim" }));

    set_default_weapon(23, 19, W_POLEARM, W_IMPALE, W_BOTH, 0);

    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(23,19)+random(100)-50);
}
