#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit TEMPLE + "std_base.c";

void
create_temple_room()
{
    

    set_short("Standard Hall room");
    set_long("The standard room with the items for the Great Hall of " +
        "Audience.\n");

    add_item(({"hall", "Great Hall of Audience"}), 
        "This hall is the very heart of the temple. It is large and you " +
        "see the black walls continue up towards the vaulted ceiling.\n");


    add_item(({"wall", "walls", "black wall", "black walls"}),
        "The walls are made of black stone streaked with dark-red " +
        "veins almost black as dried blood. Twisted patterns swirl " +
        "along the surface in a chaotic saraband as the flickering light " +
        "from the braziers create eerie shadows along the walls.\n");

    add_cmd_item(({"wall", "walls", "black wall", "black walls", "veins",
        "pattern", "patterns"}), ({"touch", "feel"}), "As you touch the " +
        "cold stone wall, you feel how the rough texture seems to move " +
        "beneath your fingertips almost like a slow pulsating life beneath " +
        "your hand. The chill of the stone grows colder and colder until " +
        "you are forced to withdraw your hand because of the pain running " +
        "up your arm.\n");

    add_cmd_item(({"wall", "walls", "black wall", "black walls"}),
        "push", "You begin to push on the wall, finding it hard to " +
        "keep the pressure long enough due to the intense cold radiating " +
        "from the black stone and the uncomfortable feeling of it being " +
        "alive. Unfortunately, you are unable to notice any portion of " +
        "the wall giving way to your efforts.\n");

    add_cmd_item(({"wall", "walls", "black wall", "black walls"}),
        "knock", "For some unexplainable reason you begin to knock on the " +
        "solid stone wall. A very faint and dull sound eachoes through the " +
        "vast hall.\n");


    add_item(({"veins", "dark-red veins", "pattern", "patterns"}),
        "As you stand and look carefully at the dark patterns imerged " +
        "in the black depths of the stone walls, they seem to writhe " +
        "and twist as if the walls themselves were alive.\n");

    add_cmd_item(({"veins", "dark-red veins", "pattern", "patterns"}),
        ({"trace", "follow"}), "You begin to slowly trace your finger " +
        "along one of the dark-red veins in the wall. You cannot help " +
        "but notice how the colour is so very much like old dried blood. " +
        "The vein is cold beneath your touch and as your finger continues " +
        "to follow the chaotic pattern, you feel a prickling sensation and " +
        "it grows numb.\nYou remove your finger from the wall.\n");



    add_item(({"floor"}), 
        "The floor is made of polished black stone resembling marble. " +
        "It is smooth and deepest black which seems to absorb all light.\n");

    add_cmd_item(({"floor"}),({"touch", "feel"}),
        "The floor is very smooth to the touch and it feels almost soft.\n");

    add_cmd_item(({"floor"}),({"stomp", "hit", "knock", "tap"}),
        "It is rock solid.\n");


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
        "Several large iron braziers are evenly spaced on the floor through" +
        "out the large hall. Coals are burning with a low glowing light, " +
        "creating shadows which seem alive.\n");

    add_cmd_item(({"brazier", "braziers", "burning braziers"}), 
        ({"touch", "feel"}), "You reach out to touch one of the braziers, " +
        "but quickly pull back your hand for fear of burning yourself.\n");
}

