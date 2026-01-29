
/*
 *   object:      a fancy mirror for the create staff quest
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
   set_name("mirror");
   add_name("fancy mirror");
   add_name("_fancy_mirror_"); 
   set_adj("fancy");
   set_short("fancy mirror");
   set_long("This is one of the most fancy mirrors you have ever seen in "+
        "your life. Its frame is constructed entirely of crushed seashells "+
        "and sand. The mirrored glass is flawlessly forged and backed with "+
        "the finest silver.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 5000);
   add_prop(OBJ_I_WEIGHT, 10);
}

