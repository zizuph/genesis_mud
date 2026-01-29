/* South Battlement one of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

object banner, flag, leader, member1, member2, member3;

void
reset_vin_room()
{
    if (!leader)
    {
	leader = clone_object(VNPC+"patrol_leader");
	leader->move(TO);
	leader->start_patrol();
    }
    if (!member1)
    {
	member1 = clone_object(VNPC+"patrol_member");
	member1->move(TO);
    }
    if (!member2)
    {
	member2 = clone_object(VNPC+"patrol_member");
	member2->move(TO);
    }
    if (!member3)
    {
	member3 = clone_object(VNPC+"patrol_member");
	member3->move(TO);
    }
}
string
batt_desc()
{
    return "You are above the outer Gate of Vingaard, looking down on the "+
    "the gate itself. The southern battlement stretches out to your east "+
    "and west, with a tower leading down to the lower levels at the end "+
    "of each. Banners stand proud, adorning the battlements. ";
}

public void
create_battlement()
{
    AI(({"gate","outer gate"}),"This is the sturdy gate used to control " +
      "the enterings and leavings of various peoples.\n");
    AI(({"banners","proud banners"}),"The banners decorate the " +
      "battlements. One is the standard of Vingaard Keep, while another " +
      "is the flag of Solamnia.\n");
    AE(VROOM + "sb1", "west", 0);
    AE(VROOM + "sb3", "east", 0);

    banner = clone_object(VOBJ + "vk_banner");
    banner->move(TO);

    flag = clone_object(VOBJ + "sol_flag");
    flag->move(TO);
    add_prop(ROOM_I_NO_CLEANUP, 1);
}
