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

#define ADJ1        "gray"
#define ADJ2        "steel"
#define ARMOUR      "fullplate"
#define BOD_TYPE    A_TORSO|A_ARMS|A_LEGS
#define AC_MOD      -1,3,1

int ac =  40;

void 
create_faerun_armour()
{
	int tmp;
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This suite of armour is made of large plates of steel, " +
    	"supported by chains and padding. The interlocking sheets of steel were " +
    	"skillfully crafted to form blow-deflecting bends and curves. " +
    	"While this fullplate lacks any adornment it still seems to offer " +
    	"formidable protection.\n");
 
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
