inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

#define M_DIR_M "/d/Rhovanion/common/esgaroth/npcs/"
#define CLOCK "/d/Gondor/elessar/lib/clock"
#define TIME (string)CLOCK->query_time_of_day()

static string extras = "\n";

create_room() {}

nomask string
ctime()
{
    return TIME;
}

nomask void
add_a_monster(string type)
{
    object ob;
    setuid();
    seteuid(getuid());
    ob = clone_object(M_DIR_M + type);
    ob->arm_me();
    ob->move(TO);
}

nomask void
reset_a_monster(string type)
{
    if (present("_esgaroth_monster_", TO))
        return;
    add_a_monster(type);
}

nomask void
set_extras(string str)
{
    extras = str;
}

nomask string
query_extras()
{
    return extras;
}
