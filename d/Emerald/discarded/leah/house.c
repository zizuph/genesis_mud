inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    set_short("Inside Elven House");
    set_long("   This seems to be the foyer of a large house. Maybe a "+
	     "mayor used to live here?  There is a large rug in the center "+
             "of the room. A large fireplace dominates the southern wall, "+
             "above it hangs a portrait. There is plenty of space here to hold "+
             "a town meeting.  To the north you can see into the kitchen, "+
             "and to the east there is a living room.\n\n");

    add_item(("rug"), "It's a rather large woven rug, it is smooth and soft to "+
              "the touch. The colors of the rug match the room perfectly.\n");
    add_item(("fireplace"), "The fireplace is located on the southern wall. "+
              "There is a copper basket sitting beside it, with a matching "+
              "poker set on the other side.\n");
    add_item(("portrait"), "The portrait seems to be of a large family of elves. "+
              "There is a Elven male with a child apon his lap, a Elven woman, "+
              "standing behind him.  There are also six elven children sitting "+
              "at the Elven males feet. The pictures background seems to have "+
              "been taken in this very room.\n");
    add_item(("basket"), "The basket is made of copper, it is very sturdy. It "+
              "currently is full of wood.\n");
    add_item(("poker"), "The poker set is hand crafted. It looks like it has "+
              "helped to keep this house warm for a long time.\n");
    add_item(("kitchen"), "The kitchen appears to be very brightly decorated. "+
              "You can imagine the smells of the meals cooked in there.\n");
    add_item(("wood"), "The wood is neatly stacked in the basket.  You can "+
              "smell the fresh cut oak.\n");
    add_item(("living room"), "The living room seems quite and still, as if "+
              "it is lost in time.\n");

    add_exit(VILLAGE_DIR + "road2", "west");
    add_exit(VILLAGE_DIR + "kitchen", "north");
    add_exit(VILLAGE_DIR + "livingroom", "east");
}
