#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Gateway lane");
    set_long("You are walking along Gateway Lane, which heads east from "+
      "here to eventually meet up with the Caravan Gate. To the west you "+
      "can see where the road passes by Highland Gate and crosses High "+
      "street, which separates the Caravan district from the Noble district. "+
      "Towering to the north are the massive city walls of Kabal, while in "+
      "the south a high stone wall can be seen encircling a large, imposing "+
      "edifice.\n");

    add_item(({ "road" }),
      "The street is paved in cobblestones, with most of the cobbles looking "+
      "worn and slightly cracked from heavy use.\n");

    add_item(({ "massive city walls", "city walls", "walls" }),
      "This large stone barrier is made of the finest stone mined from the "+
      "Hespyre mountains, which lie east of Kabal. The city walls rise up "+
      "to a height of at least thirty feet.\n");

    add_item(({ "high stone wall", "stone wall", "wall" }),
      "The wall to the south stands at fifteen feet in height and encircles "+
      "a barely visible edifice, stretching west and east from here.\n");

    add_item(({ "edifice" }),
      "All that is visible of the building from this vantage point is the "+
      "dark grey, almost black stone it is made of.\n");

    add_exit(CVAN + "high-gate", "west");
    add_exit(CVAN + "gateway/s2", "east");
}
