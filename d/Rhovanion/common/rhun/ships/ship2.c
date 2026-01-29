#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Rhovanion/farlong.h"
#define EM_ROOM "/d/Emerald/"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(RHUN+"ships/cabin2");
    set_deck(RHUN+"ships/deck2");
	cap=clone_object(RHUN+"ships/captain2");
    set_captain(cap);
    set_places_to_go(({RHUN+"stown3/pier2",
			RHUN+"river/mouth",
			RHUN+"river/at_sea1",
			RHUN+"river/at_sea2",

			RHUN+"river/flying",

			EM_ROOM + "lake/channel3",
                        EM_ROOM + "lake/channel2",
                        EM_ROOM + "lake/channel1",
                        EM_ROOM + "lake/lake2",
                        EM_ROOM + "lake/lake1",
                    EM_ROOM + "lake/pier4",
                        EM_ROOM + "lake/lake1",
                        EM_ROOM + "lake/lake2",
                        EM_ROOM + "lake/channel1",
                        EM_ROOM + "lake/channel2",
                        EM_ROOM + "lake/channel3",

			RHUN+"river/flying",

			RHUN+"river/at_sea2",
			RHUN+"river/at_sea1",
			RHUN+"river/mouth"}));
    set_time_between_stops(({24,

			     2,
			     2, 
			     2,
			     2,
			     2,
			     2, 
			     2,
			     2,
			     70,
			     2,
			     24,
			     2,
			     2, 
			     2,
			     2,
			     2, 
			     2,
			     2,
			     2,
			     2}));
    set_ticket_id("the Rhovanion-to-Emerald line");
    set_name("ship");
    add_name("boat");
    add_adj("tilting");
    set_long("This seacraft tilts to the side as it goes along.\n");
}

void
sail_away_out_on_the_open_sea()
{
    int time, location, call_no, board_enabled, *time_between_stops;
    object pier, captain;
    mixed *places_to_go;
    string file_name_pier;

    location = query_location();
    call_no = query_call_no();
    board_enabled = query_board_enabled();
    places_to_go = query_places_to_go();
    time_between_stops = query_time_between_stops();

    if (call_no < 1)
    {
	board_enabled = 0;
	location++;
        set_location(location);
	if (location >= sizeof(places_to_go)) 
        {
	    location = 0;
            set_location(location);
        }
	call_no = time_between_stops[location];
        set_call_no(call_no);
	if (captain = query_captain())
        {
            file_name_pier = file_name(pier = environment(captain));
	    if (file_name_pier != query_deck()[0] &&
                file_name_pier != query_cabin()[0])
	    {
		captain->move_living("boarding the ship", query_deck()[0]);
		tell_room(pier,
		    capitalize(LANG_ADDART(short())) + " starts moving away.\n");
	    }
        }
	call_left(environment(), places_to_go[location]);
	call_arrive(places_to_go[location]);
	move(places_to_go[location]);
	if (places_to_go[location]->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
	{
	    tell_room(places_to_go[location],
		capitalize(LANG_ADDART(short())) + " just came in.\n");
	    if (captain)
	    {
		captain->move_living("the ship", places_to_go[location]);
		captain->command("say All aboard!  The " + short() +
		    " leaves in " + (time = query_callout_fq() * call_no) +
		    " seconds!");
		if (query_ticket_id())
		    captain->command("say Buy your tickets now or stay ashore!");
		call_out("give_leave_warning", time - 20);
	    }
	    set_board_enabled(1);
	}
	else
	    tell_room(places_to_go[location], capitalize(LANG_ADDART(short()))+
		      " passes by.\n");
    }
    else 
    {	
	call_no--;
        set_call_no(call_no);
    }

    if (event_enable)
    {
	if (!(event_enable = !random_event()))
	    return;
        call_out("sail_away_out_on_the_open_sea", query_callout_fq(), 0);
    } else {
 	call_out("sail_away_out_on_the_open_sea", query_callout_fq() *
				call_no, 0);
	call_no = 0;
        set_call_no(call_no);
    }
}

