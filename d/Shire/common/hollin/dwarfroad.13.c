/* File: /d/Shire/common/hollin/dwarfroad.13.c */ 

#define ROOM_NUMBER 13
#define TEMP_DIR "/d/Shire/common/hollin/"

#include "defs.h"

inherit "/d/Shire/common/lib/dwarfroad";

create_dwarfroad()
{
    set_short("Ancient Dwarfroad");
    set_long(
          "You are walking on the Ancient Dwarfroad.\n"
        + "This is a broad, though seemingly little used dwarf-road which travels "
        + "towards the Misty Mountains in the east. South of you, you can hear "
        + "the trickling sounds of a river following the road. This is the "
        + "Sirannon River, or Gate Stream, which is coming down from a valley "
        + "in front of the Western Gate of Moria. "

        + "Getting ever higher up towards the Mountains, you notice that the vegetation "
        + "around you gets more sparse. You can see a steep slope in front of you, and "
        + "also a straight line going upwards towards an edge.\n"

    );

    add_item(({"dwarf-road", "road", "dwarven road" }),
          "This road, which is called the Dwarf-Road leads up to the Western Gate of Moria. "
        + "It is broad, but seems not to have been used much lately. It follows a river "
        + "which is in the south.\n"
    );
    add_item(({"mountains", "misty mountains", "tops" }),
          "These high unclimbable mountains divide the whole Middle Earth "
        + "in two. They rise up into the white cloads which brings cold and "
        + "ice to the tops of the mountains. You surely cannot cross east "
        + "over these mountains. If there is a way over east, it must be "
        + "through under the mountains. It is said that there used to be "
        + "a vast kingdom of dwarves here, but where is the entrance?\n"
    );
    add_item(({"river", "sirannon", "sirannon river", "gate stream", "gate-stream" }),
          "The river seems to have been very powerful before, but now it seems "
        + "to run down empty. Something must have blocked the flow of water, "
        + "but why, you can only figure.\n"
    );
    add_item(({"forest", "hollin", "hollin forest" }),
          "The forest north of you is quite dense and it seems only a bother to "
        + "try to walk into it.\n"
    );
    add_item(({"vegetation"}),
        "It gets more and more sparse the higher the terrain gets.\n"
    );
    add_item(({"slope"}),
        "It seems to be a steep slope. Perhaps you can go nearer to find out more about it?\n"
    );
    add_item(({"line"}),
        "Hmm, it's difficult to see what it is from here.\n"
    );
    add_exit(TEMP_DIR + "dwarfroad.14", "east", 0);
    add_exit(TEMP_DIR + "dwarfroad.12", "west", 0);
}
