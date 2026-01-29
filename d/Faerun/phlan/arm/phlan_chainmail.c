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
* 30+/-5
*/

int AC = 25+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("chainmail");
    set_adj("sturdy");
    set_adj("Phlanish");
    set_short("sturdy Phlanish chainmail");    
	
	set_long("This is a sturdy chainmail shirt, protecting your torso, chest" 
        +" and back. The steel links are riveted, making them stronger against piercing"
        +" or slashing weapons but with less give, attacks from blunt weapons"
        +" would be more damaging. Facing humanoids armed with axes and spears,"
        +" this is just how adventurers in Phlan prefer it.\n");
   
set_at(A_BODY);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
