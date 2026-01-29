/* Any room including this file will need to call reset_room() from
 * create_room().  If reset_room() is already in the room this is added
 * to, include the statement ::reset_room(); in that function.
 */

#include "defs.h"

object bandit;

reset_room()
{
    if (random(100) < 1)
        create_bandit();
}


create_bandit()
{
    object bandit;
    if (!find_object("/d/Shire/common/monster/bandit"))
    {
        bandit = clone_object(STAND_MONSTER + "bandit");
        bandit->move(this_object());
    }
}
