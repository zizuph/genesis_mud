/*
 * This dragon is used to travel between Neraka and Sanction. It allows
 * some people to mount it, and fly to Sanction.
 */
#pragma strict_types
 
inherit "/d/Ansalon/guild/dragonarmy/dragons/dragon";

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define DRAGON_BACK NOBJ + "traveldragon_back"

void
check_back()
{
    if (!back)
    {
	    setuid();
	    seteuid(getuid());
	    back = clone_object(DRAGON_BACK);
	    back->set_dragon(TO);
    }
}

/*
 * Hack. Anyone may use this traveldragon, so anyone is the summoner
 * as far as the validation code is concerned. It's either this, or
 * duplicate lot of code.
 */
object
query_summoner()
{
    return this_player();
}

public int
dragonarmy_dragon_mount()
{
    check_back();

    if (sizeof(query_dragon_occupied()) > 1)
    {
	    write("There is no space left for you on the dragon.\n");
	    return 1;
    }

    say(({METNAME+ " mounts the " +colour+ " dragon.\n",
	    NONMETNAME+ " mounts the " +colour+ " dragon.\n",
	    "" }));
    write("You mount the " +colour+ " dragon.\n");
    TP->move_living("M", back, 1);

    say(({METNAME+ " mounts the " +colour+ " dragon.\n",
	    NONMETNAME+ " mounts the " +colour+ " dragon.\n",
	    "" }));

    return 1;
}


