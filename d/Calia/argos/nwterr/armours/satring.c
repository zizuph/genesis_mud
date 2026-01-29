 /*****************************************************************************
*  /d/Calia/argos/nwterr/armours/satring.c
*
*  Description: Satyr Ring
*
*  Created Sept 2021, Greneth
*
*  Changes:      
*
 *****************************************************************************/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define ENGS ({"leaves","flutes","hearts","vines","trees","mystic symbols"})
void create_armour() {
    set_name("ring");
    set_adj("wooden");
    set_short("wooden ring");
    set_long(
       "It is a simple wooden ring, engraved with tiny "+
       (ENGS[(random(sizeof(ENGS)))])+"\n");
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  50);
}