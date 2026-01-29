/* Sand, by Teth, April 9, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("grain of sand");
    set_pname("grains of sand");
    add_name("sand");
    add_pname("sands");
    set_adj("fine");
    set_short("fine grain of sand");
    set_pshort("fine grains of sand");
    set_long("This fine grain of sand is the product of many years of "+
             "erosion of a rock or stone. It is tan-brown in colour, yet "+
             "seems to have a black spot on one side.\n");
   
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_I_WEIGHT, 1);
}


