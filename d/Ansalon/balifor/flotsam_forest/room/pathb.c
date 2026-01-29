#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("On a small wagon trail between fields");
   set_long("@@long_descr");
   
   add_item(({"small wagon trail","small trail","wagon trail","trail"}),
      "You stand upon a small wagon trail that links the surrounding " +
      "farmhouses of Flotsam to the main road. It continues to the east " +
      "and west.\n");
   add_item(({"cultivated fields of wheat","fields of wheat","fields",
            "wheat","cultivated fields"}),"On either side of the road grows a " +
      "rugged variety of wheat, used to feed the surrounding population " +
      "of Flotsam.\n");
   add_item(({"wild grasses","grasses","weeds","side of the trail",
            "side of trail"}),
      "Many wild varieties of weeds and grasses grow at the side of " +
      "the trail.\n");
   add_item(({"rough path","path","rocks","cobblestone"}),
      "A rough path of broken cobblestone and rocks head to the " +
      "northeast " +
      "towards a farmhouse.\n");
   add_item(({"rundown farmhouse","rundown looking farmhouse","farmhouse"}),
      "To the northeast you can see a rundown looking farmhouse.\n");
   
   
   add_exit(FROOM + "patha","west",0);
   add_exit(FROOM + "pathd","east",0);
   add_exit(FROOM + "pathc","northeast",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + "You stand upon a small wagon trail between cultivated " +
   "fields of wheat. Wild grasses growing at the side of the trail " +
   "sway with the wind. A rough path leads off the trail to the " +
   "northeast " +
   "towards a rundown looking farmhouse, " +
   "while the trail continues to the east.\n";
}
