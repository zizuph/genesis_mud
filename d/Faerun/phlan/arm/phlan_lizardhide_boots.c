/*
 *   Armour for Phlan quest NPC
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
*                   P S B  Overall sound protection
*/

#define AC_MOD      0,0,0

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
    add_name("boots");
    set_adj("high");
    set_adj("lizard-hide");
    set_short("high lizard-hide boots");    
	
	set_long("These are high boots coming almost to mid-thigh and made"
        +" of a greenish hued lizard skin with small overlapping irridescent"
        +" scales. The scales give a level of rigid protection to the"
        +" otherwise supple hide. The soles are of thick black leather.\n");
   
set_at(A_FEET | A_LEGS);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_FEET | A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
