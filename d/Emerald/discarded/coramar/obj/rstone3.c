/*
 * RSTONE3 - Third Rune Stone
 */

#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASERUNESTONE;

void
create_runestone()
{
    add_name("_coramar_rune_3");
    
    set_rune_desc("The rune is very detailed and must have taken "+
        "an expert in carving to make this image. The image engraved deep "+
        "into the flat side of the stone is of a diamond. Within the "+
        "borders of the diamond, there is a perfect triangle. At the very "+
        "center of the triangle, there is a small, deep circle that looks "+
        "as though it was made with a very unusual chisel.");


    add_prop(CIRDAAN_RUNE_NUMBER, 3);

    hide_me();
}
