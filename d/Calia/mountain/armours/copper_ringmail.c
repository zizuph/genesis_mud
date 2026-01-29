
/*  
    ringmail armour for regular krougs

    coder(s):   Maniac

    history: 
         7/8/95               Created                     Maniac  

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "armour.h"

void
create_armour()
{
    set_name("ringmail");
    set_adj(({"copper", "polished"}));
    set_short("suit of polished copper ringmail");
    set_pshort("suits of polished copper ringmail");
    set_long("A suit of polished copper ringmail, of the type worn " +
             "by regular kroug warriors. It covers the torso " +
             "and arms.\n");
    set_ac(20);
    set_at(A_BODY | A_ARMS);
    set_am(({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 3000);
}

