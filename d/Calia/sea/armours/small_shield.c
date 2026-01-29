/*     
       Black shield for small water krougs

       Coded by Digit and Maniac
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name("shield");
    set_adj("black");
    set_short("black shield"); 
    set_pshort("black shields"); 
    set_long("A black shield.\n"); 
    set_ac(11);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VOLUME, 2400);
}

