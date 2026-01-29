inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object  door;

void
create_room()
{
    set_short("a house in a village in Emyn Arnen");
    set_long(BSN("Long ago this house must have belonged to a farmer " +
        "or a merchant living in this hamlet. Now it has " +
        "been deserted and fallen into disrepair. The roof has collapsed " +
        "on the upper floor, and the windows and the door are just " +
        "gaping holes in the front of the house."));
    add_item(({"ceiling", "roof"}), BSN(
        "The ceiling of this room seems still to hold, but through " +
        "the hole which once was used by the stairs, one can see " +
        "that the roof of the house has crashed down onto the floor " +
        "above."));
    add_item(({"ground", "floor"}), BSN(
        "The floor is covered by rubble and dirt. The wooden planks " +
        "which once covered the ground have rotten away in places so " +
        "that the earth below is uncovered. In the northwest corner "
      + "a wooden board is lying on the ground."));
    add_item(({"corner", "northwest corner", "wooden board", "board"}), BSN(
        "In the northwest corner of the room, there is a wooden "
      + "board lying on the ground. It looks different from the wooden "
      + "planks that once were the floor of the room."));
    add_item(({"rubble", "dirt", "earth"}), BSN(
        "Just rubble and dirt. It stinks, and there is certainly " +
        "nothing valuable among it."));
    add_item(({"window", "windows", "door"}), BSN(
        "All that remains of the windows and the door leading south " +
        "onto the street are empty holes in the wall."));

    add_exit(ITH_DIR + "emyn-arnen/mp1",     "south", 0, 1);

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(OBJ_I_SEARCH_TIME, 1);
    door = clone_object(ITH_DIR + "emyn-arnen/obj/h2up_door");
    door->set_no_show_obvious(1);
    door->move(TO);
}

string
do_search(object pl, string str)
{
    if (!strlen(str) || (str != "corner" && str != "board" &&
        str != "northwest corner" && str != "wooden board"))
        return 0;

    if (!door)
        return 0;
    if (door->query_open())
        return 0;
    if (door->query_closed_desc() != "")
        return 0;
    door->set_closed_desc("There is a closed trap door leading down.\n");
    change_my_desc(door->query_closed_desc(), door);
    say(QCTNAME(TP) + " searches the northwest corner and finds a "
      + "trap door leading down.\n");
    return BSN("When you examine the wooden board in the northwest "
      + "corner, you notice that it is a trap door leading into a "
      + "cellar under the house.");
}

void
reset_room()
{
    door->reset_door();
}
