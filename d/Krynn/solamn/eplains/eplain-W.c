#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_short("At a waterfall");
    set_long("The plains stretch out around you, and even though " +
	     "they appear really flat, there are still ever so slight " +
	     "undulations. One of bigger inclinations can be seen here, and " +
	     "the mighty Vingaard River to your west has to pass this " +
	     "drop as well. The total difference is only about 2 metres, " +
	     "and the inclination quickly vanishes into the plain " +
	     "landscape around, but there is a waterfall here nonetheless. " +
	     "The river appears to be very shallow right at the top of the " +
	     "waterfall, allowing passage across the river to the west. " +
	     "A small stream arrives from the east, adding a negligible " +
	     "amount of water to the broad river.\n");
    add_item(({"plains","inclination"}),
		"The plains have a bigger inclination here forming a waterfall "+
		"on the river with a shallow ford on top of it.\n");
    add_item(({"waterfall"}),
		"The total drop of the waterfall is only about two metres.\n");
    add_item(({"river","vingaard river"}),
      "The river appears to be very shallow at the top of waterfall.\n");
    add_item(({"stream"}),
		"The small stream arriving from east joins the river here.\n");
    add_item(({"ford"}),
		"It looks like it is possible to cross the river to the west.\n");

    add_std_exits();
    add_exit("waterfall2.c", "west", "@@closed@@",6,1);

    herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );
}

int
closed()
{
    write("You make your way forward across the river, but the current " +
	  "is much stronger than what it appeared to be and what you can " +
	  "handle. You barely make it back to the shore.\n");
    return 1;
}
