/* Blue Jay Feather, by Teth, April 9, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("feather");
    set_short("black-spotted blue feather");
    set_pshort("black-spotted blue feathers");
    set_adj(({"black-spotted","blue"}));
    set_long("This feather is blue and white, with several black spots "+
             "dotting its surface. It is probably the feather of a blue "+
             "jay, a bird that eats most everything, including hazelnuts. "+
             "The quill of the feather is long, straight and stiff, "+
             "necessary for flight.\n");

   add_prop(OBJ_I_VOLUME, 2);
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VALUE, 5);
}

