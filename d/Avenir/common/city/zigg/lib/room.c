/*
 *  file name:   std_room.c
 *  creator:     Lucius
 *  last update: Lilith Nov 2021  Updated room props and notes.
 *  purpose:    Standard inherit for ziggurat rooms.
 *  note(s):    
 *  bug(s):
 *  to-do:
 */
#pragma no_clone
#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#define D(x) find_player("lilith")->catch_tell(x + "\n")

public void
zig_room(void)
{
    /* Individual room code goes here. */
}

static void
create_room(void)
{
    /* Default room tell delay. */
    set_tell_time(300);

    /* All of sybarus is inside. */
    add_prop(ROOM_I_INSIDE, 1);
	
	/* There are some things the Gods of Sybarus don't abide on their turf */
    add_prop(ROOM_M_NO_ATTACK, "You sense a powerful will countering your "+
        "own, blocking your attack.\n");
    add_prop(ROOM_I_HIDE, -1); 
    add_prop(ROOM_M_NO_STEAL, "It is the Gods' Will that you cannot do that here.\n");
    add_prop(ROOM_M_NO_SCRY,  "A will far more powerful than your own prevents this.\n");	
	
    /* No magic props. */
    add_prop(ROOM_M_NO_MAGIC, "Only the gifts bestowed by the Idrys have power "+
    	"here.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "You sense a powerful will countering your "+
    	"own, blocking your attack.\n");

    /* Just want NO teleport TO--however, you'd have to 
	 * remove the NO_MAGIC from specific rooms you want 
	 * it to be ok in. Since most teleportation is a 
	 * magical spell.
	 */
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);    

    /* Our individual room code. */
    zig_room();

    /* Convenience call. */
    set_alarm(0.1, 0.0, &reset_room());
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
}

public string
see_nearby(void)
{
    object room, *obs = ({});
    int idx, size = sizeof(room_exits);

    for(idx = 0; idx < size; idx += 3)
    {
	int ix, sz = sizeof(non_obvious_exits);

	if (IN_ARRAY(room_exits[idx + 1], ({"in","out","up","down"})))
	    continue;

	ix = (idx / 3);
	/* Check if exit is non-obvious. */
	if (sz > ix)
	{
	    if (non_obvious_exits[ix])
		continue;
	}

	catch(room_exits[idx]->teleledningsanka());
	if (objectp(room = find_object(room_exits[idx])))
	    obs += all_inventory(room);
    }

    if (!sizeof(obs = filter(obs, living)))
	return "";

    return " In the surroundings nearby, you see "+
	COMPOSITE_LIVE(obs) +".";
}

/*
 * Mask this to print a message for a non-exit view.
 */
static string
view_static(string str)
{
    return "You find no "+ str +".\n";
}

/*
 * Dynamic direction views.
 */
static string
view_nearby(string str)
{
    mixed room;
    object *obs;
    int idx = member_array(str, room_exits);

    if (!strlen(str))
	return "Error!";

    /* No exit in that direction. */
    if (idx == -1)
	return view_static(str);

    room = room_exits[idx - 1];
    catch(room->teleledningsanka());

    /* Did the room load? */
    if (!objectp(room = find_object(room)))
    {
	return "You have difficulty making out what lay to "+
	"the "+ str +".\n";
    }

    obs = filter(all_inventory(room), living);
    str = "Off to the "+ str +" is: "+ capitalize(room->short()) +".\n";

    if (sizeof(obs))
	str += "Roaming around that area is "+ COMPOSITE_LIVE(obs) +".\n";
    else
	str += "It seems to be devoid of traffic for the moment.\n";

    return str;
}

/*
 * Auto adds directional view (ex. "exa north, exa south, etc")
 */
static void
add_view_items(void)
{
    int idx, size = sizeof(room_exits);

    for(idx = 1; idx < size; idx += 3)
    {
	int ix, sz = sizeof(non_obvious_exits);

	if (IN_ARRAY(room_exits[idx], ({"in","out","up","down"})))
	    continue;

	ix = ((idx - 1) / 3);
	/* Check if exit is non-obvious. */
	if (sz > ix)
	{
	    if (non_obvious_exits[ix])
		continue;
	}

	add_item(({ room_exits[idx] }),
	    &view_nearby(room_exits[idx]));
    }
}

/*
 * These should all be called after you add exits.
 */

/*
 * Common things amongst all ziggurat rooms.
 */
static void
add_zigg(void)
{
    add_view_items();
}
