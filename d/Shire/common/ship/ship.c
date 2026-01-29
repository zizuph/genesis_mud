#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include "/d/Shire/common/defs.h"

void reset_ship();

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(SHIP_DIR + "cabin");
    set_deck(SHIP_DIR + "deck");
    cap=clone_object(SHIP_DIR + "riondir");
    set_captain(cap);
    set_places_to_go(({SHIP_DIR + "w6",
		       SHIP_DIR + "w5",
                       SHIP_DIR + "w4",
                       SHIP_DIR + "w3",
                       SHIP_DIR + "w2",
                       SHIP_DIR + "w1",
                       "/d/Genesis/start/human/town/pier3",
                       SHIP_DIR + "w1",
                       SHIP_DIR + "w2",
                       SHIP_DIR + "w3",
                       SHIP_DIR + "w4",
                       SHIP_DIR + "w5",
                       SHIP_DIR + "w6",
		       COMMON_DIR + "greyhaven/shore"}));

    set_callout_fq(3);
    set_time_between_stops(({1,
			     2,
			     1,
			     2,
			     3,
			     1,
			     20,
			     1,
			     2,
			     3,
			     1,
			     3,
			     1,
			     20}));

    set_name("ship");
    add_name("boat");
    add_adj("elegant");
    set_ticket_id("the shire line");
    set_long("This is an elegant ship in perfect condition.\n");
    set_alarm(900.0, 900.0, reset_ship);
}

void reset_ship()
{
    if(!objectp(query_captain()))
    {
        object cap;
        cap=clone_object(SHIP_DIR + "riondir");
        set_captain(cap);
      start_ship();
    }
}
