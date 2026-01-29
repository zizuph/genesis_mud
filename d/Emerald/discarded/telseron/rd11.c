/*
 * The northwest road in Telseron
 * By Finwe, September 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void
create_room()
{
    set_short("A wide boulevard");
    set_long("   You're on a boulevard in the city of Telseron. " +
        "You are on Gardenia street. It is wide, clean and runs " +
        "in a northeast and southwest direction. The boulevard is " +
        "nicely shaded by the row of trees on either side of the " +
        "street. It is very busy as elves travel past " +
        "you going about their business. South of here is a nondescriptive, " +
        "stone building. Birds fly to " +
        "and from the roof. West is the town plaza. Southwest is " +
        "the park. A feeling of great peace and serenity can be " +
        "felt coming from that direction. Northeast, Fuschia, " +
        "Hibiscus, and Gardenia streets meet.\n\n");
 
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

    add_exit(TOWNSHIP_DIR + "pz02", "west");
    add_exit(TOWNSHIP_DIR + "rd12", "east");
    add_exit(TOWNSHIP_DIR + "rd07", "northeast");
    add_exit(TOWNSHIP_DIR + "pk03", "southwest");
 
}
 
void
reset_room()
{
}
