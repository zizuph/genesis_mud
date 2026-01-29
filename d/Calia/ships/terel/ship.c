
/* Ship from Gelan to Terel, 

   Coded by Maniac & Jaacar, 27/11/95
*/


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
		TEREL_PORT,
                WATER5,
		WATER4,
		WATER3,
		WATER2,
		WATER1}));
	set_time_between_stops(({
		15,
		2,
		2,
		2,
		2,
                2,
		15,
		2,
		2,
		2,
		2,
                2}));
    set_ticket_id("gelan-terel line");
    set_board_enabled(1);
    set_name("ship");
    add_name("boat");
    add_adj("magical");
    add_adj("crystalline");
        set_short("mysterious crystalline ship");
    set_long("A magical ship made almost entirely of magical, flawless "+
             "crystal, blending into its sea environment and changing " +
             "with the light and movement of the waves.\n");
}


/*
 * Function name: short
 * Description:   Return the short description of the object.
 */
public varargs string
short(object for_obj)
{
    switch (time() % 18) {
        case 0:
        case 1:
        case 2: return "magical crystalline ship";
                break;
        case 3:
        case 4: 
        case 5: return "shimmering wave ship";
        case 6:
        case 7:
        case 8: return "rippling water ship";
        case 9:
        case 10:
        case 11: return "deep dark ship";
        case 12:
        case 13:
        case 14: return "ship of crashing foam";
        default: return "almost invisible ship";
    }
}



int
board(string what)
{
	object ticket, *tmp;

	if (!board_enabled)
		return 0;
	if (what && (!sizeof(tmp =
		FIND_STR_IN_OBJECT(
			what,E(TP))) || TO != tmp[0]))
		return 0;
	if (TP->query_average_stat() >=20)
		return::board(what);
	write("You board the ship.\n");
	E(TP)->set_dircmd(what);
	TP->move_living("boarding the ship", query_deck()[0]);
	return 1;
}
