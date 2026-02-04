/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 


public void
create_room()
{
    ::create_room();
    set_short_desc("road");
    set_long_desc("road");
    set_long("As you crest the top of the hill, a snow covered pass opens " +
             "to the northeast leading through the vast Dragon Tooth " +
             "mountains. Rolling snow tufted foothills can be seen leading " +
             "to the southwest.\n");

    add_item(("foothills","snow tufted"),
             "Snowy foothills spread from the southwest to the northwest " +
             "The only safe path southbound would be to travel to the southwest.\n");


    add_exit(DEFAULT + "road02", "northeast");
    add_exit("/d/Terel/sorgum/tomb/hill_mid", "southwest");
    add_exit("w/tomas/workroom", "southwest");

    reset_room();
}


