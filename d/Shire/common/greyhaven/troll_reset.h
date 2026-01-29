/* Any room including this file will need to call reset_room() from
 * create_room().  If reset_room() is already in the room this is added
 * to, include the statement ::reset_room(); in that function.
 */

#include "defs.h"

object troll;

reset_room()
{
    if (random(100) < 4)
        create_troll();
}


create_troll()
{
    object troll;

    if (!find_object("/d/Shire/common/monster/troll"))
    {
        troll = clone_object(STAND_MONSTER + "troll");
        troll->move(this_object());
    }
}
