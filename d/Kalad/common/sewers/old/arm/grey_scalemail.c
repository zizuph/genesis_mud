/*
 * /d/Kalad/common/sewers/arm/grey_scalemail.c
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

#define ARMOUR_CLASS (35 + random(3))

void
create_armour()
{
::create_armour();

    set_name("scalemail");
    set_pname("scalemails");

    set_short("grey scalemail");
    set_pshort("grey scalmails");
    set_long("This is a grey scalemail, made out of dried lizardskin. " +
	     "The scales overlap eachother and behind them you notice " +
	     "a thin layer of soft leather for the wearers comfort. " +
	     "The lizardskin is thin thus making this fine peace of " +
	     "armour very light. \n");

    set_adj("grey");

// ac = 35-38
    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     3,     -3 }));

    set_at(A_BODY);

//  ac = 35-38, this will make the armours value a bit different all the
//  time, making it harder to determine how good it is... =o)

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 5) + random(10) );
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 5400 + random(200) );

return;
}
