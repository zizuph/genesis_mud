// file name: ~Avenir/common/dark/l3/center.c
// creator(s):
// revision history:
//   - removed exit to ec1.c
//       -=Denis
//  - inherits /d/Avenir/inherit/room for use with smis
// note:
// bug(s):
// to-do: something.

inherit "/d/Avenir/inherit/room";
#include "/d/Avenir/common/dark/dark.h"
void
create_domain_room()
{
    set_short("A crossing of tunnels");
    set_long(
"You are at a crossing of many tunnels, all joining together at odd "
+"angles. A terrible stench is coming from the cavern to the "
+"southwest. From the northwest tunnel blows an icy wind, mixing "
+"with an intense heat that radiates from northern passage to "
+"make a warm breeze. The tunnel to the south slopes gently "
+"upwards into darkness and seems to continue on to the northeast.\n");

    AI(({"wall","walls","tunnel","tunnels","passage","passages"}),
"The tunnels that come together here are all of different types. The "
+"passages to the south and north are lined with white stone walls "
+"with flowing blue patterns in them. The passage to the northeast is "
+"of roughly hewn stone, and the one to the northwest is carved from the "
+"natural stone, but it is flawlessly smooth.\n");

        AI(({"dark","darkness"}),"The darkness seems to have a life "
+"of its own, stretching itself out in an attempt to engulf you "
+"within.\n");

        AI(("floor"),"The floor is smooth, and is carved out of the "
+"living rock itself, unlike the walls. The floor is clean and "
+"flat here.\n");

        AI(({"cave","cavern"}),"The smooth rock wall that runs south "
+"and northwest seems to have been broken through, to reveal a small "
+"cavern behind it. From here, you can make out nothing in the gloom, "
+"but a horrid smell, like something long dead, comes from the cave.\n");

    add_exit("/d/Avenir/common/dark/l3/s1","south",0);
    add_exit("/d/Avenir/common/dark/l3/n6","north",0);
    add_exit("/d/Avenir/common/dark/l3/n1","northwest",0);
    add_exit("/d/Avenir/common/dark/l3/e1","northeast",0);
    add_exit("/d/Avenir/common/dark/l3/wc1","southwest",0);
// nc1 is a mapping flaw, it should probably move here.
//    add_exit("/d/Avenir/common/dark/l3/nc1","southeast",0);

    BLACK
    IN
}

