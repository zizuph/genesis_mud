inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("A wide boulevard");
    set_long("   A boulevard in the northern part of the city. " +
        "All around you, many elven folk greet you as they go " +
        "about their business. It is wide and well used. A " +
        "great road rises from the south and meets here. From " +
        "the south, a great deal of traffic comes and goes. In " +
        "the distance, a great castle rises. A nimbus of light " +
        "envelopes the castle, drawing you to it. The road that " +
        "meets Fuschia street is called Amaryllis street.\n\n");
 
    add_item("trees",
        "The trees are large with branches that form a canopy " +
        "across the boulevard. You don't recognise what kind of " +
        "trees they are but they resemble maples. The bark " +
        "is smooth to the touch and a silver color. A dim glow " +
        "surrounds each tree. Under the trees are small plantings " +
        "of colourful flowers.\n");
    add_item(({"road", "street", "boulevard"}),
        "The boulevard is constructed of white marble. So cleverly " +
        "constructed is it that the street seems to be one " +
        "continuous piece of marble. The road is well travelled, " +
        "but oddly enough, doesn't show any wear from all the " +
        "traffic. The boulevard surrounds Telseron like a " +
        "protective wall.\n");
    add_item("sky",
        "You can make the sky from between the canopy of trees. " +
        "It's a deep azure blue without a sign of any clouds.\n");
    add_item("ground",
        "You see a wide boulevard.\n");
    add_item("buildings",
        "A wide variety of buildings surround you.\n");
    add_item("elves",
        "These are the residents of Telseron. Like most elves, " +
        "They love forests, songs, and many good things.\n");
    add_item(({"plantings", "flowers"}),
        "The plantings are full of flowers which fill the " +
        "air with fragrance.\n");
    add_item(({"boulevard", "street"}),
        "The boulevard is constructed of wide stones. Oddly enough, " +
        "shows no sign of use. The boulevard is clean and encircles " +
        "the town.\n");
    add_item("ground",
        "You see a boulevard.\n");
    add_item("sky",
        "The sky is clear and blue. A large tree dominates the " +
        "southern horizon.\n");
 
    add_exit(TOWNSHIP_DIR + "board", "south");
    add_exit(TOWNSHIP_DIR + "rd05", "east");
    add_exit(TOWNSHIP_DIR + "rd03", "west");
} 
