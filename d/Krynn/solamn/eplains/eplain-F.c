#include "local.h"
inherit TDIR+"eplain_base";

int
no_pass()
{
    write("The ford is not yet passable.\n");
    return 1;
}

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("At the Vingaard River");
    set_long("This is the eastern shore of the Vingaard River. " +
        "The river is flowing from south to north. The water at this " +
        "spot on the river is very low, and a track leads down into " +
        "the river. The track leads out again on the other side.\n");
    add_item(({"track", "ford", "river", "vingaard river", "water"}), 
        "This appears to be a ford across the Vingaard River, with a " +
        "track entering the river here, and emerging again on the other " +
        "side.\n");
    add_item(({"shore", "eastern shore"}), "The water of the river " +
        "laps softly onto the shore.\n");

    add_std_exits();
    add_exit("beyond_ford","west","@@no_pass@@",6,1);

    herbs = HERB_MASTER->query_herbs( ({ "shore", }) );
}
