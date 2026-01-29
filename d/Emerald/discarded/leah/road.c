inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    set_short("Main road in Leah");
    set_long("   This busy road has many people leaving there homes to travel to "+
      "their work, or shopping for the day.  Just west of here you can see "+
      "a townhouse.  And to the east of here you can see a few shops.  North "+
      "of here you can see a large marble tower that reaches up to the sky. "+
      "South you can see the centre of town.\n\n");

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
    add_item(({"homes", "home", "townhouse"}), "The townhouse looks small "+
      "and unkept.\n");
    add_item(({"shops", "shop", "east"}), "The shops to the east look warm "+
      "and inviting. Perhaps if you took a closer look you would find "+
      "something you would want to purchase.\n");
    add_item(({"town", "center", "centre"}), "You are north of the centre of "+
      "town. There are many people bustling about the centre.\n");


    add_exit(VILLAGE_DIR + "road3", "east");
    add_exit(VILLAGE_DIR + "alley2", "west");
    add_exit(VILLAGE_DIR + "tower", "north");
    add_exit(VILLAGE_DIR + "centre", "south");
}
