#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    
    set_short("A secluded pond");
    set_long("Water wells up from the ground to form a small pond, " +
        "which is surrounded by the bare rock of the mountains " +
        "to the south and east. A stream runs out of the pond to " +
        "the west.\n");

    add_item(({"pond", "water"}), "The pond is about two feet across, " +
        "and enclosed on the south and east side by bare rock. Water wells " +
        "up from the bottom of the pond, and flows out in a small stream " +
        "to the west.\n");
    add_item(({"creek", "stream"}), "The stream is less than a foot wide. " +
        "It gurgles quietly through the grass, flowing to the west.\n");
    add_cmd_item(({"water"}),"drink","@@drink_water@@");
    add_search(({"spring","pond","water"}),8,"/std/coins",-3);
    add_item(({"rock","mountains","bare rock"}),"The rock here is too " +
        "steep to climb, making it impossible to travel to the east or " +
        "south.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );
}

string
drink_water()
{
    int val = 100 + random(300) + random(300);
    if (TP->drink_soft(val,1))
    {
	TP->drink_soft(val,0);
	write("You drink some water from the pond and feel refreshed.\n");
	say(QCTNAME(TP) + " drinks some water from the pond.\n");
    }
    else
      write("You don't feel thirsty at all at the moment.\n");
    return "";
}

