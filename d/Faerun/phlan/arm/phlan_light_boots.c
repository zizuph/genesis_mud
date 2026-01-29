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
*                   P S B  Good for walking through brush
*/

#define AC_MOD      1,0,-1

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
    add_name("boots");
    set_adj("supple");
    set_adj("leather");
    set_short("supple leather boots");    
	
	set_long("These are knee high supple leather boots with surprising"
        +" resiliency. The specially treated leather uppers are dyed dark"
        +" green in color while the thick soles, perfect for walking"
        +" through through thorns and underbrush, are of a rigid boiled"
        +" ox hide.\n");
   
set_at(A_FEET);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_FEET));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
