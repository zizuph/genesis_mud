#pragma save_binary
#pragma strict_types

#include "local.h"

inherit VILLAGE;

int do_enter(string str);

void
create_village_room()
{

    areaname = "Waymeet";
    land     = "the Shire";
    areatype = 1;
    areadesc = "paved road";

    extraline = "You are on the Great East Road, passing through the "
    +"middle of "+areaname+". To the west, the road leads to Michel "
    +"Delving, while if you venture east, you will eventually get to "
    +"the village of Bree. Roads also lead northwest and south from "
    +"here. Waymeet is a small but busy community "
    +"that has sprung up around the cross-road to service the people "
    +"travelling along the Great East Road, and it has a bustling inn as "
    +"well as the usual burrows that you would expect to find in "
    +"a hobbit hamlet. ";

    add_item("waymeet",
      "A small but lively hobbit community servicing the "
      +"travellers who travel the Great East Road.\n");


    add_item("michel delving",
      "Far to the west, this is the largest town in the Shire.\n");

    add_item("bree",
      "Far along the Great East Road, Bree marks the end of "
      +"civilization in the Shire.\n");

    add_item("inn",
      "This inn, called the Foaming Mug, is a large, two story building "
      +"that is the only building above ground in Waymeet. Occasional "
      +"shouts and gales of laughter can be heard from within. There "
      +"is a stable attached to the inn, where travellers can leave "
      +"their horses while they enjoy a mug of ale.\n");

    add_item("stable",
      "The stable is a small wooden building attached to the inn. "
      +"Horses and ponies are tethered up in here while their "
      +"owners visit the inn. The stable doors are closed, and seem "
      +"to be bolted from within, preventing entry.\n");

    add_item(({"burrow","hobbit hole","burrows","smial"}),
      "Waymeet is a small community, made up of several small "
      +"burrows and a large burrow, housing the families who "
      +"live in Waymeet. The burrows are situated around the "
      +"cross-road. They have little round doors and windows "
      +"set into the gentle hill on which Waymeet is set.\n");

    add_item("large burrow","This burrow seems much larger than "
      +"the other burrows of Waymeet. Its door is slightly ajar, "
      +"to let the cool breeze in.\n");

    add_exit(EAST_R_DIR + "er11","west",0,2);
    add_exit(EAST_R_DIR + "er13","east",0,2);
 //   add_exit(EAST_R_DIR + "er12s","south",0,1,1);
 //   add_exit(EAST_R_DIR + "foam_mug","inn");   
    add_exit(EAST_R_DIR + "er11n", "northwest", 0, 2);
    add_exit("/d/Shire/waymeet/rooms/streets/street_7", "north");
    add_exit("/d/Shire/waymeet/rooms/streets/street_8", "south");
}

void
init()
{
    ::init();
    add_action("do_enter","enter");
}

int
do_enter(string str)
{

    if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
    {
	write("You enter the large burrow.\n");
	say(QCTNAME(TP)+ " leaves, heading into the large burrow.\n");
	TP->move_living("M",VILLAGE_DIR + "waym/1a",1);
	return 1;
    }

    write("Enter what ? A "+str+" ? You can't do that!\n");
    return 1;
}

