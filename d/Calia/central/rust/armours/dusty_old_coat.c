/* This is a old gnome Jessup's coat.
Created by Bishop of Calia 6/11/98 */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 5

void
create_armour()
{
    set_name("coat");

    set_adj("grey");
    set_adj("dusty");

    set_short("grey dusty coat");
    set_pshort("dusty coats");

    set_long("This grey coat looks decades old. Only half of the buttons" +
        " on it are left.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));
}