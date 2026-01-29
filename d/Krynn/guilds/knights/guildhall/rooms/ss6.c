/* Street South 6 in VK
 * by Teth
 * Dec. 4, 96
 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>

inherit STREET;

public void
create_street()
{
    object door;
    add_my_desc("There is a rounded tower to the southeast. " +
        "The street continues north and west.\n");
    AI(({"rounded tower","tower"}),"It serves the dual purpose " +
        "of being a post for guards, as well as a method to reach " +
        "the battlements.\n");
    AI(({"door","iron door","tower door"}), "@@door");
    
    door = clone_object(VOBJ + "sedoora");
    door->move(TO);
    door->set_key(KEEPKEY);

    AE(VROOM + "ss5", "west", 0);
    AE(VROOM + "es5", "north", 0);
    
}

string
door()
{
    write("The door is made of iron and looks very solid.\n");
    return "";
}
