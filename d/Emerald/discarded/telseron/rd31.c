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
    object gate;
    set_short("A wide boulevard");
    set_long("   A busy boulevard in the city of Telseron. " +
        "The boulevard is crowded with elves going about their " +
        "business. However, it is still clean despite all traffic " +
        "it gets. The street is wide and goes underneath a canopy " +
        "of trees that grows on either side of the street. From the " +
        "south, royal couriers and palace workers come, for this " +
        "marks the entrance to the Castle. The Castle twinkles in " +
        "the sunlight creating an aura that seems to surround it. " +
        "You are on Tulip street.\n\n");
 
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
 
    add_exit(TOWNSHIP_DIR + "rd32", "east");
    add_exit(TOWNSHIP_DIR + "rd30", "west");

   gate = clone_object( TOWNSHIP_DIR + "doors/gate_castle_in");
   gate->move(this_object());
   catch(call_other(TELSERON_DIR + "castle/" + "clone_handler", "??"));
}
 
void
reset_room()
{
}
