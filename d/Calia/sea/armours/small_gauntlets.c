/*    
        Black gauntlets for the water krougs

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
    set_name("gauntlets");
    set_pname("gauntlets");
    set_adj("black");
    set_short("pair of black gauntlets");
    set_pshort("pairs of black gauntlets");
    set_long("A pair of black gauntlets.\n");
    set_ac(11);
    set_at(A_HANDS);
    set_am( ({ 2, 0, -2 }) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    seteuid(getuid());
}

