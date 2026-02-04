// path_s00.c   This is the inherited base room for the path_s rooms.
// This path runs southwest from the big Tree and then west behind 
// the townhouses toward the West Gate.
// Lilith Mar 2022

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";
#include "/d/Terel/include/herb_arrs.h"

public void
add_here()
{    	   
    add_item(({"snow"}), 
      "The snow reflects the sunlight off the top of " +
      "the trees, giving it a silver color. Many feet have "+
      "tamped down the snow, some of them leaving imprints "+
      "alongside the path, too.\n");

    add_item(({"path"}), "It is a little less beaten than the roads, but " +
      "it still looks well-worn.\n");

    add_item(({"river", "icy river"}), "It brings cold icy water from "+
      "the mountains to Calathin and eventually flows to the sea.\n");		

    add_item(({"ice", "ground"}), "The ground is covered in a thick layer "+
      "of snow and ice. It never seems to warm up enough to melt. There "+
      "are some imprints in the snow here.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item(({"up", "sky", "blue sky" }),
      "The sky is intensely blue and cloudless. The only thing you "+
      "see in it is woodsmoke.\n");

    add_item(({"woodsmoke", "smoke"}),
      "You can see it coming from the chimneys nearby.\n"); 

    add_cmd_item(({"woodsmoke", "smoke", "air", "fresh air", }), "smell",
      "The fresh air smells of pines and woodsmoke.\n");

    add_item(({"mountain", "mountains", "mountain range", 
	"view", "peaks", "horizon", "wilderness"}), 
      "What a view!  These mountains to the west are beautiful.  "+
      "Snow-capped and majestic.  Breathtaking.  "+
      "And terrifyingly harsh.\n");

    add_item(({"forest", "pine forest", "silver pine forest"}),
      "Calathin has encroached upon the forest of silver pines "+
      "that lies north of the river and extends all the way up "+
      "into the high hills of the icy mountains. The forest here "+
      "has been thinned out by judicious tree-cutting, as evidenced "+
      "by the numerous stumps scattered throughout.\n");		

    add_item(({"tree stumps", "stumps", "stump", "jagged stump",
	"splintered stump"}), 
      "There are tree stumps scattered here and there on both sides "+
      "of the path. The stumps are varying heights and some are cut "+
      "cleanly while others are more jagged and splintered.\n");

    add_item(({"imprints", "footprints"}), "Some imprints "+
      "in the snow are deeper than others.\n");		

    set_up_herbs( ({ one_of_list(FROST_HERBS),
	one_of_list(FOREST_HERBS),
	one_of_list(FOREST_HERBS) }),
      ({"here","forest","tree", "trees", "ground"}), 
      3 );

}

public void
add_trees()
{
    add_item(({"trees", "pines", "pine trees", "silver pines", 
	"tree","treeline"}), 
      "These pine trees are tall and straight, with thick trunks "+
      "perfect for building log cabins and houses. Their boughs are "+
      "draped in snow.\n");

    add_item(({"branch", "branches", "limb", "limbs", "bough", "boughs"}),
      "The trunks of the pines are bare of branches for 3 or 4 meters "+
      "and the branches are covered in snow.\n");		

    add_cmd_item(({"tree", "trees"}), "climb", "The trunks of the "+
      "trees are too icy to climb, and the branches are too high "+
      "to reach.\n");		
}	

public void
add_intree()
{
    add_item(({"trees", "pines", "pine trees", "silver pines", 
	"tree","treeline"}), 
      "This pine tree, like all the others around it, is tall "+
      "and straight, with a thick trunk. It has many branches "+
      "radiating away from the trunk, most of which are covered "+
      "in snow.\n");

    add_item(({"branch", "branches", "limb", "limbs", "bough", 
	"boughs"}),
      "The branch of the pine tree is thick but tapers rapidly "+
      "to a whip-like thinness. Smaller woody branches with "+
      "greenish-silver needles extend outward in a fan-like "+
      "configuration that seems perfect for holding snow.\n");		

    add_item(({"woody branches", "greenish-silver needles",
	"needles"}),
      "The needles of the pine tree are greenish-silver in "+
      "color.\n"); 		

    add_item(({"trunk", "tree trunk", "pine tree trunk", "bark",
	"rough bark", "tree bark"}),
      "The trunk is broader than your chest. The rough bark "+
      "is covered in ice.\n");		
}	


public void		
add_buildings()
{
    add_item(({"home", "homes", "townhouse", "townhouses", "row house", 
	"row houses","house","houses","chimney","building","buildings" }), 
      "You can see a row of buildings along the West Road that houses "+
      "the expanding population of Calathin. The buildings east of "+
      "here are mostly shops and other businesses on the town square.\n");

    add_item(({"walls", "wall", "sides" }), 
      "These are the sides of buildings.\n");

}

public void
add_town()
{

    add_item(({"town square"}),
      "You can't see it, but you can hear it. The town square lies "+
      "east of here.\n");

    add_item(({"huge tree", "huge pine", "huge pine tree", 
	"towering tree", "towering pine tree"}),
      "The tree looks like an ancient pine, about 100 meters tall or "+
      "more. It is towering above to the northeast.\n");

}

public void
create_terel_room()
{
    set_short("Base for path_s rooms");
    set_long("This is the base room for the path_s rooms.\n");  

}

