/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

#define LIVE_I_CAN_FISH  "_live_i_can_fish"

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("There is moor all around you with an occasional tree "
         +   "making its living. To the east of you is a larger pond, "
         +   "and there are traces of digging here. Luckily, a few dams "
         +   "are still standing and it is possible to walk on them, "
         +   "since the holes have also filled with water.",SL));

    add_exit(ROOM + "moor5","north",0,3);
    add_exit(ROOM + "moor4","west",0,3);
    add_exit(ROOM + "moor1","southwest",0,3);
    add_exit(ROOM + "moor7","south",0,3);

    // Small bait fish can be caught here.
    add_prop(LIVE_I_CAN_FISH, "default");

    add_item("pond","It's a pond filled with black water. " +
        "It blocks your path to the east.\n");
    add_item("holes","The holes definitely are not natural. " +
        "As well as the pond, they are filled with water.\n");
    add_item("water",
        "This water is black and does not look inviting at all.\n");
    add_item(({"dam","dams"}), "The dams still remain from the " +
        "digging that created all the holes.\n");
}


