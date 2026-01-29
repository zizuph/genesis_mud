/* 
 * scavanger hunt item
 */
  
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("crystal");
    add_name("_shire_crystal_");
    add_name("exquisite cut crystal");
    set_adj("exquisitely cut");
    set_long("This is an exquistely cut crystal. It is tear drop " +
        "shaped and sparkles in the light. A white flame burns " +
        "bright in its center.\n");
    add_prop(OBJ_I_VALUE, 150);

    add_item(({"white flame", "flame"}),
        "The white flame burns brightly. It looks to be ethereal " +
        "as it never goes out and yet the gem is cool to the touch.\n");
}
