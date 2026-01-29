/*
For this file I had a look at
/d/Gondor/anorien/druedain/rangerfield2.c
*/
#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master");

#include "locals.h"
#include <language.h>

object  ox;

void
create_area_room()
{
    set_areatype(1);
    set_areadesc("flowery field");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("grass");
    set_grass("long green");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("There is a village just south of here.");

    add_item("village","You see some houses surounded by fields " +
      "and trees.\n");
    add_item(({"tree","trees"}), "You see some tall trees surounding the "+
      "houses.\n");
    add_item(({"field","fields"}), "You see some fields in the outer parts "+
      "of the village.\n");

    add_exit(THORN_DIR + "r1.c","southwest",0,2);

    reset_room();
}

void
add_npcs()
{
    if (!objectp(ox))
    {
	ox = clone_object(NPC_DIR + "oxen");
	ox->move_living("from the void", TO);
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, add_npcs);
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}

int
do_climb(string str)
{
    if (!str || (str != "tree" && str != "trees"))
    {
	NF("Climb what?\n");
	return 0;
    }

    str = "trees";
    NF("You cannot climb the "+str+", as even the nearst "+str+" are too far away.\n");
    return 0;
}

