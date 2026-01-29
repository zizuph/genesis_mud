#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../../std/defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
        set_short("Path in the forest");
        set_long("@@long_desc");

        add_exit(FROOMS+"/@@random_forest","south");
        add_exit(FROOMS+"/@@forest_or_path","northeast");
        add_exit(FROOMS+"/@@random_forest","west");
        add_exit(FROOMS+"/@@random_forest","east");
        add_exit(FROOMS+"/@@random_forest","north");
        add_exit(FROOMS+"/@@random_forest","northwest");
        add_exit(FROOMS+"/path4","southeast");
        add_exit(FROOMS+"/path2","southwest");

        add_item(({"tree","trees","forest"}),
                "The trees on the both sides make the path so "+
                "narrow that it is hardly seen. You have an "+
                "instant feeling of beeing watched.\n\n");

        add_item(({"ground","path","track"}),
                 "The track is crossed by gnarled roots here and "+
                 "there. False trails lead in every direction. "+
                 "You can see animal tracks, some of them quite "+
                 "fresh.\n\n");

}

string
random_forest()
{
        write("Oh, no! You are lost now! You can wander here"+
              " FOREVER!\n\n");
        return "forest"+random(20);
}

string forest_or_path()
{
 if(TP->query_prop(HAS_PATH_HINT) ||
    QH_QUERY_QUEST_COMPLETED(TP,"tricksters_entrance")) 
      return "spath1";

 return random_forest();
}

string long_desc()
{
 string res;

 res="You are on a path leading through dark forest. "+
     "The forest on the both sides of the path is "+
     "so dense that you do not dare to step aside. "+
     "You hear threatening growls from the "+
     "undergrowth. The forest seems to be wild "+
     "but not uninhabited. The path comes from southwest,"+
     "and breaks sharply to southeast.";
 if(TP->query_prop(HAS_PATH_HINT) ||
    QH_QUERY_QUEST_COMPLETED(TP,"tricksters_entrance")) 
      res+="You see small , almost invisable path leading northeast "+
        "of here.";
 return res+"\n\n";
}
