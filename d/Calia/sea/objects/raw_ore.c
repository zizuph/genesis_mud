
/*
 *   object:      raw silver ore from the hermit
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
   set_name("ore");
   add_name("silver ore");
   add_name("_raw_silver_ore_"); 
   set_adj("silver");
   set_short("silver ore");
   set_long("It is a large chunk of raw silver ore. If you could "+
        "find someone to refine this, it might make some good "+
        "silver bullion.\n");

   add_prop(OBJ_I_VOLUME, 20);
   add_prop(OBJ_I_VALUE, 20);
   add_prop(OBJ_I_WEIGHT, 20);
}

