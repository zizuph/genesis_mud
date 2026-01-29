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


#define ADJ1    	"brown"
#define ADJ2    	"leather"
#define ARMOUR      "gloves"
#define BOD_TYPE    A_ARMS
#define AC_MOD      0,0,0

// 35+/-5
int ac = 30+random(3)+random(4)+random(3)+random(4);

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);

    set_short("pair of " + ADJ1 + " " + ADJ2 + " " + ARMOUR); 
	set_pshort("pairs of " + ADJ1 + " " + ADJ2 + " " + ARMOUR);
	
	set_long("These are long, " + ADJ1 + " leather gloves, protecting your hands up to your elbows. " +
    	"The part covering your arm is reinforced with small strips of steel, while your hands " +
    	"are only covered with hardened leather to provide as much freedom as possible.\n");
   
    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
	tmp = F_VALUE_ARMOUR(ac)/2;
    // guaranteed - the price will never be lower than 3/4 of F_VALUE_ARMOUR(ac)
    // but might be up to 2 times higher, with semi-gaussian distribution 
    // around F_VALUE_ARMOUR  
    add_prop(OBJ_I_VALUE, min(tmp*3/2, random(tmp) + random(tmp) + random(tmp) + random(tmp)));
   
    	

}
