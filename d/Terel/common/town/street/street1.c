inherit "std/room";
#include "/d/Terel/include/Terel.h"

void
create_room(){
   
   set_short("Street");
   set_long("You are on a street just south of the Calathin town " +
      "square. The street is paved with reddish cobblestone. Some small " +
      "pines grow along the edges of the street here. There is a grand " +
      "building directly west, with an arena of sorts beyond "+
	  "it. Southwest a small street leads toward the river, while "+
      "a long road heads east, past the South Gate.\nThere is a sign"+
      "post here to help travelers.\n");
   
   add_exit("street0", "north", 0);
   add_exit("street2", "southwest", 0);
   add_exit("/d/Terel/calathin/guild", "west",0);
   add_exit(CALATHIN_DIR + "roads/road_e00", "east", 0);	
  
   add_item(({"sign", "signpost"}), "Maybe you can read the sign?\n");

   add_cmd_item(({"sign", "signpost"}), "read",
        "The sign reads:\n" +
        "North:     Calathin Town Square.\n" +
        "East:      South Gate and Eastern wilderness.\n" +
        "West:      Silver Hall guild and arena.\n"+
        "Southwest: The Sacred Garden.\n");  
   add_item(({"street", "cobbles", "reddish cobblestones",
      "red cobblestones", "cobblestones"}), 
      "This is a wide street cobbled in reddish cobbles. It "+
      "leads north into the town square and south toward the "+
      "river.\n");
   add_item(({"north", "town square"}),
      "To the north is the Calathin town square.\n");
   add_item(({"south", "river", "southwest", "sacred garden"}),
      "To the south lies the river. You can get to it by "+
      "following the street southwest.\n");
   add_item(({"building", "buildings", "grand buildings", 
      "west building", "guild", "guild hall", "adventurer guild", 
      "stadium", "arena"}),
      "Two grand buildings rise up on the west sides of the "+
      "street. The one in the front looks like an aventurer's "+
      "guild, and behind it, an arena for tournaments.\n");   
    add_item(({"trees", "tree", "pine", "pines", "pine trees", 
      "boughs", "branches"}),
      "Pines grow thickly together here, casting a deep shade "+
	  "over the street. Snow rests on the boughs.\n");
   add_item(({"river"}), "It flows south of here, in an east-west "+
      "direction.\n");
   add_item(({"shade", "deep shade", "west", "east"}), 
      "The pine trees lining the street cast a mysteriously deep "+
      "shade over the area.\n");	
    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");	  
}
