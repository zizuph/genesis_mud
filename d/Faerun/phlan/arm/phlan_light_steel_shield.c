/*
 *   Armour from Phlan armour shop
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

#define AC_MOD      1,2,-3

/*
*   20+/-5
*/

int AC = 15+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("shield");
    set_adj("light");
    set_adj("shield");
    set_short("light steel shield");    
	
	set_long("This light shield has a wooden frame with a."
        +" plating of thin steel strips. It appears to be specifically"
        +" made for turning a blade or deflecting a point, but would not"
        +" work as well against a crushing attack.\n");
   
set_at(A_SHIELD);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
