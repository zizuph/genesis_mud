/*
 * /d/Kalad/common/sewers/arm/grey_scale_helmet.c
 * Purpose    : Worn by a bit stronger guards deeper in the lizard caves.
 * Located    : Guards in lizardcaves
 * Created By : Sir Toby, 97-07-07
 * Modified By: 
 * First Modif: 
 */


#pragma strict_types

inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define ARMOUR_CLASS (30 + random(3))

void
create_armour()
{
::create_armour();

    set_name("helmet");
    set_pname("helmets");

    set_short("grey scale helmet");
    set_pshort("grey scale helmets");
    set_long("This is a grey scale helmet, made out of dried " +
	     "lizardskin. The scales overlap eachother in a " +
	     "perfect way, and under them you notice a thin " +
	     "layer of soft leather for the wearers comfort. " +
   	     "There is a leather strap to hold the helmet on the head. " +
	     "The lizardskin is thin thus making this fine peace of " +
	     "armour very light. \n");

    set_adj("grey");
    set_adj("scale");

// ac = 30-33
    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     2,     -2 }));

    set_at(A_HEAD);

//  ac = 30-33, this will make the armours value a bit different all the
//  time, making it harder to determine how good it is... =o)

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 5) + random(10) );
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 500 + random(200) );

return;
}
