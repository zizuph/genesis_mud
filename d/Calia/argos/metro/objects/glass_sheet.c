
/*
 *   object:      a sheet of glass for the create staff quest
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
   set_name("glass");
   add_name("sheet");
   add_name("_sheet_of_glass_"); 
   set_adj("sheet");
   set_short("sheet of glass");
   set_pshort("sheets of glass");
   set_long("It is a sheet of glass. If you could find someone to do so, "+
        "you might be able to put some metal on the back to make it into "+
        "some mirrored glass.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 10);
   add_prop(OBJ_I_WEIGHT, 10);
}

