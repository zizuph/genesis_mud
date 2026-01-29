/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE

void
create_vin_mount_room()
{

    set_short("In the Vale");
    set_long("You are in a lovely quiet vale. Green grass is growing "
        +    "everywhere you look and a stream flows gently along the road. "
        +    "To the southeast you can see a magnificent tower rising towards "
        +    "the sun. It seems that this fortress, which is topped by the "
        +    "tower, blocks the exit from the vale.\n");

    OUTSIDE;

    add_exit(ROOM + "road14","northwest",0,10);
     add_exit(KSPUR, "southeast", 0,10);

    add_item("vale",
         "It is a lovely vale, no noise can be heard except " +
        "the singing of birds and the occasional rustle of " +
        "some small animal.\n");
    add_item("grass",
         "The grass grows up to your knees and has an intensive " +
        "healthy green color.\n");
    add_item("stream",
         "This small stream is barely visible beneath the grass, " +
        "but you can hear it bubbling and gurgling next to the " +
        "road.\n");
    add_item(({"ground","road"}),
         "The road is covered with grass here, " +
        "making your footing soft.\n");
    add_item(({"tower","fortress"}),
         "The fortress seems to melt perfectly into " +
        "the vale, its tall white tower radiating security. The fortress " +
        "blocks the exit from the vale to the southeast, but you can see " +
        "the road disappearing into the fortress.\n");
    add_item(({"bird","birds","animal","animals"}),
         "You can hear sounds but you cannot see anything.\n");

}


