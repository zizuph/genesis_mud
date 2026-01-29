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

#define ADJ1        "silvery"
#define ADJ2		"chainmail"
#define ARMOUR      "coif"
#define BOD_TYPE    A_HEAD|A_NECK
#define AC_MOD      -2,2,0

// 26 +/- 6
int ac =  20 + random(3) + random(3) + random(3) + random(3);

void 
create_faerun_armour()
{
    int tmp;
    set_name("helm");
    add_name("helmet");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This coif was created from hundreds of small silver rings. It is not the " +
    	"best choice to protect from bludgeon and it can be easily punctured by an arrow " +
    	"or a pike but it is quite a reasonable safeguard against cutting wounds. " +
    	"The coif covers your head and neck.\n");
 
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
