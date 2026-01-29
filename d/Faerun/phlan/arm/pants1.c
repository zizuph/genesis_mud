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

#define AC_MOD      0,0,0

/*
 *   3 +/- 1
 */
 
int AC =  2 + random(2);

/*
*   description
*/

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("pants");
    set_adj("khaki");
    set_adj("linen");
    set_short("khaki linen pants");    
    set_long("It is a pair of linen khaki pants with large pockets.\n");
   
set_at(A_LEGS);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}