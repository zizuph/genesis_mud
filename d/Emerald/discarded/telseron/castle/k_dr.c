/*
 * King's drawing room in the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
void
create_room()
{   
    add_prop(ROOM_I_INSIDE, 1);
    set_short("King's drawing room");
    set_long("   This is where the King comes to relax and get away " +
        "from the affairs of the kingdom. The room is sumptuous and " +
        "comfortable. It is where the King often holds private " +
        "meetings with his advisors and counsellors. Many a late " +
        "night is spent here discussing the challenges of the land " +
        "and how to best face and overcome them. Couches and " +
        "comfortable chairs are spread around the room. Some pillows " +
        "are piled in the corner as well as a bag like chair. Servants " +
        "come and go through this room as they take care of the " +
        "King's wishes. A large chandelier hangs from the ceiling and " +
        "fills the room with a beautiful glow. The smooth pure white " +
        "walls are decorated with floral designs. The floors are " +
        "covered with rich carpets They look comfortable and are " +
        "luxurious. The ceiling is richly decorated with frescos.\n\n");
 
    add_item(({"couch", "couches"}),
        "These oak framed couches are large and comforable filled. " +
        "They are dark brown and have a rich paisley design on them. " +
        "Golden threads are woven into the couches.\n");
    add_item("chairs",
        "The easy chairs match the couches. They are comfortable " +
        "and dark brown with rich paisley designs.\n");
    add_item("chair",
        "This chair is the oddest seat you have ever sean. It is " +
        "circular, and sits on the floor. It is filled with pellets " +
        "of some sort. Odd, but the chair looks comfortable.\n");
    add_item("pillows",
        "They are large and fluffy. The pillows are filled with " +
        "feathers, comfortable and used to toss around and sit on.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling has been richly painted with various scenes. They " +
        "depict the strength of the King in battle.\n");
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface is so perfectly " +
        "covered you don't detect any seams. The walls have been "+
        "polished and are smooth to the touch.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs", 
               "carpet", "carpets"}),
        "The carpets are a rich forest green. Intricate designs of " +
        "leaves decorate the carpet in burgandy, royal blue, gold, " +
        "and dark brown.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall. They are made of inlaid emerald.\n");
    add_item("chandelier",
        "This marvelous light is muti-tiered. The crystals are made " +
        "from perfectly shaped cut diamonds. Tall candles emit bright " +
        "light, which is caught by the diamonds. The light is " +
        "reflected onto the walls into a thousand rainbows.\n");
 
    add_exit( TCASTLE_DIR + "k_room", "east");
    add_exit( TCASTLE_DIR + "g_rm01", "west");
}
