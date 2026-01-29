/* Weapon coded by Arren, June 93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("sword");
    set_short("Rohirrim long sword"); 
    set_long(BS("The sword is long and bright, and there are green "+
    "gems set in the hilt. This is a typical sword of the Westfold Men.\n"));

    set_adj("long");
    add_adj("rohirrim");

    set_default_weapon(29, 25, W_SWORD, W_IMPALE | W_SLASH, W_RIGHT, 0);
    
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_VOLUME, 1100);
}
