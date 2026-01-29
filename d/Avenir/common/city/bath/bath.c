#pragma strict_types
/*
 * ~/bath.c
 *
 * Main inheritable for the Bath
 *
 * Revisions:
 *   Lucius, May 2016: Added no_scry property to the Baths.
 *   Lucius, Aug 2016: Updates for baths recode.
 *   Lilith, Sep 2021: 5 yo bug from the recode fixed.
 *                     load_other_door was not being called when the doors were 
 *                     created, so the auto locking mechanism was locking the inside 
 *                     door only, leaving the outside door open and allowing others
 *                     to just walk in, thus compromising players' privacy.
 *
 */
#include "bath.h"
#include "/d/Avenir/include/macros.h"

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

/* Inherit the standard room object */
inherit "/std/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/*
 * Function name: create_bath_room
 * Description:   This function should be called to create rooms.
 */
static void
create_bath_room(void)		{ }

public nomask void
create_room(void)
{
    set_tell_time(300);

    add_tell("A tendril of warm, moist air carries to you the scent "+
        "of herbs.\n");
    add_tell("Droplets of water condense on your eyelashes, and you "+
        "breathe deeply of the warm, humid air.\n");
    add_tell("Serenity emanates from the very stones of this place.\n");
    add_tell("You find the sound of trickling water very restful.\n");

    IN_IN;

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO,  1);
    add_prop(ROOM_M_NO_SCRY, 1);

    remove_prop(ROOM_I_ALLOW_STEED);

    create_bath_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
        start_room_tells();
}

public void
hook_smelled(string str)
{
    write("The air is pungent with the odour of many herbs.\n");
}

public string
bath_view(void)
{
    int size;
    object *live = ({ });
    object rm = find_object(BATHRM + "pub_bath");

    if (objectp(rm))
	live += all_inventory(rm);

    if (!sizeof(live)) 
	return "";

    live = FILTER_LIVE(live);
    live = FILTER_CAN_SEE(live, this_player());

    if (!(size = sizeof(live)))
	return "";

    return " In the public pool before you " +
	(size > 1 ? "are " : "is ") +
	COMPOSITE_LIVE(live) + ".";
}

/*
 * Used by the steps to replicate messages when using exit.
 */
public void
enter_desc(void)
{
    write("As you walk down the steps you wade into the pool.\n");
    say(QCTNAME(this_player()) + " enters the public pool.\n");
}

public int
enter_pool(string str) 
{
    string vb = capitalize(query_verb());

    if (!strlen(str) || !parse_command(str, ({}),
	    " [into] [the] 'bath' / 'pool'"))
    {
	return notify_fail(vb +" what? "+ vb +" into pool?\n");      
    }

    enter_desc();
    set_dircmd("pool");

    this_player()->move_living("M", BATHRM + "pub_bath", 1, 0);
    tell_room(BATHRM + "pub_bath", QCTNAME(this_player()) +
	" enters the pool.\n", this_player());

    return 1;
}

public static object bath_door;

public void
bath_door(string room, string other, string dir)
{
    bath_door = clone_object(BATHOB +"priv_door");
    bath_door->config_door(room, other, dir);
    bath_door->move(this_object());
    bath_door->load_other_door(); // This should fix the unlocked 
	                              // and or open outer door problem
}

public object
query_bath_door(void)	{ return bath_door; }

