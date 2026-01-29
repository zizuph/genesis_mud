#include <stdproperties.h>
#include "defs.h"

inherit "/d/Khalakhor/std/room";

void
create_khalakhor_room()
{
    set_short("Igneous' sleeping room");
    set_long("This room is where Igneous sleeps when "+
      "he isn't at his keyboard and has decided to power idle!!\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(STAND_DIR + "workroom", "workroom");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (ob->query_real_name() == "igneous")
	ob->add_prop(LIVE_S_EXTRA_SHORT," is snoring loudly");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    if (ob->query_real_name() == "igneous")
	ob->remove_prop(LIVE_S_EXTRA_SHORT);
}
