
/*
 *   object:      seashell frame from the mermaid
 *   coder(s):    September 5th, 2003 - Jaacar
 *    
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void
create_object()
{
   set_name("frame");
   add_name("seashell frame");
   add_name("_seashell_frame_"); 
   set_adj("seashell");
   set_short("seashell frame");
   set_long("It is a beautiful seashell frame. If you could find someone "+
        "to put some mirrored glass in this frame, you would have a very "+
        "beautiful mirror.\n");

   add_prop(OBJ_I_VOLUME, 5);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 5);
}

