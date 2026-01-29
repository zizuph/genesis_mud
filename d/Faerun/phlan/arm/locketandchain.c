/*
 * Brandi's locket
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

/*
*                   P S B  common leather properties
*/

#define AC_MOD      0,0,0

/*
 *   2 +/- 1
 */
 
int AC = 1 + random(2);


void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("locket");
    set_adj("silver");
    set_adj("chained");
    set_short("silver-chained locket");    
    set_long("A braided silver chain with a locket. Engraved on"
       +" the back of the locket is the name Lou Kinglass.\n");
   
set_at(A_NECK);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_NECK));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
