/*
 *  Chainmail gloves
 *  Tharizdun, 2021
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

/*
*                   P S B  primarily used for duelling sword on sword
*/

#define AC_MOD      0,2,-2

/*
* 12+/-5
*/

int AC = 7+random(10);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("gloves");
    set_adj("light");
    set_adj("chainmail");
    set_short("light chainmail gloves");    
        set_long("These light chainmail gloves are made of fine steel links."
        +" They are designed to protect the hands from slashing damage in combat.\n");
   
    set_at(A_HANDS);
    set_ac(AC);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_HANDS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}