#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>

#include "locals.h"
#include "lossarnach_herbs.h"

void
create_area_room()
{
    set_areatype(5);
    set_areadesc("open field");
    set_whereis("near");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("To the west tall trees rise into the sky, leaving "+
      "nothing to be seen there save the forest. In the distance "+
      "to the east you can glimpse some fields. South of here a "+
      "small hill seems to rise from the plain field.");

    add_item(({"trees","forest"}),"The forest extend from the south "+ 
      "trough the land and all the way north to the foot of "+ 
      "the mountains it seems.\n");
    add_item("sky","You throw your head back looking straight up "+
      "into the sky.\n");
    add_item("field","Far away to the east, there seem to be fields.\n");
    add_item("hill", BSN("As you examine the hill you notice that it is "
	+ "in fact a hut. It looks like a hill because grass of growing "
	+ "on the roof of the hut, making it difficult to recognize it."));

    add_exit(THORN_DIR + "t2","west",0,2);
    set_up_herbs( ({ ONE_OF_LIST(LOSSARNACH_HERBS),
	ONE_OF_LIST(LOSSARNACH_HERBS),
	ONE_OF_LIST(LOSSARNACH_HERBS), }),
      ({ "field", "forest", }), 4);
}

void
init()
{
    ::init();
    add_action("enter_hut","enter");
}


int
enter_hut(string where)
{
    if (!where)
	return 0;

    if (where != "hut" && where != "hill")
	return 0;

    write("You walk down the open field and enter the hut.\n");
    say(QCTNAME(TP)+" walks southwards and seems to disapeer into "+ 
      "the hill .\n",TP);

    this_player()->move_living("into hill", THORN_DIR + "hut");
    this_player()->init_command("look");
    return 1;
}


