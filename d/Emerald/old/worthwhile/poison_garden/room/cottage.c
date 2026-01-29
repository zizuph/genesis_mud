inherit "/std/room";
#include "../garden.h"
#include <macros.h>
#include <filter_funs.h>

static int alarm;

create_room()
{
    set_short("An old cottage");
    set_long("This one-room cottage looks extremely old and " +
	"dirty.  Strange and exotic plants are arranged " +
	"about the room and line the cottage's inner walls. " +
	" Two windows are positioned on either side of the door " +
	"you came in.  Strange as it may seem, " +
	"you feel as if the plants are watching your every move.\n");
  
    add_item(({"plant","plants"}), "Plants of all shapes and sizes " +
	"are placed around the room.  There is something " +
	"strange about them, but you can't put your finger on it.\n");
    add_item(({"wall","walls"}), "The old walls are nearly " +
	"hidden by the strange plants lining them.\n");
    add_item(({"window","windows"}), "Your vision is limited by " +
	"the vines covering the outer window, though you can " +
	"see the lay of the garden between them.\n");
}

void drag(object who)
{
    if (present(who))
    {
        return;
    }
     
    tell_room(this_object(), "A thick vine lances out from nowhere " +
	"and catches " + QTNAME(who) + " by the leg, dragging " + 
	who->query_objective() + " back in.\n");
    who->catch_tell("A thick vine wraps around your leg and drags you " +
	"back into the cottage.\n");
    tell_room(environment(who), "A thick vine wraps around " + 
	QTNAME(who) + "'s leg and drags " + who->query_objective() + 
	" into the cottage.\n", who);
    
    who->move_living("M", this_object(), 1);
}

void leave_inv(object ob, object to)
{
    object wither;
  
    ::leave_inv(ob, to);
  
    if (interactive(ob))
    {
    	if (alarm && !sizeof(FILTER_PLAYERS(all_inventory())))
    	{
	    remove_alarm(alarm);
	    alarm = 0;
    	}
    
    	if (!IS_WIZ(ob) && (wither = present("_wither_")) &&
	    (member_array(ob, wither->query_enemy(-1)) >= 0) && to && 
	    (member_array(file_name(to), query_exit_rooms()) >= 0))
    	{
	    set_alarm(0.5, 0.0, &drag(ob));
    	}
    }
}

void vine_touch()
{
    object *who = FILTER_PLAYERS(all_inventory());
  
    if (!sizeof(who))
    {
    	remove_alarm(alarm);
    	alarm = 0;
    	return;
    }
  
    who[random(sizeof(who))]->catch_msg("You feel something touch you " +
	"on the " + (({ "back of your neck", "back of your leg", "arm",
	"top of your head" })[random(4)]) + ".  When you look to see " +
	"what is there, you notice nothing near you except a few " +
	"plants.\n");
}
  
void init()
{
    ::init();
  
    if (interactive(this_player()) && !alarm)
    {
        alarm = set_alarm(120.0, 120.0, vine_touch);
    }
}
