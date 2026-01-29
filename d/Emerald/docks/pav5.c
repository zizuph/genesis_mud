#include "defs.h"

inherit PAV_ROOM;

#include <language.h>

#if AGENT_PRESENT
void
reset_room()
{
    object agent;
    string str;

    if (present("ticketing agent"))
    {
	return;
    }

    setuid();
    seteuid(getuid());
    agent = clone_object(DOCK_NPC_DIR + "agent");
    agent->move(this_object(), query_counter_subloc());
    str = LANG_ADDART(agent->query_nonmet_name()) +
        " arrives behind the counter.\n";

    tell_room(this_object(), ({ str, str, "" }));
}
#endif

void
create_pav_room()
{
    add_exit("pav1", "west");
    add_exit("pav6", "northeast");
    add_exit("pav8", "southeast");

    add_information_desk();

#if AGENT_PRESENT    
    reset_room();
#endif
}


