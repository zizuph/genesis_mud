/* Eggshell, by Teth, April 9, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("eggshell");
    set_short("speckled eggshell");
    set_pshort("speckled eggshells");
    set_adj("speckled");
    set_long("Speckled and fragile, this eggshell appears to be fairly old, "+
      "yet still brightly coloured. It is a mottled brown on white, "+
      "perhaps the eggshell of a thrush.\n");

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VALUE, 5);
}



