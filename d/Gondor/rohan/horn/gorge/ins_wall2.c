inherit "/d/Gondor/rohan/horn/helmsdeep.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define STRENGTH_NEEDED 50

void create_helmsdeep_room()
{
    set_short_desc("a field inside Helm's wall");
    set_extra_long("A field inside the wall. The wall runs from southeast "+
    "to northwest. A path follows the wall. At this point "+
    "the stream enters a wide culvert, leading through the wall. ");

    FIELD;
    GRASS;
    PATH;
    KEEP;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("wall","Helm's wall was built long ago by the sea-kings "+
    "from Gondor.\n");
    add_item(({"culvert","wide culvert"}),BS("The inlet of the culvert "+
    "is south of the track. It's dark inside the culvert.\n"));
    add_item("stream","The stream is quite rapid at the inlet of the "+
    "culvert.\n");

    add_exit(ROH_DIR + "horn/gorge/ins_wall1","northwest",0);
    add_exit(ROH_DIR + "horn/gorge/ins_wall3","southeast",0);

    set_up_herbs( ({ ONE_OF_LIST(HERBS),
                     ONE_OF_LIST(HERBS),
                     ONE_OF_LIST(HERBS), }),
                  ({ "field", "fields", "path", "gorge",
                     "ground", }), 3);
}
   
int str_test()
{
    int str;
    str = TP->query_stat(SS_STR);
    if (str > STRENGTH_NEEDED)
        return 1;
    else
        return 0;
}

int
c_enter(string str)
{
    int ok;
    if ( str == "culvert" || str == "stream" )
    {
        set_dircmd(str);
        ok = str_test();
        if (ok == 1)
        {
            TP->move_living("into the culvert",ROH_DIR +"horn/in_culvert");
            return 1;
        }
        else
        {
            write("As you try to enter the culvert, you discover "+
            "that the current is too strong for you.\n"+
	    "You are swept through the culvert and out the "+
	    "other side.\n");
            TP->move_living("into the culvert, swept away by the current",
            ROH_DIR +"horn/gorge/causeway");
            return 1;
        }
    }
}

void
init()
{
    ::init();
    add_action(c_enter,"enter");
}

