/* 
 * Room base 
 *
 */

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit TRIAL_OUT;

void
create_trial_room()
{
    add_item(({"stone", "path", "rock", "road"}), "The road "+
      "is very orderly, nearly unblemished. The lane is "+
      "covered in stone, so that it almost looks like the "+
      "structures around it is melted into the road.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}
