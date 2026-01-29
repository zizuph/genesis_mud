/* created by Aridor 04/19/94 */

#include "../local.h"
#include <stdproperties.h>

inherit MININGROOM;

object stone;

void
create_mining_room()
{
    set_my_long("A cavern that leads east. The walls don't look normal " +
        "here, holes and cuts and traces of labor are visible " +
        "everywhere. ");

    add_exit(THEIWAR + "r33","east");

    what1 = "gold";
    set_alarm(20.0,0.0,"reset_room");
}


void
reset_room()
{
    num1 = random(5);

    if (present(stone) || random(2))
      return;
    seteuid(getuid(TO));
    stone = clone_object(OBJ + "sh_stone");
    stone->add_prop(OBJ_I_HIDE, 10 + random(40));
    stone->move(TO);
}
