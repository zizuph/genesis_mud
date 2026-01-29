
/*  
    hardened leather armour for lesser krougs

    coder(s):   Maniac

    history: 
        30/2/96         Modified                          Maniac
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
    set_name("armour");
    set_adj(({"hardened", "leather"}));
    set_short("suit of hardened leather armour");
    set_pshort("suits of hardened leather armour");
    set_long("A suit of hardened leather armour, of the type worn by " +
             "lesser kroug warriors. It is studded, and covers the torso " +
             "and arms.\n");
    set_ac(14);
    set_at(A_BODY | A_ARMS);
    set_am(({0, 0, 0 }));
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 2300);
}

