/*
 *  Basic leather gloves
 *  Tharizdun, 2021
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE; 	
 
int AC =  5;

void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("gloves");
    set_adj("tanned");
    set_adj("leather");
    set_short("tanned leather gloves");    
    set_long("These are soft doeskin gloves. They may protect the hands"
        +" slightly in combat, but more importantly they avoid accidental contact"
        +" with dangerous herbs or other irritants.\n");
   
set_at(A_HANDS);
    set_ac(AC);    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_HANDS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}