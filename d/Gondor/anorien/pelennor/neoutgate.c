inherit "/d/Gondor/minas/lib/outgate";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "negatedefs.h"

object patrol;

void
add_stuff()
{
    if (!patrol) {
	patrol = clone_object(MINAS_DIR+"npc/gondor_leader");
	patrol->set_monster_home(ANO_DIR+"pelennor/neoutgate");
	patrol->set_restrain_path(({ANO_DIR}));
	patrol->set_patrol_size(5);
	patrol->arm_me();
	patrol->move(TO);
    }
}

void
create_outgate()
{
    set_gfile1(GFILE1);
    set_ofile(OFILE);
    set_ogroom(OGROOM);
    set_igroom(IGROOM);
    set_igdir(IGDIR);
    set_gdir(GDIR);
    set_grtoog(GRTOOG);
    set_gopen(GOPEN);
    set_gclosed(GCLOSED);
    set_short("Before the Causeway Fort");
    add_item("fort",BSN("This is the Causeway Fort, a gatehouse protecting the gate which "+
	"the road from Osgiliath to Minas Tirith passes through. "+
	"The road comes up from the northeast, on a walled causeway, and "+
	"runs up to the gate to the southwest. The fort is made of thick "+
	"stone walls, and there are strong battlements on its top."));
    add_exit(ANO_DIR+"road/or4","northeast","@@test_blocked",1);
}

int
test_blocked()
{
    int stopped;
    object attacker;
    attacker = TP->query_attack();
    if (objectp(attacker) && attacker->query_npc())
	/*
	    if (present(objectp(attacker)) &&
	      CAN_SEE(attacker,TP) &&
	      CAN_SEE_IN_ROOM(attacker) &&
	      attacker->query_npc())
	*/
    {
	stopped = TP->query_stat(SS_DEX) - attacker->query_stat(SS_DEX) + 85;
	if (stopped < 0)
	    stopped = 0;
	stopped = 12 - stopped/10;
	if (stopped < 1)
	    stopped = 1;
	if (stopped > 10)
	    stopped = 10;
	if (random(stopped))
	{
	    write("The " + attacker->query_nonmet_name() + " stops you!\n");
	    return 1;
	}
    }
    return 0;
}

