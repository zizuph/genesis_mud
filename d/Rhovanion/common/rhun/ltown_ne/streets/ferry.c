#pragma save_binary

inherit "/d/Genesis/ship/ship";
#include "/d/Rhovanion/defs.h"

void create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_deck(RHUN_DIR+"ltown_ne/streets/ferry_deck");
    cap=clone_object(RHUN_DIR+"ltown_ne/streets/ferry_captain");
    set_captain(cap);
    set_places_to_go(({RHUN_DIR+"ltown_ne/streets/dock",
			RHUN_DIR+"ltown_ne/streets/bay1",
			RHUN_DIR+"ltown_ne/streets/bay2",
			RHUN_DIR+"ltown_sw/streets/dock", 
			RHUN_DIR+"ltown_ne/streets/bay2", 
			RHUN_DIR+"ltown_ne/streets/bay1"}));
    set_time_between_stops(({15, 
			    2, 
			    2, 
			    15, 
			    2, 
			    2}));
    set_ticket_id("the Rhun ferry line");
    set_name("ferry");
    add_name("boat");
    add_name("ship");
    add_adj("old");add_adj("wooden");
    set_long("This is an old wooden ferry.\n");
}