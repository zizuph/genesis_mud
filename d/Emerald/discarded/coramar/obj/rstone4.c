/*
 * RSTONE4 - Fourth Rune Stone
 */

#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASERUNESTONE;

void
create_runestone()
{
    add_name("_coramar_rune_4");
    set_rune_desc("The rune is an expert carving of two joined "+
    "circles. One is larger than the other, and the small one is "+
      "pressed and seems almost oval in shape.");

    add_prop(CIRDAAN_RUNE_NUMBER, 4);
}
