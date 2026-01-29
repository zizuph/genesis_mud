/* This is a chainmail for the gnome guards of
Rust. Made by Bishop of Calia, 11/11/98 */


inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 30

void
create_armour()
{
    set_name("chainmail");

    set_adj("double");
    set_adj("steel");

    set_short("steel double chainmail");
    set_pshort("double chainmails");

    set_long("This suit of double chainmail looks like a dependable" +
        " piece of armour. It probably hasn't seen a lot of combat" +
        " action, and has leather padding on the inside to make" +
        " it softer to wear.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);

    set_am(({ 0,0,0 }));

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}