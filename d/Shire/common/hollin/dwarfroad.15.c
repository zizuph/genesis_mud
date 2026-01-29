/* File: /d/Shire/common/hollin/dwarfroad.15.c */ 

#define ROOM_NUMBER 15
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

        + "You are standing under some old stairs of old, carved out of the mountain. "
        + "You might follow this way up in the east, but the Main Road goes northeast "
        + "towards a winding road some hundred meters further north. Also, you can see "
        + "what once must have been a magnificient fall as the Sirannon River flowed "
        + "down the slope south of the Stairs, but now something must have stopped the "
        + "flow, because now only trickles of water run slowly down the fall.\n"

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
    add_item(({"stairs"}),
          "This must be dwarves work, magnificient as it is, though rotten "
        + "leaves and vegetation shows that this road has been abandoned maintainance "
        + "a long time ago.\n"
    );
    add_item(({"main"}),
        "Could be followed to the northeast or back down in the west.\n"
    );
    add_item(({"fall"}),
        "A sad view indeed, when considering the beauty of it in the past.\n"
    );
    add_exit("/d/Shire/common/hollin/steps", "east", 0);
    add_exit(TEMP_DIR + "dwarfroad.14", "west", 0);
//    add_exit(STAND_DIR + "mainroad.1", "northeast", "@@check_ne");
}


int check_ne()
{
  write("A stout, long-bearded dwarf steps up, barring your way with his "+
    "gleaming halberd. He roars: 'No one may pass this way, the road is not safe for "+
    "travellers yet. Check back soon, we are working on it as fast as "+
    "we can.'\n");
    return 1;
}
