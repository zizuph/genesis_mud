#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>

object *guard = allocate(2),
*peasants = allocate(2);

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("low");
    set_whereis("near");
    set_crop("wheat");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");

    set_extraline("North of here you see fields covering the lands of"+
      " "+land+". South of here you see a well kept farm "+
      "which seems wealthy. The road comes running from "+
      "the east and enters a village to the west.");

    add_item(({"field","fields"}),"On the nearst field north of here you "+ 
      "see "+crop+" growing. They extend all "+
      "the way to some mountains in the north.\n");

    add_item(({"farm"}),"The main house lies just south of here, you can see "+
      "a barn left of the main house.\n");

    add_mountains();

    add_exit(THORN_DIR + "r6","west",0,1);
    add_exit(LEB_DIR + "road/nr3","east",0,1);
    add_exit(THORN_DIR + "f8","north",0,2);
    //  Closed as this room does not exist yet!
    //  add_exit(THORN_DIR + "farm1","south",0,1);


    reset_room();
}

void
add_npcs()
{
    int     ig = sizeof(guard),
    ip = sizeof(peasants);


    while (ig--)
    {
	if (!objectp(guard[ig]))
	{
	    guard[ig] = clone_object(NPC_DIR + "militia");
	    guard[ig]->set_long(BS("It is a militia man, he looks like he "+
		"is working like any other farmer, though he will "+
		"probably be ready to fight when summoned upon.\n"));
	    guard[ig]->set_random_move(10);
	    guard[ig]->MILITIA_2ND_PATH;
	    guard[ig]->arm_me();
	    guard[ig]->move_living("from the void", TO);
	}
    }

    while (ip--)
    {
	if (!objectp(peasants[ip]))
	{
	    peasants[ip] = clone_object(NPC_DIR + "peasants");
	    peasants[ip]->set_restrain_path(({CITY_HOUSES,ROAD_PATH}));
	    peasants[ip]->arm_me();
	    peasants[ip]->move_living("from the void", TO);
	}
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, "add_npcs");
}
