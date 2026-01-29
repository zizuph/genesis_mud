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

#define AC_MOD      0,1,-1

/*
* 20+/-5
*/

int AC = 15+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("leggings");
    set_adj("reinforced");
    set_adj("Phlanish");
    set_short("reinforced Phlanish leggings");    
	
	set_long("This is a pair of reinforced leather leggings. They have overlapping" 
        +" scales of light steel on the thighs, giving a slight advantage against"
        +" a sword or an axe, but leaving the joints less protected especially"
        +" when it comes to crushing attacks.\n");
   
set_at(A_LEGS);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}

