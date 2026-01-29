
/*
 *   object:      a block of silver bullion for the staff quest
 *   coder(s):    September 5th, 2003, Jaacar
 *    
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
   set_name("cylinder");
   add_name("silver");
   add_name("bullion");
   add_name("_cylinder_of_silver_bullion_"); 
   set_adj("silver");
   set_short("cylinder of silver bullion");
   set_pshort("cylinders of silver bullion");
   set_long("This is a cylinder shaped piece of silver bullion. If you "+
        "could find someone to do so, you might be able to get it pressed "+
        "into a sheet of silver.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_WEIGHT, 10);
}

