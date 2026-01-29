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
 
void
create_armour()
{
    set_name(({"brown loincloth","loincloth"}));
    set_adj("brown");
    set_short("brown loincloth");
    set_long("A well worn loincloth that barely covers what it needs to.\n");
    set_ac(1);
    set_at(A_LEGS);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}