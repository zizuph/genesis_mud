/*
    Updated by Shinto 10-21-98
	Updated by Lilith, Mar 2022: Added first townhouse in 
	   Calathin that players can buy.
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
    set_short("Westgate neighborhood of Calathin");
    set_long("This snowy road heads in a westerly direction toward a "
      + "range of mountains that thrusts threatening peaks into the sky. "
      + "Rows of townhouses line the north and south sides of the road, "
      + "each with a chimney and a brightly-painted door. "
      + "This looks like a good neighborhood to settle in. "
      + "It is far enough from the town square to be quiet, but still near "
      + "enough to benefit from easy access to shops and pubs."
      + "\n");

    add_item(({"shop", "shops"}), "The shops are all east of here.\n");

    add_item(({"home", "homes", "townhouse", "townhouses", "row house", 
	"row houses", "house", "houses", "chimney" }), 
      "On either side of the road, a row of townhouses has been built "
      + "to house the expanding population of Calathin. Each one has "
      + "a chimney and a painted door.\n");

    add_item(({"door", "doors", "painted door", "painted doors"}), 
      "The doors have been painted bright colors. "
      + "There is a red door to the north and an orange door to the "
      + "south.\n");

    add_item(({"river", "icy river"}), "It brings cold icy water from the "
      + "mountains to Calathin and eventually flows to the sea.\n");

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
	  
    add_npc(CALATHIN_DIR +"npc/std_move_citizen", 2);
	
    add_exit(CALATHIN_DIR + "roads/road_w02", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w05", "west", 0);
	add_exit("/d/Terel/houses/calathin1/entry", "north", 0);
}
