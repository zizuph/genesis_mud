inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{

    set_short("Centre of Leah");
    set_long("   You find that you are standing in the centre of an "+
      "elven village, known as Leah. The beauty of the village "+
      "astonishes you. To the north you can see a large white tower "+
      "surrounded by beautiful vibrant colours. To the west an alley "+
      "heads between two buildings. A quaint little chapel with "+
      "gardens is tucked away into the northeast. South from here the "+
      "street heads out to the gates.\n\n");

    add_item(({"tower", "large tower", "large marble tower", 
	"marble tower"}), "The tower is tall and graceful, its white "+
      "marble arching towering into the sky.\n"); 
    add_item(({"road", "main road", "street"}), "This wide cobblestone "+
      "road goes east to west through town.  It is bustling with "+
      "people.\n");
    add_item(({"village", "Leah"}), "The village spreads out before you "+
      "inviting you to explore it further.\n");
    add_item(({"people"}), "The people seem to be hurring around doing "+
      "there daily shopping.\n");
    add_item(({"cobblestone", "cobblestones"}), "The cobblestones are "+
      "laid in an intricate pattern.\n");
    add_item(({"garden","north", "gardens"}), "The brilliance and "+
      "colour of the garden spreads out everywhere. The true beauty "+
      "of the garden is too far away to truly appreciate.\n");
    add_item(({"west", "bank", "bank of Leah"}), "To the west you see "+
      "the bank of Leah.  A few of the villagers are doing their "+
      "daily business there.\n");
    add_item(({"east", "construction"}), "To the east you can see the "+
      "left over wood of a building.  It appears that the outside is "+
      "finished. You should take a closer look to find out if the "+
      "inside is also done.\n");
    add_item(({"town", "center", "centre"}), "You are in the centre of "+
      "town. There are many people bustling about the centre.\n");
    add_item(({"alley", "narrow alley"}), "The alley looks dirty and "+
      "yucky. Perhaps you would rather not enter it.\n");

    add_exit(VILLAGE_DIR + "road2", "south");
    add_exit(VILLAGE_DIR + "road", "north");
    add_exit(VILLAGE_DIR + "alley1", "west");
    add_exit(CHAPEL_DIR + "outside", "northeast");
}
