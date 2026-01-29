/* Soot, by Teth, April 9, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("piece of black soot");
    set_pname("pieces of black soot");
    add_name("soot");
    add_pname("soots");
    set_short("piece of black soot");
    set_pshort("pieces of black soot");
    set_adj("black");
    set_long("This soot is black as night. It is the result of burning "+
      "wood, most likely. It has a slightly greasy feel about it, "+
      "but that is not unusual.\n");

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
}



