
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include <ss_types.h>
#include <macros.h>


inherit KURINOST_OUT;

void
reset_kurinost_room()
{
    return;
}

create_kurinost_room()
{
    set_short("Green Dragonarmy Camp outside of Kurinost");
    set_long("@@long_descr");


    add_item("kurinost","The Silvanesti city of Kurinost "+
        "to the east.  From here it appears to be more of "+
        "a village than a city.\n");
    add_item("camp","You stand in the Green Dragonarmy's "+
        "camp at Kurinost.  The camp is noted by a series "+
        "of tents clustered in a clearing of the forest.\n");
    add_item("forest","The forest here is healthy and "+
        "beautiful, but you notice that not far off to the "+
        "southwest the trees begin to look gnarled and ugly.\n");
    add_item(({"tree","trees"}),"The trees here look normal and healthy.\n");
    add_exit(KROOM + "road1","northwest",0);
    add_exit(KROOM + "guard1","northeast",0);
    add_exit(KROOM + "road3","southeast",0);

    reset_kurinost_room();
}

string
long_descr()
{
   return "This is the Green Dragonarmy's camp outside "+
     "of Kurinost.  The camp is just outside the perimeter of the "+
     "nightmarish forest.  Trees here have yet to be affected by the "+
     "torturous disease that infects the woods to the southwest.  "+
     season_descr()+tod_descr1()+"\n";

}
