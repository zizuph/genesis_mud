inherit "/d/Gondor/rohan/horn/helmsdeep.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define STRENGTH_NEEDED 50

/* Prototypes */
int c_enter(string str);
int str_test();
void cross_stream();

void 
create_helmsdeep_room()
{
    set_short_desc("Outside the Deeping-wall");
    set_extra_long("Outside the Deeping-wall. "+
    "The wall rises high overhead, and "+
    "the battlement juts over the top like a sea-delved cliff. "+
    "A culvert pierces the wall just to the northwest, and a stream "+
    "flows out the culvert and down the slope. ");

    add_item("culvert","The interior of the culvert is pitch dark.\n");
    add_item("stream","The stream is quite rapid at the outlet from the "+
    "culvert.\n");
    add_item(({"parapet","battlement"}),BS("The parapet protects the top "+
    "of the wall, here and there are clefts in the stone through which "+
    "archers can shoot. Nothing more can be seen from this side.\n"));
    add_item(({ "wall", "deeping-wall", "deeping wall" }), BSN(
    "The wall, which runs northwest and southeast, is twenty feet high; "+
    "its top is sheltered by "+
    "a parapet. The front is smooth and the great stones are set "+
    "with such skill that no foothold can be found."));
    add_item("slope", "A field of grass slopes down towards the "+
    "road.\n");

    GRASS;
    FIELD;
    GORGE;
    CLIFFS;
    MOUNTAINS;

    add_exit(ROH_DIR+"horn/gorge/out_wall1","northwest",cross_stream,5);
    add_exit(ROH_DIR+"horn/gorge/ofield3","northeast",0);
    add_exit(ROH_DIR+"horn/gorge/out_wall3","southeast",0);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("plain")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("meadow")), }),
        ({ "field", "gorge", }), 5);
}

public void  
init()
{
    ::init();
    add_action("c_enter","enter");
}

int 
str_test()
{
    int str;
    str = TP->query_stat(SS_STR);
    if (str > STRENGTH_NEEDED)
        return 1;
    else
        return 0;
}

int 
c_enter (string str)
{
    int ok;
    if ( str == "culvert" || str == "stream" )
    {
        ok = str_test();
        if (ok == 1)
        {
            set_dircmd("culvert");
            TP->move_living("into the culvert", ROH_DIR + "horn/in_culvert");
            return 1;
        }
        else
        {
            TP->catch_msg("As you try to enter the culvert, you discover "+
            "that the current is too strong for you.\n"+
	    "You are swept downstream.\n");
            TP->move_living("down the stream", ROH_DIR +"horn/gorge/causeway");
            return 1;
        }
    }
}

void 
cross_stream()
{
    TP->catch_msg("You cross the stream.\n");
}

