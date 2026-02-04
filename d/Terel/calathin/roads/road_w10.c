/*
    Updated by Shinto 10-21-98
  */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
   set_short("forest path behind townhouses");
   set_long(
    + "This is a path running east-west through the forest behind a "
    + "row of townhouses in western Calathin. "
    + "Above the walls, a spectacular mountain range seems to pierce the "
    + "sky like the jagged teeth of a mythical beast. "
    + "The wind is so bitterly cold it makes your bones ache.\n");  

   add_item(({"path", "east"}), 
      "This path runs east-west through the forest behind a row "+
      "of townhouses.\n");
	  
   add_item(({"home", "homes", "townhouse", "townhouses", "row house", 
      "row houses", "house", "houses", "chimney" }), 
      "On either side of the West road, a row of buildings "
    + "houses the expanding population of Calathin. Each one has "
    + "a chimney and a painted door.\n");
	
   add_item(({"door", "doors", "painted door", "painted doors"}), 
      "The doors to the townhouses have been painted bright colors.\n");
   
   add_item(({"river", "icy river"}), "It brings cold icy water from the "
    + "mountains to Calathin and eventually the sea.\n");

   add_item(({"trees", "pines", "pine trees", "silvery pines"}), 
      "These pine trees are tall and straight, perfect "
    + "for building log cabins and houses.\n");
	
   add_item(({"tree stumps", "stumps", "clearing"}), 
      "There are many tree stumps on both sides of the road. It looks "
    + "like many trees were cut for building purposes.\n");
	
   add_item(({"walls", "wall" }), 
      "A tall wall encircles the town of Calathin, creating an "
    + "island of safety in an otherwise dangerous wilderness.\n");

   add_item(({"mountain", "mountains", "mountain range", "peaks"}), 
      "These mountains are beautiful.  Snow capped and majestic.  "
    + "Breathtaking. And terrifying.\n");
	
   add_item(({"west gate","gate"}), 
      "It is the gate that guards the western entrance to Calathin.\n");
	  
   add_item(({"road","west road","snowy road"}),   
      "The road is frozen hard and leads toward Calathin's West Gate.\n");

   add_item(({"snow"}), "The snow in these parts reflects a silver color.\n");

   add_item(({"ice", "ground"}), "The ground is covered in a thin layer "
    + "of ice and snow. It never seems to warm up enough to melt.\n");
	
   add_item(({"woodsmoke", "smoke"}),
      "You can see it coming from the chimneys nearby.\n"); 

   add_cmd_item(({"woodsmoke", "smoke", "air"}), "smell",
      "The air smells of woodsmoke.\n");

    add_exit(CALATHIN_DIR + "roads/road_w11", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w09", "west", 0);	

}
