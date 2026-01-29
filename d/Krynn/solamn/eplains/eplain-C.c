#include "local.h"
inherit TDIR+"eplain_base";

string
current_army()
{
    string area = TO->query_area_name();
    if (!area)
	return "Free People";
    return ARMYMASTER->army_in_area(area);
}

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("In a military camp");
    set_long("This seems to be a military campsite. You can see a " +
        "fireplace, and around it a cleared area. Currently, the " +
        "area is occupied by the @@current_army@@.\n");
    add_item(({"fire", "fireplace", "ashes", "pile"}),
        "The fireplace is nothing more than a pile of ashes.\n");
    add_item(({"plains", "plains of solamnia"}), "Spreading out before " +
        "you as far as the eye can see are the Eastern Plains of " +
        "Solamnia.\n");

    add_std_exits();

    set_num_npc(5);
    set_npc_chance(1);
    reset();
}
