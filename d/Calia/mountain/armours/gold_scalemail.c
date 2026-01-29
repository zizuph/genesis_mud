
/* 
    scale mail for tough krougs

    coder(s):   Maniac

    history: 
        20/2/96              Modified                     Maniac
         9/8/95               Created                     Maniac  

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "armour.h"

void
create_armour()
{
    set_name("mail");
    set_adj(({"polished", "gold", "scale"}));
    set_short("suit of polished gold scale mail");
    set_pshort("suits of polished gold scale mail");
    set_long("A suit of polished gold scale mail, worn by higher " +
             "ranking kroug warriors. It covers the torso " +
             "and arms.\n");
    set_ac(25);
    set_at(A_BODY | A_ARMS);
    set_am(({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VOLUME, 4500);
}

