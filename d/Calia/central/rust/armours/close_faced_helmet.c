/* This is a helmet for the gnome guards of
Rust. Made by Bishop of Calia, 11/11/98 */


inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 27

void
create_armour()
{
    set_name("helmet");
    add_name("helm");

    set_adj("steel");
    set_adj("close-faced");

    set_short("close-faced helmet");
    set_pshort("close-faced helmets");

    set_long("This steel helmet has a T-shaped opening in front," +
        " allowing unobstructed vision and speaking. It looks like" +
        " a sturdy helmet.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);

    set_am(({ 0,0,0 }));

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}