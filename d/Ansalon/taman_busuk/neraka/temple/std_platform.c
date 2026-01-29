#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit TEMPLE + "std_base.c";


void
create_temple_room()
{
    set_short("Standard platform");
    set_long("Room with basic for the Highlord platforms.\n");

    add_item(({"floor", "platform"}),
        "This platform is made of smooth red-veined black marble.\n");

    add_cmd_item(({"floor", "platform"}), ({"touch", "feel"}),
        "The floor is very smooth to the touch and it feels almost soft.\n");

    add_cmd_item(({"floor", "platform"}), ({"stomp", "hit", "knock", "tap"}),
        "It is rock marble.\n");

    add_item(({"platforms"}),
        "You look out across the Hall and see five platforms with chairs on " +
        "them and one platform which only has a bridge connecting it to a " +
        "higher platform in the middle of the hall.\n");

    add_item(({"wall"}),
        "There is a door there with a couple of standards hanging above it.\n");

    add_item(({"walls"}),
        "The walls all around this large hall are dark with shadows playing " +
        "along them.\n");

    add_item(({"ceiling"}),
        "You tilt your head back and try to see the ceiling. Far far above " +
        "you, hidden in deep shadows, is the ceiling of this huge vaulted " +
        "chamber. You estimate that it must reach at least 100 feet above " +
        "your head. As you strain to see as much as you can of the dark " +  
        "dome you seem to notice dark shadows moving up there. Something " +
        "glimmers and you feel the hairs at the back of your neck rise.\n");
 
    add_cmd_item(({"ceiling"}),
        ({"touch", "feel"}), "Unless you have the ability to sprout wings " +
        "and fly, there is no possibility whatsoever for you to be able to " +
        "reach the ceiling and touch it.\n");
    
    add_item(({"shadows", "shadow"}),
        "Dark shadows move and flitter along the walls and ceiling, " +
        "created by the low burning braziers.\n");

    add_item(({"brazier", "braziers", "burning braziers"}),
        "You see several large iron braziers evenly spaced throughout the " +
        "large hall. Coals are burning with a low glowing light, creating " +
        "shadows which seem alive.\n");

    add_cmd_item(({"brazier", "braziers", "burning braziers"}),
        ({"touch", "feel"}), "You will have to climb down from here if you " +
        "are to reach the braziers.\n");

    add_item(({"chair", "throne", "large chair", "carved chair"}),
        "This is a large chair carved out of oak. It is high-backed with " +
        "massive armrests and a suede seat.\n");

    add_cmd_item(({"chair", "throne", "large chair", "carved chair"}),
        ({"push", "pull", "lift"}),
        "You try hard to move the large chair but it seems to be securely " +
        "bolted to the floor.\n");

    add_item(({"high-back", "back", "back of chair"}),
        "On the highest point of the carved back of the large chair is a " +
        "pair of miniature standards.\n");

    add_item(({"armrest", "armrests", "massive armrests"}),
        "They are carved from oak with the ends resembling dragons' claws.\n");

    add_item(({"centre", "middle"}),
        "A slender bridge of rock from the north reaches a higher platform " +
        "standing in the very centre of this large hall. A set of narrow " +
        "stairs lead up to the platform made from rock curling upward from " +
        "the floor like a giant hooded snake.\n");

    add_item(({"high platform", "higher platform", "snake", 
               "giant hooded snake"}),
        "You would need to get closer to it to get a better look.\n");

    add_item(({"bridge", "slender bridge"}),
        "It is made of black rock and seems to defy the laws of gravity " +
        "making it seem as if it will break at any moment.\n");

}
