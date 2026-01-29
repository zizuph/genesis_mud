#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/herald/herald.h"

#define EXIT1 HERALD_DIR + "path2","northwest",0,3
#define EXIT2 ER_DIR + "er3n","south",0,2
// it was east road er3n for the new part


void
create_er_room()
{
    int i;

    area = "just north of"; /* Distance from areaname */
    areaname = "Undertowers";
    land = "Eriador";
    areatype = 1;
    areadesc = "steep hill";
    grass = "high";

    extraline = "These steep hills are the Tower Hills, covered in high "+
    "green grass.  To the east and south, the terrain gets smoother and "+
    "more gentle, while north and west the hills continue to rise high "+
    "into the sky.  From this angle, the tips of the Three Elven Towers are "+
    "barely visible.  Northwest, a treeline blocks the view of the towers.";

    add_item(({"hills","hill","steep hills","tower hills","steep hill"}),
      "The Tower Hills are named because of the Three Elven Towers "+
      "which were built by Gilgalad and Elendil in the Second Age of "+
      "this world.  The hills themselves have naturally been around a bit "+
      "longer.\n");

    add_item(({"towers","elven towers","tower","three elven towers","tips"}),
      "You are quite near the Three Towers but the slope of the hills and the "+
      "treeline to the northwest block your view considerably.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);

    set_noshow_obvious(1);
    add_std_herbs("hills", 2933);
    set_search_places(({"slope","high grass","hillside","hills","grass","hill"}));

}
