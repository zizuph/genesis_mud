
/*
 *   object:      a sheet of metal for the staff quest
 *   coder(s):    September 5th, 2003, Jaacar
 *    
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
   set_name("sheet");
   add_name("silver");
   add_name("_sheet_of_silver_"); 
   set_adj("silver");
   set_short("sheet of silver");
   set_pshort("sheets of silver");
   set_long("This is a sheet of refined silver. If you could find someone "+
        "to do so, you might be able to get this put on to a piece of "+
        "glass, turning it into mirrored glass.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_WEIGHT, 10);
}

