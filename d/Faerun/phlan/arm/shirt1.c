/*
 * Armour for Aldo the barfly
 *
 * modified by Tharizdun 2021
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

int AC = 2+random(2);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("shirt");
    set_adj("gaudy");
    set_adj("flowered");
    set_short("gaudy flowered shirt");    
	
    set_long("It is a cotton shirt with a gaudy tropical flower print.\n");
   
set_at(A_BODY);
    set_ac(AC);   
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
