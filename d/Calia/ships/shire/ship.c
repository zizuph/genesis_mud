#pragma save_binary

inherit "/d/Genesis/ship/ship";
#include <stdproperties.h>
#include "ship.h"
#include "/sys/cmdparse.h"

void
create_ship()
{
	object cap;
    
       setuid();
	seteuid(getuid());
	set_deck(SHIPS+"deck");
	set_cabin(SHIPS+"cabin.c");
	cap = clone_object(SHIPS+"captain.c");
	set_captain(cap);
	set_places_to_go(({
		GELAN_PORT,
		WATER1,
		WATER2,
		WATER3,
		WATER4,
        WATER5,
        WATER6,
        WATER7,
                SHIRE_PORT,
        WATER7,
        WATER6,
        WATER5,
		WATER4,
		WATER3,
		WATER2,
		WATER1}));
	set_time_between_stops(({
		24,
		3,
		3,
		3,
		3,
        3,
        3,
        3,
		24,
        3,
        3,
        3,
		3,
		3,
		3,
		3}));
        set_ticket_id("gelan-shire line");
	set_board_enabled(1);
	set_name("ship");
	add_name("boat");
	add_adj("swift");
        add_adj("green");
        set_long("The ship is painted a bright green. Its elegant design "+
		"tells you that it must be very swift. The triangular "+
		"white sail contains a figure of a green dolphin.\n");
}

