/* torque.c originally done by Phase, redone by Mayhem.
 * This is the quest item for the Crystal Tower quest
 *
 * Completely redone by Shiva, December 2000
 */

#pragma save_binary
#pragma strict_types

#include "torque.h"

inherit TORQUE_BASE;

public void
create_torque()
{
    set_name("torque");
    set_adj(({ "one-eyed", "one-horned" }));
    set_short("one-eyed one-horned torque");
}

public int
query_torque_active(object requesting_torque)
{
    return 1;
}
