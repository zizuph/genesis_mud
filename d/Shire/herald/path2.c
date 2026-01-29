#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/herald/herald.h"

#define EXIT1 HERALD_DIR + "path1","southeast",0,3
#define EXIT2 HERALD_DIR + "path3","north",0,2


void
create_er_room()
{
    int i;

    area = "in"; /* Distance from areaname */
    areaname = "the Tower Hills";
    land = "Eriador";
    areatype = 3;
    areadesc = "hilltop";
    grass = "low";
    treetype = "poplar";

    extraline = "This hilltop has a small line of trees crowning this "+
    "steep hill.  Southeast is an opening that allows movement down and "+
    "north, the trees thin.";

    add_item(({"forest","trees","tree","line of trees"}),
      "The maple trees are densely packed here, but the forest is "+
      "a very small one.  Openings lead southeast and north.\n");

    add_item(({"hill","crown","steep hill"}),
      "Seen from this vantage point, the dense forest appears as "+
      "a crown on this steep hill.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);

    set_noshow_obvious(1);
    add_std_herbs("hills", 5546);
    set_search_places(({"slope","high grass","hillside","hills","grass","hill"}));

}
