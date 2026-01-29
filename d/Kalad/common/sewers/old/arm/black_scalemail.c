/*
 * /d/Kalad/common/sewers/arm/black_scalemail.c
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

#define ARMOUR_CLASS (41 + random(3))

void
create_armour()
{
::create_armour();

    set_name("scalemail");
    set_pname("scalemails");

    set_short("black scalemail");
    set_pshort("black scalmails");
    set_long("This is a black scalemail, made out of dried lizardskin. " +
	     "The scales overlap eachother and behind them you notice " +
	     "a thin layer of soft leather for the wearers comfort. " +
	     "The lizardskin is thin thus making this fine peace of " +
	     "armour very light. \n");

    set_adj("black");
    add_adj("scale");

    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     3,     -1 }));

    set_at(A_BODY);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 5) + random(10) );
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 5400 + random(200) );

    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(OBJ_S_WIZINFO,"The armour is not magic, only high ac.\n");

return;
}
