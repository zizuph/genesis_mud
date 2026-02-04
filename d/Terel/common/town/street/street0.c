inherit "std/room";
#include "/d/Terel/include/Terel.h"

void
create_room(){
   
   set_short("Calathin Street");
   set_long("You are on a wide street just south of the main "+
      "entrance to Calathin's town square. The street is paved "+
	  "with reddish cobblestones and lined with pine trees. " +
      "There are two grand buildings on either side. "+
	  "You can see windows, but no doors, so the entrances "+
      "are probably further north. South of here is the East "+
      "road, and a river beyond it.\n");	  
	  
   add_exit("/d/Terel/calathin/square1_4","north",0);
   add_exit("street1", "south", 0);   
   
   add_item(({"street", "cobbles", "reddish cobblestones",
      "red cobblestones", "cobblestones"}), 
      "This is a wide street cobbled in reddish cobbles. It "+
      "leads north into the town square and south toward the "+
      "river.\n");
   add_item(({"north", "town square"}),
      "To the north is the Calathin town square.\n");
   add_item(({"south", "river", "east road", "road"}),
      "To the south lies the way to the East Road and the river.\n");
   add_item(({"windows", "window", "building", "buildings",
      "grand buildings", "east building", "west building", "people"}),
      "Two grand buildings rise up on the east and west sides of the "+
      "street. Through the windows you can see people drinking and "+
      "dining.\n");   
   add_item(({"trees", "tree", "pine", "pines", "pine trees"}),
      "Young pine trees line the street. They are small, tame trees, "+
      "nothing like the ones that grow in the Silver forest.\n");
   add_item(({"river"}), "It flows south of here, in an east-west "+
      "direction.\n");
	  
}
