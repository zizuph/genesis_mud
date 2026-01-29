/* Straw by Teth, Jan 9 97 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("blade");
    set_pname("blades");
    add_name(({"blade of straw","straw blade","straw"}));
    add_pname(({"blades of straw","straw blades","straws"}));
    set_adj("golden");
    add_adj("straw");
    set_short("golden straw blade");
    set_pshort("golden straw blades");
    set_long("This golden straw blade is most likely wheat straw, " +
      "or rye straw. It is difficult to tell in its present " +
      "state. A bale of straw would feed a horse nicely.\n");

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
}


