#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit TEMPLE + "std_base.c";

void
create_temple_room()
{
    
    set_short("Dungeon corridor room");
    set_long("This is a standard room for the corridors in the dungeon.\n");

    add_item(({"corridor", "dark corridor", "narrow corridor"}),
        "The corridor is narrow and dark as the walls seem to " +
        "absorb the light.\n");

    add_item(({"wall", "walls", "black wall", "black walls"}),
        "The walls are made of black stone streaked with dark-red " +
        "veins almost black as dried blood. Twisted patterns swirl " +
        "along the surface in a chaotic saraband as faint traces of " +
        "light create eerie shadows along the walls.\n");

    add_cmd_item(({"wall", "walls", "black wall", "black walls", "veins",
        "pattern", "patterns"}), ({"touch", "feel"}), "As you touch the " +
        "cold stone wall, you feel how the rough texture seems to move " +
        "beneath your fingertips. The chill of the stone grows colder " +
        "and colder until you are forced to withdraw your hand because " +
        "of the pain running up your arm.\n");

    add_cmd_item(({"wall", "walls", "black wall", "black walls"}),
        "push", "You begin to push on the wall, finding it hard to " +
        "keep the pressure long enough due to the intense cold radiating " +
        "from the black stone. Unfortunately, you are unable to notice " +
        "any portion of the wall giving way to your efforts.\n");

    add_cmd_item(({"wall", "walls", "black wall", "black walls"}),
        "knock", "For some unexplainable reason you begin to knock on the " +
        "solid stone wall. A very faint and dull sound can be heard.\n");


    add_item(({"veins", "dark-red veins", "pattern", "patterns"}),
        "As you stand and look carefully at the dark patterns imerged " +
        "in the black depths of the stone walls, they seem to writhe " +
        "and twist as if the walls themselves were alive.\n");

    add_cmd_item(({"veins", "dark-red veins", "pattern", "patterns"}),
        ({"trace", "follow"}), "You begin to slowly trace your finger " +
        "along one of the dark-red veins in the wall. You cannot help " +
        "but notice how the colour is so very much like old dried blood. " +
        "The vein is cold beneath your touch and as your finger continues " +
        "to follow the chaotic pattern, you feel it growing numb until " +
        "you almost lose all feeling in it.\nYou remove your finger from " +
        "the wall.\n");


    add_item(({"shadows", "shadow"}),
        "Dark shadows move and flitter along the walls and ceiling.\n");


    add_item(({"floor"}), 
        "The floor is made of polished black stone resembling marble. " +
        "It is smooth and deepest black which seems to absorb all light.\n");

    add_cmd_item(({"floor"}),({"touch", "feel"}),
        "The floor is very smooth to the touch and it feels almost soft.\n");

    add_cmd_item(({"floor"}),({"stomp", "hit", "knock", "tap"}),
        "It is rock solid.\n");


    add_item(({"ceiling"}), 
        "The ceiling is vaulted and made of the same stone " +
        "as the walls. The deep crevices in the texture seem to be " +
        "the blackest of black.\n");

    add_cmd_item(({"ceiling"}), ({"touch", "feel", "knock"}),
        "You try desperately to reach the ceiling but it is too high " +
        "for you.\n");

    add_prop(ROOM_I_LIGHT, 0);
}

