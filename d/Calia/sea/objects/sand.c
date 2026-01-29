
/*
 *   object:      a handful of sand for the create staff quest
 *   coder(s):    September 5th, 2003, Jaacar
 *    
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void
create_object()
{
   set_name("sand");
   add_name("_handful_of_sand_"); 
   set_adj("light brown");
   set_short("handful of light brown sand");
   set_pshort("handfuls of light brown sand");
   set_long("This is a handful of light brown sand. This might be "+
        "made into glass if you could find someone to do so.\n");

   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 1);
}

