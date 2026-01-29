#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>
#include "locals.h"

object *guard = allocate(2),
*pig = allocate(2);

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("dusty");
    set_whereis("near");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_crop("grass");
    set_land("Gondor");
    set_extraline("The road is coming through a field to the northwest, "
      + "continuing southeast into the village. The outer parts of the "
      + "village spread south of the road, while to the northeast there "
      + "is another field.");
    add_item(({"field", "fields", }), VBFC_ME("exa_field"));
    add_item("thornlin","You see a small village.\n");
    add_item("village","You can spot Thornlin.\n");

    add_exit(THORN_DIR + "r2a","southeast",0,1);
    add_exit(THORN_DIR + "f9.c","northeast",0, 1);
    reset_room();
}

void
add_npcs()
{
    int     ig = sizeof(guard),
    ip = sizeof(pig);


    while (ig--)
    {
	if (!objectp(guard[ig]))
	{
	    guard[ig] = clone_object(NPC_DIR + "militia");
	    guard[ig]->set_long(BS("It is a militia man, he looks like he "+
		"is working like any other farmer, though he will "+
		"probably be ready to fight when summoned upon.\n"));
	    guard[ig]->set_random_move(100);
	    guard[ig]->MILITIA_2ND_PATH;
	    guard[ig]->arm_me();
	    guard[ig]->move_living("from the void", TO);
	}
    }

    while (ip--)
    {
	if (!objectp(pig[ip]))
	{
	    pig[ip] = clone_object(NPC_DIR + "pig1");
	    pig[ip]->ANIMAL_3RD_PATH;
	    pig[ip]->move_living("from the void", TO);
	}
    }
}

string
exa_field()
{
    object  clock = find_object(CLOCK);
    string  desc = "North of the village and the road there are fertile "
    + "fields extending up to the root of the mountains "
    + "visible in the distance.";

    switch (clock->query_season())
    {
    case "spring":
	desc += " The fields have been tilled recently and are "
	+  "obviously newly sown.";
	break;
    case "summer":
	desc += " There are different crops growing on the fields, "
	+  "close to the road there "+crop+".";
	break;
    case "autumn":
	desc += " The fields are full with ripe crops. On the field "
	+  "just north of the road, the "+crop+" is curved with "
	+  "the weight of full ears.";
	break;
    case "winter":
	desc += " All the fields are harvested and lie barren for the "
	+  "winter. Judging from the straw "+crop+" have been "
	+  "growing here.";
	break;
    default:
	break;
    }
    return BSN(desc);
}



void
reset_room()
{
    set_alarm(1.0, 0.0, "add_npcs");
}
