 /*****************************************************************************
*  /d/Calia/argos/nwterr/armours/satshield.c
*
*  Description: Satyr Shield
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
    set_name("shield");
    set_adj(({"light","wooden","round","small"}));
    set_short("light wooden shield");
    set_long("It is a small round shield made of wood, decorated with "+
       (ENGS[(random(sizeof(ENGS)))])+"\n");
    set_ac(10);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
}