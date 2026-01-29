/* A chisel for use in the polymorph quest to get a chipping of stone from
   an obelisk. Sold in the hardware store in the palace.

   Coded by Maniac 31/8/95

*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "obj.h"
#include POLYMORPH_QUEST


void
create_object()
{
    set_name("chisel");
    set_long("An ordinary chisel. Nothing special about it.\n"); 
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 50); 
}

