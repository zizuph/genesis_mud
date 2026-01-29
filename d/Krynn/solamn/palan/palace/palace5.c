/* created by Aridor 09/14/93 */

#include <macros.h>
#include "../local.h"

inherit ROOM_BASE


query_to_jail()
{
  return "down";
}

void
create_palan_room()
{
    set_short("On the Marble Stairs");
    set_long(BS("You have reached the middle of the Marble Stairs. "
         +   "Looking up you can see a brilliant green light blocking "
         +   "your further ascent. You can also see into the "
         +   "entrance hall of the palace, but it is quite far down.", SL));

    add_exit(PALACE + "palace1","down",0,0);
    add_exit("/d/Krynn/aridor/workroom","up","@@is_protected",0);
}



is_protected()
{
    if (TP->query_wiz_level())
    {
        write("You step through the green light.\n");
        say(QCTNAME(TP) + " effortlessly steps through the green light.\n");
        return 0;
    }
    write(BS("As you climb the stairs you feel a magical barrier hindering "
        + "you from ascending further. You have the feeling that this is "
        + "very strong magic working here, and only the great wizards "
        + "have the power to pass through.", SL));
    return 1;
}

 
