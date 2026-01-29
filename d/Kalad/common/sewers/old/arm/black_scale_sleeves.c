/*
 * /d/Kalad/common/sewers/arm/black_scale_sleeves.c
 * Purpose    : Worn by a bit stronger guards deeper in the lizard caves.
 * Located    : Guards in lizardcaves
 * Created By : Sir Toby, 97-07-31
 * Modified By: 
 * First Modif: 
 */

#pragma strict_types

inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define ARMOUR_CLASS (37 + random(5))

void
create_armour()
{
::create_armour();

    set_name("sleeves");
    set_pname("sleeves");

    set_short("black scale sleeves");
    set_pshort("black scale sleeves");
    set_long("This is a pair of black scale sleaves, made out of dried " +
	     "lizardskin. The scales overlap eachother in a " +
	     "perfect way, and under them you notice a thin " +
	     "layer of soft leather for the wearers comfort. " +
             "There are leather straps to hold them in place. " +
	     "The lizardskin is thin thus making this fine peace of " +
	     "armour very light. \n");

    set_adj("black");
    set_adj("scale");

    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     2,     -1 }));

    set_at(A_ARMS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 3) + random(10) );
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 450 + random(150) );

    if(ARMOUR_CLASS >= 40)
	{
	add_prop(OBJ_M_NO_BUY,1);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
	add_prop(OBJ_S_WIZINFO,"The armour is not magic but the " +
		"randompart might take it above 40 in ac.\n");
	}
return;
}
