#pragma strict_types
// file name:   /d/Avenir/common/ships/sparkle/shirt.c
// creator(s):       Tepsich   Nov 1994
// purpose:          shirt for Staek
// last update:      Boriska, Mar 23 1995
//
// * Lucius May 2009: Cleanup.
//
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_armour(void)
{
    set_name("shirt");
    set_short("white silk shirt");
    add_adj(({"silk", "white"}));
    set_long("A shirt made of high-quality silk. There is an abundance of "+
      "white lace at the neckline and the cuffs of the full sleeves. "+
      "The shirt is loose and flowing, allowing unrestrained movement "+
      "while supplying absolute luxurious comfort.\n");

    set_ac(1); 
    set_at(A_BODY);

    add_prop(OBJ_I_VALUE, 70);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
}
