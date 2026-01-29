/*
 * /d/Kalad/common/sewers/arm/green_scale_sleeves.c
 * Purpose    : Common armours of sewers.
 * Located    : In sewers, worn by thieves and lizards.
 * Created By : Sir Toby, 97-06-23
 * Modified By: 
 * First Modif: 
 */


#pragma strict_types

inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define ARMOUR_CLASS (15 + random(3))

void
create_armour()
{
::create_armour();

    set_name("sleeves");
    set_pname("sleeves");

    set_short("green scale sleeves");
    set_pshort("green scale sleeves");
    set_long("This is a pair of green scale sleaves, made out of dried " +
	     "lizardskin. The scales overlap eachother in a " +
	     "perfect way, and under them you notice a thin " +
	     "layer of soft leather for the wearers comfort. " +
             "There are leather straps to hold them in place. " +
	     "The lizardskin is thin thus making this fine peace of " +
	     "armour very light. \n");

    set_adj("green");
    set_adj("scale");

// ac = 15-18
    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     2,     -2 }));

    set_at(A_ARMS);

//  ac = 15-18, this will make the armours value a bit different all the
//  time, making it harder to determine how good it is... =o)

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 3) + random(10) );
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 450 + random(150) );

return;
}
