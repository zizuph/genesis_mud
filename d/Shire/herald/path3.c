/* Exit changed to lead to the new Herald join room
 * - Arman Kharas, 13 July 2018
 */

#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/herald/herald.h"

#define EXIT1 HERALD_DIR + "path2","south",0,3
#define EXIT2 "/d/Shire/guild/heralds/room/join","northwest",0,2


void
create_er_room()
{
    int i;

    area = "in"; /* Distance from areaname */
    areaname = "the Tower Hills";
    land = "Eriador";
    areatype = 3;
    areadesc = "dale";
    grass = "soft";
    treetype = "poplar";

    extraline = "This small dale is boxed in by four trapezoidal ridges "+
    "making this place a difficult one to escape.  Above you, to the southeast "+
    "rises the tallest of the Three Towers, the others obscured by the trees "+
    "topping the western hillside.  Where the western and northern ridges meet "+
    "a slight depression is formed, making the way easier.  The southern hill "+
    "is the least steep of them all.";

    add_item(({"dale","small dale","box","ridges","trapezoidal ridges"}),
      "The bottom of this small dale is only about fifteen meters by "+
      "fifteen meters, and the hills that rise up as ridges around this "+
      "dale are dozens of meters high.  The southern ridge is the smallest "+
      "and least steep, however.\n");

    add_item(({"western ridge","northern ridge","ridge","depression"}),
      "The western and northern ridges meet at nearly a right angle, "+
      "leaving a depression where water has run down the hillside or "+
      "some other erosion has taken place.\n");

    add_item(({"trees","tree"}),"The trees are of several kinds, poplars, "+
      "maples and oaks dominate, but also are a few small pines and cedars "+
      "trying to grow from the forest floor.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

    set_noshow_obvious(1);

    add_std_herbs("hills", 8370);
    set_search_places(({"slope","high grass","hillside","hills","grass","hill"}));

}
