/*
 *   Armour from Phlan guards
 *   Tharizdun, 2021
 */
 
#include "/d/Faerun/defs.h"
#include "/d/Faerun/phlan/arm/defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

/*
 *   30 +/- 5
 */

int AC = 25 + random(10);

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("shield");
    set_adj("heavy");
    set_adj("steel");
    set_short("heavy steel shield");    
        set_long("This heavy shield has a copper reinforced wooden"
        +" frame stretched over with ox hide, then plated with bands of"
        +" tempered steel. It would be equally effective against any"
        +" type of weapon.\n");
   
    set_at(A_SHIELD);
    set_ac(AC);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}
