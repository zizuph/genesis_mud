/*
 * Armour for halfling guards
 * -- Finwe, December 2015
 *
 * modified by Tharizdun 2021 to be Brandi's dress.
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

/*
*                   P S B  additional padding vs. blunt
*/

#define AC_MOD      -1,0,1

/*
 *   7 +/- 2
 */
 
int AC =  5 + random(4);


void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("kilt");
    set_adj("stained");
    set_adj("amber");
    set_short("stained amber kilt");    
    set_long("A tunic with a flared bottom resembling a kilt. An integrated"
        +" belt cinches it tight at the waist. It is made of a coarse wool"
        +" and poorly dyed an amber-orange color.\n");
   
set_at(A_TORSO | A_LEGS | A_ARMS | A_NECK);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_TORSO | A_LEGS | A_ARMS | A_NECK));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}