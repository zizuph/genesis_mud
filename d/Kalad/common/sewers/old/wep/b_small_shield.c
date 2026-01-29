/*
 * /d/Kalad/common/sewers/arm/b_shied.c
 * Purpose    : Worn by thieves and lizards in the sewers
 * Located    : In lizard caves and sewers
 * Created By : Sir Toby, 97-07-31
 * Modified By: 
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

    set_name("shield");
    set_pname("shields");

    set_short("black steel shied");
    set_pshort("black steel shields");
    set_long("This is a small black steel shield. " +
	     "It has nicly made leatherstraps making " +
	     "it very comfortable to wear.\n");

    set_adj("small");
    set_adj("black");
    set_adj("steel");

    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     1,     -1 }));

    set_at(A_SHIELD);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 5) + random(10) );
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 500 + random(200) );

return;
}
