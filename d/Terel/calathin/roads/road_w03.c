/*
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

public void
create_terel_room()
{
    set_short("Calathin westroad intersection");
    set_long("Here, just east of the center square of town, the western "
      + "road interects with a path leading north, toward an impressive "
      + "stand of silvery pines. West, a range of mountains thrusts jagged "
      + "peaks threateningly into the sky, a stunning backdrop for the rows "
      + "of town houses that line the way to the West Gate. "
      + "South, in the gap between the gem shop and the pub, you can see "
      + "a river flowing sluggishly by. " 
      + "You can hear the sounds of people in the town square to the east."
      + "\n");

    add_item(({"shop", "shops"}), "There are no shops here.\n");

    add_item(({"home", "homes", "townhouse", "townhouses", "row house", 
	"row houses", "house", "houses", "chimney" }), 
      "On either side of the road, a row of townhouses has been built "
      + "to house the expanding population of Calathin. Each one has "
      + "a chimney and a painted door.\n");

    add_item(({"door", "doors"}), 
      "The doors to the west have been painted bright colors.\n");

    add_item(({"river", "icy river"}), "It brings cold icy water from the "
      + "mountains to Calathin and eventually the sea.\n");

    add_item(({"trees", "pines", "pine trees", "silvery pines"}), 
      "These pine trees are tall and straight, perfect "
      + "for building log cabins and houses.\n");

    add_item(({"mountain", "mountains", "mountain range", "peaks"}), 
      "These mountains are beautiful.  Snow capped and majestic.  "
      + "Breathtaking. And terrifying.\n");

    add_item(({"road","west road","west","west gate","gate","snowy road"}), 
      "The road is frozen hard and leads toward Calathin's West Gate.\n");

    add_item(({"snow"}), "The snow in these parts reflects a silver color.\n");

    add_item(({"ice", "ground"}), "The ground is covered in a thin layer "
      + "of ice and snow. It never seems to warm up enough to melt.\n");

    add_item(({"woodsmoke", "smoke"}),
      "You can see it coming from the chimneys nearby.\n"); 

    add_cmd_item(({"woodsmoke", "smoke", "air"}), "smell",
      "The air smells of woodsmoke.\n");
    add_exit(CALATHIN_DIR + "roads/road_w01", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w02", "west", 0);
    add_exit(CALATHIN_DIR + "paths/path_s09", "north", 0);
    add_npc(CALATHIN_DIR +"npc/std_move_citizen", 2);	

}

