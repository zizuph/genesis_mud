/* nship.c
 * borrowed from Gondor's ship.c
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";
#include <cmdparse.h>
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <language.h>
#include "/d/Gondor/common/lib/time.h"

#define SHIP_IS_STOPPED "_ship_is_stopped"

object pier = find_object("/d/Gondor/guilds/bnumen/ship/water/at_anchor");
int message_away();

void
create_ship()
{
    object cap;    
    seteuid(getuid());
/* decks */
    set_deck(BNUMEN_DIR + "ship/ndeck2");
    add_deck(BNUMEN_DIR + "ship/ndeck1");
    add_deck(BNUMEN_DIR + "ship/ndeck3");
/* cabins */
    set_cabin(BNUMEN_DIR + "ship/ncabin_hall1");
    add_cabin(BNUMEN_DIR + "ship/ncabin_hall2");
    add_cabin(BNUMEN_DIR + "ship/ncabin_hall3");
    add_cabin(BNUMEN_DIR + "ship/ncabin_hall4");
/*
    add_cabin(BNUMEN_DIR + "ship/ncabin2_hall1");
    add_cabin(BNUMEN_DIR + "ship/ncabin2_hall2");
    add_cabin(BNUMEN_DIR + "ship/ncabin2_hall3");
    add_cabin(BNUMEN_DIR + "ship/ncabin2_hall4");
*/
/* guild rooms */

    add_cabin(BNUMEN_DIR + "rooms/train_hall");
    add_cabin(BNUMEN_DIR + "rooms/start_room");
    add_cabin(BNUMEN_DIR + "rooms/lib_houses");
    add_cabin(BNUMEN_DIR + "rooms/lib_lords");
    add_cabin(BNUMEN_DIR + "rooms/lib_public");



    set_places_to_go(({BNUMEN_DIR + "ship/water/at_anchor",
                       BAY_DIR + "openwater",
                       BAY_DIR + "openwater2",
                       BAY_DIR + "openwater3",
                 BNUMEN_DIR + "ship/water/at_sea",
                 BAY_DIR + "openwater3",
                 BAY_DIR + "openwater2",
                 BAY_DIR + "openwater",
                 }));
    set_time_between_stops(({35,
        20,
        13,
        13,
        13,
        13,
        13,
        13,
}));
    set_ticket_id("the Black Star line");
    set_name("barque");
    set_adj(({"long", "black"}));
    add_name("ship");
    add_name("star");
    set_long("The long black barque towers over you with its tall " +
        "masts. It was clearly built for distant journeys and " +
        "could carry hundreds of warriors into battle. The silken " +
        "sails are midnight black. A steel battering ram is affixed " +
        "to the bow.\n");
/*
    enable_reset();
*/

}

/*
void
reset_ship()
{
    start_ship(location);
}
*/

int
board(string what)
{
    object ticket, *tmp;

    if (!board_enabled)
	return 0;

/* other checks here */

    write("You board the ship.\n");
    environment(TP)->set_dircmd(what);
    TP->move_living("boarding the ship", query_deck()[0]);
    return 1;


}

/*
 * Function name: start_ship
 * Description  : Make the ship do its thing
 * Arguments	: where - the location number to start in
 * Returns	: 0 - failed to start the ship
 *		  1 - ship started
 */
public varargs int
start_ship(int where)
{
    int time;
    float next_time;


    if (!places_to_go || !time_between_stops || !query_deck() ||
	sizeof(places_to_go) > sizeof(time_between_stops) 
	 || !query_callout_fq())
	return 0;
    if (where)
    {
	if (where < 0 || where >= sizeof(places_to_go))
	    return 0;
	location = where;
	move(places_to_go[where]);
    }
    else 
	move(places_to_go[0]);
    call_arrive(environment());
    call_no = time_between_stops[where];
    if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
	set_board_enabled(1);

    tell_room(pier, "All aboard!  The " + short() + " leaves in " +
		(time = query_callout_fq() * time_between_stops[where]) +
		" seconds!\n");
    }
    next_time = itof(query_callout_fq() * time_between_stops[where]);
    set_alarm(next_time, 0.0, &message_away());
    sail_away_out_on_the_open_sea();

    return 1;
}

/*
 * Function name: sail_away_out_on_the_open_sea
 * Description	: The core of the ship; this is called every callout_fq
 *		  seconds and will move the ship around at appropiate
 *		  intervals
 *     Redefined without captain
 */
void
sail_away_out_on_the_open_sea()
{
    int time;
    float next_time;

    if (call_no < 1)
    {
	board_enabled = 0;
	location++;
	if (location >= sizeof(places_to_go)) 
	    location = 0;
	call_no = time_between_stops[location];


	call_left(environment(), places_to_go[location]);
	call_arrive(places_to_go[location]);
	move(places_to_go[location]);

	if (places_to_go[location]->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
	{
	    tell_room(places_to_go[location],
		capitalize(LANG_ASHORT(this_object())) + " just came in.\n");
        tell_room(places_to_go[location], "The " + short() +
		    " leaves in " + (time = query_callout_fq() * call_no) +
		    " seconds!\n");
        next_time = itof(query_callout_fq() * call_no);
        set_alarm(next_time, 0.0, &message_away());
	    set_board_enabled(1);
	}

	else
	    tell_room(places_to_go[location], capitalize(LANG_ASHORT(this_object()))+
		      " passes by.\n");
    }
    else 	
	call_no--;

    if (event_enable)
    {
	if (!(event_enable = !random_event()))
	    return;
        alarm_id = set_alarm(itof(query_callout_fq()), 0.0,
            sail_away_out_on_the_open_sea);
    } else
    {
        alarm_id = set_alarm(itof(query_callout_fq() * call_no), 0.0,
            sail_away_out_on_the_open_sea);
	call_no = 0;
    }
    return;
}

int
message_away()
{
    if (this_object()->query_prop(SHIP_IS_STOPPED) == 1)
        return 0;
    tell_room(pier, capitalize(LANG_ASHORT(this_object()))+
		      " starts to move away.\n");
}
/*
 * Function name: stop_ship
 * Description	: Stop the ship from doing it's thing
 * Arguments	: why - string with the reason the ship should be stopped
 */
public void
stop_ship(string why)
{
    //tell_us(why);
    // remove the alarm pointed to by alarm_id,
    // there should be only one alarm running at a time
    remove_alarm(alarm_id);
    add_prop(SHIP_IS_STOPPED, 1);
}
