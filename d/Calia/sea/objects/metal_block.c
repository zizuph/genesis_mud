
/*
 *   object:      a block of metal for the staff quest
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
   set_name("block");
   add_name("silver");
   add_name("_block_of_silver_"); 
   set_adj("silver");
   set_short("block of silver");
   set_pshort("blocks of silver");
   set_long("This is a block of refined silver. If you could find someone "+
        "to do so, you might be able to get this pressed into a sheet of "+
        "silver.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_WEIGHT, 10);
}

