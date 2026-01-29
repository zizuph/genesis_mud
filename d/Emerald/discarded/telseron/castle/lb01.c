/*
 * The library in the castle in Telseron
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
    set_short("The library");
    set_long("   You stand in the royal library. Books fill the " +
      "shelves of every imaginable subject. Here and there you " +
      "see elves studying books of different sizes. Occasionally "+
      "a busy elf will race in and look for a book, find it, and " +
      "dart out. Tables are spread around here for the convenience " +
      "of those who use the books. West and north both lead to " +
      "corridors.\n");

    add_item("shelves",
      "The shelves are filled with many different books of all " +
      "sizes and subjects. They reach to the ceiling and are full, " +
      "almost to the point of breaking.\n");
    add_item(({"book", "books"}),
      "You attempt to read the titles, but realize this is futile. " +
      "They are written in elven script and are indecipherable " +
      "to you.\n");
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
      "This marvelous light is multi-tiered. The crystals are made "+
      "This marvelous light is muti-tiered. The crystals are made " +
      "from perfectly shaped cut diamonds. Tall candles emit bright " +
      "light, which is caught by the diamonds. The light is " +
      "reflected onto the walls into a thousand rainbows.\n");
    add_item(({"up", "ceiling"}),
      "The ceiling is decorated with floral designs.\n");
    add_item(({"table", "tables"}),
      "They are large and made from oak. Some are littered with " +
      "books while others are occupied with busy elves.\n");

    add_exit( TCASTLE_DIR + "cor09", "north");
    add_exit( TCASTLE_DIR + "cor12", "west");
}

void reset_room()
{
}
