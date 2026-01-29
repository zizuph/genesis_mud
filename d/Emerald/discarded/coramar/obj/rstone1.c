/*
 * RSTONE1 - First Rune Stone
 */

#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASERUNESTONE;

void
create_runestone()
{
    add_name("_coramar_rune_1");
    
    set_rune_desc("The deeply grooved image engraved on the flat "+
                "side of the stone has a curved top, and both sides "+
                "taper down to a point. The image vaguely resembles a "+
                "plain shield often used by elven knights.");

    add_prop(CIRDAAN_RUNE_NUMBER, 1);

    hide_me();
}
