#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Rooftop of a large manor house in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"surroundings","flotsam","view","view of town",
            "view of flotsam","town"}),"Beneath you sprawls the " +
      "wretched town of Flotsam like a cancer on the coastline. " +
      "To your north opens up the Blood Bay. To your south and east " +
      "beyond the limits of the town spreads a great forest.\n");
   add_item(({"gargoyles","gargoyle"}),"These grotesque spouts project from " +
      "the roofs gutter. To your mind they too closely resemble a " +
      "crouching draconian for your liking.\n");
   add_item(({"window","small window"}),"This small window looks " +
      "like it has been broken deliberately. You might be " +
      "able to squeeze in it. \n");
   add_item(({"gutters","gutter"}),"Crumbling gutters line the rooftop " +
      "of the manor you are standing on. At each corner they " +
      "end in gargoyles.\n");
   add_item(({"roof","tiled roof","steep tiled roof","steep roof"}),
      "This tiled roof is very steep, and you constantly need to watch your footing. \n");
   add_item("attic","At the top of the steep tiled roof is a window " +
      "leading into the manor's attic.\n");
   add_item("manor","You are standing on the rooftop " +
      "of it! \n");
   
   add_cmd_item(({"down","down wall"}),"climb",
      "@@climb_down");
   
   add_cmd_item(({"in window","through window","into window"}),"squeeze",
      "@@enter_window");
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on " +
   "top of the steep tiled roof of a deserted manor. From " +
   "up here you can see all of the town of Flotsam and its " +
   "surroundings. Crumbling gutters end in grotesque gargoyles. " +
   "A single small broken window further up the roof seems to " +
   "lead into the attic. " + season_descr() + "\n";
}

string
climb_down()
{
   write("You climb down the wall of the manor and onto a " +
      "neighbouring rooftop. \n");
   TP->move_living("down the wall",FROOM + "rooftop1",1,0);
   
   return "";
}

string
enter_window()
{
   write("You squeeze through the small window and into " +
      "a dim attic.\n");
   TP->move_living("into the window",FROOM + "attic",1,0);
   
   return "";
}
