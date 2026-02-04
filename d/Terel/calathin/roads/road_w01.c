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
    set_short("Western road just outside of town");
    set_long("This snowy road heads in a westerly direction toward a "
      + "range of mountains that thrust jagged peaks high into the sky. "
      + "Far to the south, you can barely make out a river with chunks "
      + "of broken up ice flowing slowly in an eastern direction. "
      + "There are a few trees around here, but not many, as this "
      + "area was extensively logged to build houses. "
      + "The Calathin town square is just east of there. "
      + "Amaylin's Quality Weapon Shop is directly to the north, while "
      + "the entrance to the Dragon Claw Pub is south.\n");

    add_item(({"shop", "shops"}), "There is one shop here, to the north. "
      + "It is for people who want to buy weapons.\n");

    add_item(({"pub", "pubs"}), "There is one pub here, to the south. "
      + "If you go east into the town square you will find others.\n");

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


    room_add_object(CALATHIN_DIR + "obj/wep_door2");
    room_add_object(CALATHIN_DIR + "obj/drag_door2");
    add_exit(CALATHIN_DIR + "square1_4", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w03", "west", 0);

}
