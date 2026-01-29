
/* 
    Gleaming steel chainmail worn by elite krougs.

    coder(s):  Maniac

    history:
             20/2/96       Modified           Maniac
              9/8/95       Created            Maniac
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "armour.h"

void
create_armour()
{
    set_name("chainmail");
    set_adj(({"gleaming", "steel"}));
    set_short("suit of gleaming steel chainmail");
    set_pshort("suits of gleaming steel chainmail");
    set_long("A suit of gleaming steel chainmail, the type that is worn " +
             "by elite kroug warriors. It covers the torso and arms.\n");
    set_ac(35);
    set_at(A_BODY | A_ARMS);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 12750);
    add_prop(OBJ_I_VOLUME, 7500);
}

