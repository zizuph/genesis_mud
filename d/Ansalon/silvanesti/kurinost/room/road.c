
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
    set_short("Road to Kurinost");
    set_long("@@long_descr");


    add_item("camp","A group of military tents is set to the southwest "+
       "and the camp seems to have its entrance heavily guarded.\n");
    add_item("road","A well worn road leads southeast towards the "+
       "abandoned village of Kurinost.\n");
    add_item("fork","The road from the north turns southeast here, but a "+
       "new path has been cleared leading southwest creating a fork in "+
       "the road.\n");
    add_item("kurinost","The Silvanesti city of Kurinost "+
        "to the east.  From here it appears to be more of "+
        "a village than a city.\n");
    add_item("forest","The forest here is healthy and "+
        "beautiful, but you notice that not far off to the "+
        "southwest the trees begin to look gnarled and ugly.\n");
    add_item("path","The path leads southwest to a camp.\n");
    add_item(({"tree","trees"}),"The trees here look normal and healthy.\n");
    add_exit(KROOM + "dock","north",0);
    add_exit(KROOM + "guard1","southwest",0);
    add_exit(KROOM + "road","southeast","@@no_exit");

    reset_kurinost_room();
}

string
long_descr()
{

    return "You stand at a fork in the road.  An old, worn road "+
       "leads southeast to Kurinost and north to the docks, while "+
       "a newly made path leads southwest into the Dragonarmy's "+
       "camp nearby.  "+season_descr()+tod_descr1()+"\n";
}

int
no_exit()
{
   write("Guards step out and tell you that the road to Kurinost is "+
     "blocked off to all travellers by orders directly from the Green "+
     "Dragonarmy's General.\n");
   return 1;
}
