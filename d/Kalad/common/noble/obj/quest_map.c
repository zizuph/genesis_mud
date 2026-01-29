/*     Created by:      ???
 *     Location:        
 *     Modified:        Toby, 970919 (fixed a typo)
 */

inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("map");
    set_adj("wrinkled");
    add_adj("dusty");
    set_short("wrinkled dusty map");
    set_long("This is an old looking map. It shows a maze that looks "+
    "like its part of the underground of Kabal.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,6);
}

