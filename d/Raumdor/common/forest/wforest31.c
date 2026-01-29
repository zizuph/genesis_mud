/* The road through the forest of Raumdor, by Sarr */
#include "defs.h"
inherit FOREST_ROAD_ROOM;
inherit COMMON_LIB_DIR + "carvings";

void
create_room()
{
    ::create_room();
    set_short("On an old path, nearing a stone archway");
    set_long("You are on an old cobblestone path, tightly flanked by a " +
      "gloomy forest to the north and south. To the west is a stone wall " +
      "with a stone archway. You have a the feeling that are safer here " +
      "than in the forest, at least during the day. The road continues " +
      "east.\n");
    add_item(({"beach", "shore"}), "It looks like a cold, sandy shore.\n");
    add_item("wall", "The wall runs along the beach, north to south, with an " +
      "arch here to the west. It is made of smooth stone blocks. " +
      "Looking closely, you can see subtle carvings all over the surface.\n");
    add_item(({"arch","archway"}), "The archway forms a passage through the " +
      "wall, west towards a beach. You notice that, like the rest of the " +
      "wall, it is covered in carvings. However, the distribution of the " +
      "carvings is most dense on the archway itself.\n");
    add_item(({"blocks", "stone blocks"}),
      "The stone blocks are in good condition for being seaside. Although " +
      "easy to miss on first glance, they are covered in carvings.\n");
    add_item("carvings", "@@carvings_description@@");
    add_cmd_item(({"wall", "stone wall"}), "climb", "Aside from being too " +
      "tall and smooth to climb, you could just walk through the archway.\n");
    add_exit(FOREST_DIR + "wforest45","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest46","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest32","east");
    add_exit(FOREST_DIR + "wforest22","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest21","south",0,FOREST_FATIGUE);
    add_exit(BEACH_DIR + "beach1","west");
}

