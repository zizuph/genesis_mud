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

#define AC_MOD      0,0,0

/*
 *   4 +/- 1
 */
 
int AC =  3 + random(2);


void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("dress");
    set_adj("low-cut");
    set_adj("clingy");
    set_short("low-cut clingy dress");    
    set_long("A low-cut clingy dress with some inconspicuous padding"
        +" in the bust and a constricting stitch at the waist.\n");
   
set_at(A_TORSO | A_LEGS | A_ARMS);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}