// Modified by Lilith, Mar 2022: slight re-map of area, added
//   items and fleshed out descriptions.

inherit "std/room";

#define PATH "/d/Terel/common/town/"

create_room(){
   
   set_short("Street");
   set_long("You are on a small paved cobblestone street " +
      "southwest of Calathin's Silver Hall and arena. "+
      "A peaceful hush hangs over this place, a welcome "+
      "silence compared to the bustle of town. "+
      "The street is lined " +
      "with towering pine trees that crowd together and "+
      "cast a deep shade. Father southwest you can "+
      "see a bridge that will take you to the sacred garden.\n");
      
   add_exit(PATH + "street/street1", "northeast", 0);
   add_exit(PATH + "garden/entrance", "southwest", 0);
   add_exit(PATH + "street/tower_entrance", "west", 0, 0, 1);
 
   add_item(({"street", "cobbles", "reddish cobblestones",
      "red cobblestones", "cobblestones"}), 
      "This is a small street cobbled in reddish cobbles. It "+
      "leads northeast into the town square and southwest toward the "+
      "river.\n");
   add_item(({"north", "northwest", "town square"}),
      "To the north is the arena and Calathin town square.\n");
   add_item(({"south", "river", "southwest", "sacred garden"}),
      "To the south lies the river. You can get to it by "+
      "following the street southwest.\n");
   add_item(({"tree", "trees", "pine trees", "pines", "ancient pines", 
        "ancient pine tress", "ancient trees", "boughs"}),
    	"These ancient pine trees are all tall and straight, " +
        "with thick trunks that are perfect for building cabins "+
		"and houses. They grow thickly together and cast a deep, "+
        "mysterious shade. Snow has collected on the boughs. \n");
   add_item(({"shade", "deep shade", "west", "trail", "old trail",
      "irregularity"}),
      "The ancient pine trees grow so thickly together that they cast a "+
      "mysteriously deep shade over the area. Your eyes just make out "+
      "a small irregularity in the shade that might be an old trail "+
      "leading west.\n");	
    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");	  	  
    add_item(({"bridge", "old bridge"}), "It is very old and made " +
      "of wood.\n");	 	  
}
