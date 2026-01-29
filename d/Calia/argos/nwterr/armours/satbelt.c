 /*****************************************************************************
*  /d/Calia/argos/nwterr/armours/satbelt.c
*
*  Description: Satyr Belt
*
*  Created Sept 2021, Greneth
*
*  Changes:      
*
 *****************************************************************************/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("belt");
    set_adj(({"green","vine"}));
    set_short("green vine belt");
    set_long( "It is a simple belt made out of vines.\n");
    set_ac(5);
    set_at(A_WAIST);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  50);
}