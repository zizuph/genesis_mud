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

#define ADJ1        "dented"
#define ADJ2		"pointy"
#define ARMOUR      "spangenhelm"
#define BOD_TYPE    A_HEAD
#define AC_MOD      2,1,0

// 16 +/- 6
int ac =  10 + random(3) + random(3) + random(3) + random(3);

void 
create_faerun_armour()
{
    int tmp;
    set_name("helm");
    add_name("helmet");
    add_name("spangenhelm");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This is a simple but still efficient helm. It was build on a steel frame, filled " +
    	"with bronze plates. The frame curves with the shape of the head and culminates " +
    	"in a point. There is a strip of metal attached on helmets front to protect your nose.\n"); 
    	
 
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
