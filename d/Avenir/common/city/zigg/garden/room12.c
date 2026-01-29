// Ziggurat galleria (room12.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    set_long("Iridescent Sourcelight shines down on this garden terrace, "+
      "providing just enough light for the skilled gardeners to "+
      "cultivate a wide variety of plants. Over the raised aqueduct that "+
      "serves to barricade the terrace edge sprawls a dream-like view "+
      "of the City. The top two levels of the Ziggurat tower above you, "+
      "each level at least several times your height. A white flagstone "+
      "path runs from the tunnel entrance to the northwest toward the "+
      "west over a continuous lawn of grass planted in rich soil "+
      "contained by the black stone walls which make the Ziggurat. "+
      "Flower beds and deep stone planters hold irises and snapdragons "+
      "of every color and shade. Orchid vines climb the Ziggurat wall, "+
      "stretching toward the stairs that rise above the tunnel inside "+
      "and curtain the entrance.\n");

    add_exit("room11", "east", "@@exit_string");
    add_exit(ZIG_RL3 + "garden", "northwest", "@@f_vines");
}

public int
f_vines(void)
{
    write("As you approach the tunnel, the curtain of orchid vines "+
      "move, parting to allow you entrance.\n");

    return 0;
}

static void
garden_items(void)
{
    ::garden_items();

    add_item(({"stairs", "tunnel"}),
      "To the northwest, a tunnel leads back inside the Ziggurat. It passes "+
      "under the main stairway up the side of the Ziggurat. The stairs are "+
      "not accessible from here, however.\n");

    add_views("From this side of the "+
      "Ziggurat you can see the High Lord Commisioner's enclave "+
      "to the south, opulent noble houses circle the High Lord's "+
      "palace on the central hill.", "enclave, giving it");

    add_rock("detailed etching of a willow wand with serpents wrapped "+
      "around in a helix", ", the symbol of Sachluph");

}

static void
garden_flowers(void)
{
    add_flower("iris");
    add_flower("snapdragon");
    add_flower("orchid");

    ::garden_flowers();
}
