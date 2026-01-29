
/*    
   Black scale mail for small water krougs

   Coded by Digit & Maniac
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name("scalemail");
    add_name("mail"); 
    set_adj("black");
    set_short("black scalemail");
    set_long("This suit of black scalemail is actually the skin " +
             "of a small water kroug.\n");
    set_ac(14);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
}

