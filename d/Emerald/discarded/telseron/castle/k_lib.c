/*
 * The King's private library in the castle of Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
void reset_room();
 
void create_room()
{   
    reset_room();
    add_prop(ROOM_I_INSIDE,1);
    set_short("The King's private library");
    set_long("   You stand in the King's private library. Books " +
        "that he has collected fill the shelves. They are in good " +
        "condition and are in all sizes. A large table and an easy " +
        "chair are here. Some books are piled on the table, obviously " + 
        "left over from a late night research session by the King.\n\n");
 
    add_item("shelves",
        "The shelves are filled with many different books of all " +
        "sizes and subjects. They reach to the ceiling and full.\n");
    add_item(({"book", "books"}),
        "You attempt to read the titles, but fail. The script is " +
        "flowing and golden but nonetheless, it is indecipherable " +
        "to you. \n");
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface so perfectly " +
        "covered that you don't detect any seams. The walls have been "+
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
    add_item(({"up", "ceiling"}),
        "The ceiling is decorated with floral designs.\n");
    add_item("table",
        "It is large and made from oak. A few books are stacked " +
        "on it.\n");
    
    add_exit( TCASTLE_DIR + "g_rm02",  "east");
    add_exit( TCASTLE_DIR + "k_room", "west");
}
 
void reset_room()
{
}
