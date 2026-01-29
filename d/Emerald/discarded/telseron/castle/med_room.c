/*
 * The meditation room in the castle in Telseron
 * By Finwe, November 1996
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"


void reset_room();
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("A corridor");
    set_long("   A feeling of serenity and peace fills the room. " +
      "This room is often inhabited by those searching for a " +
      "quiet place to reflect. Like the rest of the castle, the " +
      "room is carpeted, has tapestries hanging on the walls, " +
      "and has a richly decorated ceiling. Seats are placed " +
      "around the perimeter of the room. Many times, musicians " +
      "can be found here quietly composing a piece for the court "+
      "or poets can be seen writing verses which capture the " +
      "history of the people here. North and east both lead to "+
      "corridors while west takes you to the Great Hall.\n\n");

    add_item(({"up", "ceiling"}),
      "The ceiling has been richly painted with various scenes. They " +
      "depict the history of Telseron.\n");
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
    add_item("tapestries",
      "These wall coverings are large and colorful. They depict " +
      "past elves quietly contemplating, thinking, and studying.\n");
    add_exit( TCASTLE_DIR + "cor03",  "north");
    add_exit( TCASTLE_DIR + "cor05",  "east");
    add_exit( TCASTLE_DIR + "g_hall", "west");
}

void
reset_room()
{
}
