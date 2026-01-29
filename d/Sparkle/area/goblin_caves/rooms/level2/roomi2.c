/*
 * Level 2 entrance room
 * Boreaulam, August 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Bottom of stone stairs");
    set_long("You stand at the bottom of a set of massive, stone stairs " +
             "which march up into the darkness. A handful of small torches " +
             "have been hung on the walls, casting long shadows down the " +
             "stairs and out into a wide cave that spreads out before you " +
             "to the north. At the base of the stairs, two hunched gargoyles " +
             "have been carved out of a black granite, their eyes seemingly " +
             "casting a soft red glow.\n\n");
    add_item(({"stairs", "stair", "staircase", "stone stairs", "stone stair", 
                "stone staircase"}),
             "Draped in shadows, these stone stairs march up into the " +
             "darkness towards the surface. The steps themselves seem " +
             "to be chipped and worn with age, having been carved out of " +
             "the same grey granite as the rest of the caves.\n");
    add_item(({"gargoyles", "gargoyle", "statue", "statues",
                "black granite", "granite statue", "granite statues"}),
              "There are two statues of gargoyles, carved in intricate " +
              "details from black granite, which sit perched at the base " +
              "of the massive, stone stairs. The gargolyes are motionless, " +
              "yet a soft, red glow seems to eminate from their eyes as if " +
              "they are watching your every move.\n");
    add_item(({"eyes", "glow"}),
             "You have never quite seen something like this before. The " +
             "eyes of the gargoyles are clearly carved from the same black " +
             "granite as the rest of the statue, yet everytime you start " +
             "to turn you away, a red light seems to glow softly from them. " +
             "Perhaps this might not be the safest place for you to be.\n");
    add_item(({"torch", "torches"}),
             "A small handful of torches have been scattered around these " +
             "caves, hanging occasionally on the walls which line the stairs " +
             "and even out into the cave which opens up to the north. They " +
             "provide just enough light for you to see, but they also create " +
             "an abundance of eerie looking shadows.\n");
    add_item(({"shadow", "shadows"}),
             "Shadows cast by the torches reach out like long black fingers " +
             "attempting to grasp you as they stretch " +
             "across the grey stone of the stairs.\n");
    add_item(({"cave", "opening"}),
             "A larger cave seems to spread out, opening up before you to " +
             "the north.\n");
    add_item(({"dark", "darkness"}),
             "As you gaze down the stone steps, it almost feels as if the " +
             "torchlight is being swallowed by the darkness.\n");
    add_item(({"step", "steps", "stone steps"}),
             "These stone steps look to have been carved out of the stone " +
             "centuries ago. They are frequently chipped and heavily worn, " +
             "dipping in the middle of each step.\n");
    add_item(({"granite", "stone"}),
             "Everything seems to be made of stone here, from the grey " +
             "granite of the stairs and the cave around you, to the two " +
             "statues carved from a black granite.\n");
    add_item(({"grey granite"}),
             "Aside from the two statues, everything here from the ceiling " +
             "to the floor seems to have been crudely carved out from the " +
             "dull, grey granite of the mountain.\n");
    add_item(({"wall", "walls"}),
             "These walls have been crudely carved out of the mountain " +
             "itself, the dull grey of the granite being broken only " +
             "by the occasional torch which has been mounted on the walls.\n");
    add_item(({"floor", "ground", "down"}),
             "The ground beneath your feet is the same grey stone as the " +
             "walls and ceiling around you, only it has been worn smooth " +
             "from centuries of traffic.\n");
    add_item(({"ceiling", "up"}),
             "The grey stone of the ceiling has been crudely tunneled out of " +
             "the mountain itself. There does not appear to have been much " +
             "care taken, as jagged chunks of stone end up casting sinister " +
             "looking shadows across the stairs nearby.\n");

    add_exit("roomh3", "north");
    add_exit(ROOMS_DIR + "level1/roomc", "up");

} /* create_room */
