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
    set_short("Westgate neighborhood of Calathin");
    set_long("This snowy road leads between the West Gate of Calathin "
      + "and the town square, with all of its shops and entertainment. "
      + "A range of mountains crowds the western sky, forming a spectac"
      + "ular background for the rows of town houses that line both sides "
      + "of the road. It is quiet enough that you can hear the rush of "
      + "the river to the south and the soughing of the pines in the "
      + "icy wind. The scent of woodsmoke fills the air.\n"
      + "\n");

    add_item(({"shop", "shops"}), "The shops are all east of here.\n");

    add_item(({"home", "homes", "townhouse", "townhouses", "row house", 
	"row houses", "house", "houses", "chimney" }), 
      "On either side of the road, a row of townhouses has been built "
      + "to house the expanding population of Calathin. Each one has "
      + "a chimney and a painted door.\n");

    add_item(({"door", "doors", "painted door", "painted doors"}), 
      "The doors to the townhouses have been painted bright colors. "
      + "There is a yellow door to the north and a green door to the "
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


    add_exit(CALATHIN_DIR + "roads/road_w04", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w06", "west", 0);
}
