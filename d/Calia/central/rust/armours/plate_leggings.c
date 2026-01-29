/* This is a leggings for the gnome guards of
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
    set_name("leggings");

    set_adj("plate");
    set_adj("polished");
    set_adj("pair of");

    set_short("pair of polished plate leggings");
    set_pshort("banded leggings");

    set_long("These well-kept leggings consist of plates covering" +
        " the front and back of your legs, with leather padding" +
        " underneath to keep them from eating into your skin.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);

    set_am(({ 0,0,0 }));

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}