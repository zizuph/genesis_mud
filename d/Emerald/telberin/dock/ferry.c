/*
 *  /d/Emerald/telberin/dock/ferry.c
 *
 *  This is the ferry that travels between the City of Telberin
 *  and the north shore of the lake.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name:        create_ship
 * Description  :        set up the ship
 */
public void
create_ship()
{
    object  cap;
    
    setuid();
    seteuid(getuid());

    set_deck("/d/Emerald/telberin/dock/ferry_deck");
    cap = clone_object("/d/Emerald/telberin/dock/ferryman");
    cap->arm_me();
    set_captain(cap);

    set_places_to_go( ({ "/d/Emerald/telberin/dock/ferry_dock",
                         "/d/Emerald/telberin/dock/lakeroom1",
                         "/d/Emerald/telberin/dock/lakeroom2",
                         "/d/Emerald/telberin/dock/lakeroom3",
                         "/d/Emerald/north_shore/dock",
                         "/d/Emerald/telberin/dock/lakeroom3",
                         "/d/Emerald/telberin/dock/lakeroom2",
                         "/d/Emerald/telberin/dock/lakeroom1" }) );
    set_time_between_stops(({	24,
				 3,
				 3,
				 3,
				24,
				 3,
				 3,
				 3,
				}));

    set_ticket_id("Telberin to North Shore Line");

    set_name("ferry");
    set_short("long flat ferry");
    add_name( ({ "ship", "boat", "vessel", "ferryboat" }) );
    add_adj( ({ "long", "flat", "sailing" }) );
    set_long("This sailing vessel is much smaller than most you have"
      + " seen. It more closely resembles a barge than a sailing"
      + " ship, and appears suited to transport both passengers"
      + " and cargo on a single deck.\n");

    enable_reset();   
} /* create_ship */


/* 
 * Function name:        reset_ship
 * Description  :        reload the captain, if he has been
 *                       killed
 */
void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
        cap = clone_object("/d/Emerald/telberin/dock/ferryman");
	cap->arm_me();
        set_captain(cap);
        cap->move(query_deck()[0]);
        start_ship(location);
    }
} /* reset_ship */

