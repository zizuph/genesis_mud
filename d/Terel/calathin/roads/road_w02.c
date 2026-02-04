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
    set_short("A road heading westwards");
    set_long("This snowy road heads in a westerly direction toward a "
      + "range of mountains that thrusts jagged peaks high into the sky. "
      + "Rows of townhouses line the north and south sides of the road, "
      + "each with a chimney and a brightly-painted door. "
      + "South is the entrance to a shop that caters to people "
      + "interested in fine gems, while north you can buy quality "	
      + "lamps.\n");

    add_item(({"shop", "shops"}), "There are two shops here. One is for "
      + "gems and the other is for lamps.\n");

    add_item(({"home", "homes", "townhouse", "townhouses", "row house", 
	"row houses", "house", "houses", "chimney" }), 
      "On either side of the road, a row of townhouses has been built "
      + "to house the expanding population of Calathin. Each one has "
      + "a chimney and a painted door.\n");

    add_item(({"river", "icy river"}), "It brings cold icy water from the "
      + "mountains to Calathin and eventually the sea.\n");

    add_item(({"trees"}), "These pine trees are tall and straight, perfect "
      + "for building log cabins and houses.\n");

    add_item(({"mountain", "mountains", "mountain range", "peaks"}), 
      "These mountains are beautiful.  Snow capped and majestic.  "
      + "Breathtaking. And terrifying.\n");

    add_item(({"road", "west road", "west", "west gate"}), 
      "The road is frozen hard and leads toward Calathin's West Gate.\n");

    add_item(({"snow"}), "The snow in these parts reflects a silver color.\n");

    add_item(({"ice", "ground"}), "The ground is covered in a thin layer "
      + "of ice and snow. It never seems to warm up enough to melt.\n");


    add_exit(CALATHIN_DIR + "roads/road_w03", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w04", "west", 0);
    room_add_object(CALATHIN_DIR + "obj/gem_door2");
    room_add_object(CALATHIN_DIR + "obj/lamp_door2");
    add_npc(CALATHIN_DIR +"npc/std_guard", 1);	

}
