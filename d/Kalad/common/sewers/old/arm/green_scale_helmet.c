/*
 * /d/Kalad/common/sewers/arm/green_scale_helmet.c
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

    set_name("helmet");
    set_pname("helmets");

    set_short("green scale helmet");
    set_pshort("green scale helmets");
    set_long("This is a green scale helmet, made out of dried " +
	     "lizardskin. The scales overlap eachother in a " +
	     "perfect way, and under them you notice a thin " +
	     "layer of soft leather for the wearers comfort. " +
   	     "There is a leather strap to hold the helmet on the head. " +
	     "The lizardskin is thin thus making this fine peace of " +
	     "armour very light. \n");

    set_adj("green");
    set_adj("scale");

// ac = 17-20
    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     2,     -2 }));

    set_at(A_HEAD);

//  ac = 17- 20, this will make the armours value a bit different all the
//  time, making it harder to determine how good it is... =o)

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 5) + random(10) );
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 500 + random(200) );

return;
}
