/*
 *   Armour from Phlan guard leader
 *   Tharizdun, 2021
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;
   
/*
*                   P S B  setting up for guard duty
*/

#define AC_MOD      0,0,0

/*
* 42+/-5
*/

int AC = 37+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("breastplate");
    set_adj("heavy");
    set_adj("steel");
    set_short("heavy steel breastplate");    
	
	set_long("This is a heavy steel breastplate, protecting your torso, chest" 
        +" and back. The tempered steel plates cover the major areas of the upper"
        +" body with underlying chain mesh at the joints. It would be equally"
        +" effective against any kind of weapon. This armour bears the markings"
        +" of an officer in the Phlannish guard.\n");
   
set_at(A_BODY);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
