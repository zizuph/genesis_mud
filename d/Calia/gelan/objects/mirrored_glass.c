
/*
 *   object:      a sheet of mirrored glass for the staff quest
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
   add_name("glass");
   add_name("mirror");
   add_name("_sheet_of_mirrored_glass_"); 
   set_adj(({"glass","mirrored"}));
   set_short("sheet of mirrored glass");
   set_pshort("sheets of mirrored glass");
   set_long("This is a sheet of mirrored glass. If you could find someone "+
        "to do so, you might be able to get this set into a frame, turning "+
        "it into a mirror.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_WEIGHT, 10);
}

