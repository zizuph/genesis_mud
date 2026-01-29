inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


void
create_er_room()
{
add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   area = "outside of";
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 2;
   areadesc = "meadow";
   grass = "green";

   extraline = "The path is within sight of a large "+
   "farm, and to the east, a farmhouse is visible, nestled "+
   "between a pair of rolling hills. The fields stretch "+
   "out in all directions, some grassy, others with crops "+
   "in various stages of growth.  To the north is a dangerously " +
   "looking, old, abandoned hobbit hole dug into the hill.";

   add_item(({"path","farm","farmhouse","farm house"}),
   "The path seems to lead through the farmland directly "+
   "past the front of the farmhouse.\n");

   add_item(({"field","fields","pair","hill","hills","rolling hills"}),
   "The fields all around grow mostly grains and a few other crops "+
   "that seem to be either potatoes or peanuts. The hills "+
   "the farm house is built upon are the only two within sight.\n");

   add_exit(MICH_DIR + "abandoned","north",0,1);
   add_exit(MICH_DIR + "farmrd2","west",0,1);
   add_exit(MICH_DIR + "farmrd4","northeast",0,1);

}

