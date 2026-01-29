/* This is the old wanderers coatcoat.
Created by Bishop of Calia 9/3/99 */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "../pond.h"

#define ARMOUR_CLASS 4

void
create_armour()
{
    set_name("coat");

    set_adj("fur");
    set_adj("thick");

    set_short("thick fur coat");
    set_pshort("fur coats");

    set_long("This warm and comfortable-looking coat seems to have" +
        " been made out of a single pelt from a large animal," +
        " possibly a bear. Cotton strings are used to keep it snug" +
        " around the body.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 1500);
}