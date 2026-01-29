/* West street 1, VK
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

object leader, member1, member2, member3;

void
reset_vin_room()
{
    if (!leader)
    {
    leader = clone_object(VNPC + "street_patrol_leader");
    leader->move(TO);
    leader->start_patrol();
    }
    if (!member1)
    {
    member1 = clone_object(VNPC + "street_patrol_member");
    member1->move(TO);
    }
    if (!member2)
    {
    member2 = clone_object(VNPC + "street_patrol_member");
    member2->move(TO);
    }
    if (!member3)
    {
    member3 = clone_object(VNPC + "street_patrol_member");
    member3->move(TO);
    }
}

public void
create_street()
{
    add_my_desc("A garden can be seen to the northwest, and a " +
      "training area lies to the north. The street goes only " +
      "south from here.\n");
    AI("garden","It is a small area used by the cooks and " +
      "innkeepers. Its location captures the light of the " +
      "sun.\n");

    AE(VROOM + "garden", "northwest", 0);
    AE(VROOM + "adv_guild","north",0);
    AE(VROOM + "ws2", "south", 0);
    reset_vin_room();
    add_prop(ROOM_I_NO_CLEANUP, 1);
}
