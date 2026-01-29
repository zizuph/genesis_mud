#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("At the river shore");
    set_long("You are on the shore of the Vingaard River, which is directly " +
	     "to your west. Here, a small stream coming from the plains from " +
	     "the east flows into the river.\n");
    add_item(({"river","vingaard river"}),
	     "This is the mighty Vingaard River, flowing through the Plains of " +
	     "Solamnia.\n");
    add_item(({"stream"}),
	     "This is a little stream coming from the east and flowing into " +
	     "the big river to the west.\n");
    add_item(({"plains","grass","bushes","tree","trees"}),
	     "The plains of Solamnia are covered with grass, bushes and the " +
	     "occasional tree.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );
}

