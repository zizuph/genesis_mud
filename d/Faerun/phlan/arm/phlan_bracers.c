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
    add_name("bracers");
    set_adj("sturdy");
    set_adj("Phlanish");
    set_short("sturdy Phlanish bracers");    
	
	set_long("This is a sturdy pair of chainmail bracers, protecting both" 
        +" arms. The steel links are riveted, making them stronger against piercing"
        +" or slashing weapons but with less give, attacks from blunt weapons"
        +" would be more damaging. These would serve well facing the local orcs.\n");
   
set_at(A_ARMS);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_ARMS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}