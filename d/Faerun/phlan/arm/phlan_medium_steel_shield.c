/*
 *   Armour from Phlan guards
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
*                   P S B  setting up for orc fighting
*/

#define AC_MOD      1,0,-1

/*
*   25+/-5
*/

int AC = 20+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("shield");
    set_adj("medium");
    set_adj("steel");
    set_short("medium steel shield");    
	
	set_long("This medium shield has a wooden frame of thick oak with"
        +" a plating of steel strips. A layer of cushioning leather between"
        +" the steel strips and wood allow it to be a little more effective"
        +" against blunt weapons than a lighter version would be.\n");
   
set_at(A_BODY);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}