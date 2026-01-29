/*
*   Clothing for quest npc
*
*   modified by Tharizdun 2021
*/
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

/*
*                   P S B  common cloth properties
*/

#define AC_MOD      -1,-1,2

/*
 *   15 +/- 5
 */
 
int AC =  10 + random(10);


void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("robe");
    set_adj("sophisticated");
    set_adj("richly-embroidered");
    set_short("sophisticated richly-embroidered robe");    
    set_long("A luxuriantly soft crimson velvet robe with rich gold"
            +" embroidery. The fur trim is black with an almost bluish"
            +" tint that seems to move and change if you look at it."
            +" This may be displacer beast fur. A tag is sewn below"
            +" the collar.\n");
            
    add_item(({"tag"}),
        "It says Cadorna Textiles.\n");     
   
set_at(A_TORSO | A_NECK | A_ARMS);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
   // add_prop(OBJ_I_VALUE, 3456));     

}
