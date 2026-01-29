/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

void
create_moor_room()
{

    set_short("Road west of Palanthas");
    set_long(BS("You stand on a fairly well paved road leading "
        +    "southwest towards the hills and east to the gate into "
        +    "Palanthas. Trees line the road and cast comforting "
        +    "shade across the pavement.",SL));

    add_item("road", "The road is fairly well paved, suggesting that it " +
             "sees a fair bit of use.\n");

    add_item("gate", "The gate into Palanthas looks somewhat sturdy, yet " +
             "it seems that they have built it merely as a formality.\n");

    add_item(({"tree", "trees"}), "The trees of the area appear to be " +
             "fairly well-tended. These line the road, and are obviously " +
             "planted by human hands.\n");

    add_exit(PALAN,"east",0,1);
    add_exit(ROOM + "road2","northwest",0,3);

}

