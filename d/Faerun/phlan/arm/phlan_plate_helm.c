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
*                   P S B  balanced defense
*/

#define AC_MOD      0,0,0

/*
* 25+/-5
*/

int AC = 20+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("helm");
    set_adj("Phlanish");
    set_adj("plate");
    set_short("Phlanish plate helm");    
	
	set_long("This is a steel plate helm, protecting your head and" 
        +" neck. The steel plates are riveted to a padded leather backing"
        +" giving it good protection against all forms of attack. It is held"
        +" in place by straps connecting it to a breastplate or hauberk.\n");
   
set_at(A_HEAD || A_NECK);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_HEAD || A_NECK));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
