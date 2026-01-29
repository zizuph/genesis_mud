/*
 * Armour from the Newerwinter Gates
 * -- Kehr, December 2006
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "wooden"
#define ADJ2        "heater"
#define ARMOUR      "shield"
#define BOD_TYPE    A_SHIELD
#define AC_MOD      -3,1,2

int ac =  25 + random(10);

void 
create_faerun_armour()
{
	int tmp;
    set_name("shield");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR);
    set_long("This " + short() + " was made from several layers of laminated " +
    	"wood and reinforced with a steel frame, which makes the shield both " +
    	"light while still providing an excellent protection. The shield is " +
    	"decorated with the painting of a sword on red and blue background. " + 
        "The shield is heater shaped and seems to be in an excellent condition.\n");

    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    tmp = F_VALUE_ARMOUR(ac)/2;
    // guaranteed - the price will never be lower than 3/4 of F_VALUE_ARMOUR(ac)
    // but might be up to 2 times higher, with semi-gaussian distribution 
    // around F_VALUE_ARMOUR  
    add_prop(OBJ_I_VALUE, min(tmp*3/2, random(tmp) + random(tmp) + random(tmp) + random(tmp)));
}

public int *
query_shield_slots()
{
    if (query_at() & A_SHIELD)
    {
        return (::query_shield_slots() + ({ A_BODY}) );
    }

    return ::query_shield_slots();
}
    