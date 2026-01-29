/*
 * The south road in Telseron
 * By Finwe, September 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void
create_room()
{
    set_short("A wide boulevard");
    set_long("   A boulevard in the southern part of the city. " +
        "All around you, many elven folk greet you as they go " +
        "about their business. It is wide and well used. A great " +
        "road rises from the north and meets here. Great trees " +
        "grow here, shading the area. Sunlight dapples the area " +
        "as it peaks through the tree branches. The street leading " +
        "north is called Amaryllis street.\n\n"); 
 
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
    add_item("castle",
        "It's an imposing building. It twinkles in the bright " +
        "sunlight casting a rainbow all around it.\n");
 
    add_exit(TOWNSHIP_DIR + "rd23", "north");
    add_exit(TOWNSHIP_DIR + "rd30", "east");
    add_exit(TOWNSHIP_DIR + "rd28", "west");
 
}
 
void
reset_room()
{
}

