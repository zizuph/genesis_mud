/*
 * Module to have an object summon the special traveldragon. This is a dragon
 * that lets people fly to places.
 *
 * This is not intended to be used directly by players.
 *
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

#include <macros.h>

private int dragon_is_summoned;
private object dragon;
private object room;

private void
summon_dragon(object tp)
{
    dragon_is_summoned = 0;

    if(objectp(tp) && E(tp) != room)
	    return;

    setuid();
    seteuid(getuid());
    dragon = clone_object(NNPC + "traveldragon");

    if (objectp(tp))
    {
        dragon->set_summoner(tp);
        dragon->set_gender(!tp->query_gender());
    }
    else
    {
        dragon->set_color("blue");
        dragon->set_age("adult");
        dragon->set_gender(0);
    }

    tell_room(room, "With a final beat of its leathery wings, "+
      LANG_ADDART(dragon->short())+ " lands here.\n");
    dragon->move_living("M", room);
}

private void
summon_message1(object tp)
{
    dragon_is_summoned = 0;

    if(objectp(tp) && E(tp) != room)
    	return;

    tell_room(room, "A cruel shriek from the skies alerts you to the " +
      "winged-form of a dragon bearing down upon you with great speed!\n");

    set_alarm(4.0, 0.0, &summon_dragon(tp));
    dragon_is_summoned = 1;
    return;
}

private void
summon_message2(object tp)
{
    dragon_is_summoned = 0;

    if(objectp(tp) && E(tp) != room)
	    return;

    tell_room(room, "In the distance, like a dark star on the horizon, " +
      "a winged-shaped creature makes its way towards you.\n");

    set_alarm(12.0, 0.0, &summon_message1(tp));
    dragon_is_summoned = 1;
    return;
}

/*
 * Function name: summon_dragonsteed
 * Description:   Summons the traveldragon
 * Arguments:     tp - living doing the summoning, usually an NPC.
 *                     If there is no living involved, set this to 0.
 *                target_room - if tp is specified, this is ignored.
 *                     Otherwise this is the room where the dragon should
 *                     appear.
 * Returns:       0 - success, non-zero failure
 */
public int
summon_dragonsteed(object tp, object target_room)
{
    if (objectp(tp))
        target_room = environment(tp);
    
    if(dragon_is_summoned)
    	return 1;

    if(objectp(dragon) && present(dragon, target_room))
    	return 2;

    if(objectp(tp) && !CAN_SEE_IN_ROOM(tp))
    	return 3;

    if(target_room->query_prop(ROOM_I_INSIDE))
	    return 4;

    if(objectp(dragon) && dragon->query_dragonarmy_dragon())
    {
	    dragon->check_back();
	    if((dragon->query_back())->query_flying())
    	    return 5;
	
	    tell_room(dragon->query_back(), "The dragon turns to you and snarls, "+
	        "making it very clear that you should dismount.\n"+
	        "You swiftly dismount.\n");
	    (dragon->query_back())->dismount_all();
	    dragon->leave_area();
    }

    set_alarm(8.0, 0.0, &summon_message2(tp));
    dragon_is_summoned = 1;
    room = target_room;
    
    return 0;
}


