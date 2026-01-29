/*
 * RSTONE2 - Second Rune Stone
 */

#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASERUNESTONE;

void
create_runestone()
{
    add_name("_coramar_rune_2");
    
    set_rune_desc("The rune is an expertly carved depiction of "+
                  "a triangle. The triangle is grooved deeply in "+
                  "the stone. In the center of the program there is "+
                  "a small, deep circle that looks like it was made "+
                  "with a very unusual chisel.");

    add_prop(CIRDAAN_RUNE_NUMBER, 2);

    hide_me();
}
