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
        "You are on Begonia street. It is wide, clean and runs " +
        "in a northwest and southeast direction. The boulevard is " +
        "nicely shaded by the row of trees on either side of the " +
        "street. The boulevard is very busy as elves move pass " +
        "you going about their business. North of you is a stone " +
        "building. An occasional scream and muffled cries of pain " +
        "echo from the walls. West is another stone building. Its " +
        "sturdy construction looks to be able to protect whatever " +
        "is inside the building. Northwest is a serene and " +
        "peaceful park. Southeast of here is where Tulip, " +
        "Hibiscus, and Begonia streets meet.\n\n");
 
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
 
    add_exit(TOWNSHIP_DIR + "pk08", "northwest");
    add_exit(TOWNSHIP_DIR + "rd32", "southeast");
 
}
 
void
reset_room()
{
}
