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
    add_name("coif");
    set_adj("Phlanish");
    set_adj("chainmail");
    set_short("Phlanish chainmail coif");    
	
	set_long("This is a Phlanish chainmail coif, protecting your head and" 
        +" neck. The steel links are riveted, making them stronger against piercing"
        +" or slashing weapons but with less give, attacks from blunt weapons"
        +" would be more damaging. It is designed with combat against the"
        +" local humanoids in mind.\n");
   
set_at(A_HEAD || A_NECK);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_HEAD || A_NECK));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}