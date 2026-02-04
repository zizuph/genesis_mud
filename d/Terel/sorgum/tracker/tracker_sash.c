/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tracker_sash.c
 *
 * Tracker guild object
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/armour";

#include "tracker_defs.h"

#include <wa_types.h>
#include <ss_types.h>

int inited;

varargs void
initialize(object player, string str)
{
    object room;
    
    inited = 1;

    /*
     * Destroy the sash if it is held by a non-guild member.
     */
    
    if (player->query_guild_name_occ() != GUILD_NAME) {
	room = ETO;
	while (!room->query_prop(ROOM_I_IS))
	    room = ENV(room);
	player->catch_msg("The " + query_short() + " disintegrates!\n");
	set_alarm(0.0, 0.0, "remove_object");
	return;
    }

    player->add_cmdsoul(GUILD_SOUL);
    player->update_hooks();
}

/*
 * Function name: query_value
 * Description:   What's the value of this armour
 */
public int
query_value()
{
    return 0;
}

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_armour()
{
    set_name("sash");
    set_short("fancy shash");
    set_adj(({"black"}));
    set_long("Its a fancy sash.\n");

    set_af(TO);    
    set_ac(1);
    set_at(A_WAIST);

    FIX_EUID;
}


public int
query_tracker_rank()
{
    object player;

    player = ETO;

    if (MEMBER(player))
        return player->query_tracker_rank();
    else
        return 0;
}

/*
 * Function name: query_auto_load
 * Description:   Make this object autoloading
 * Returns:       The filename of this object and other data
 */

public string
query_auto_load()
{
    return MASTER + ":" + "#tr#" + query_tracker_rank() + "#";
}

mixed
wear(object ob)
{
    if (ob != TO)
        return -1;

    if (MEMBER(TP)) {
        write("You wear the " + query_short() + " around your waist.\n");
        say(QCTNAME(TP) + " wears " + LANG_ASHORT(TO) + ".\n");
        return 1;
    }
    else {
        return "You lose!\n";
    }
    
}

void
init_arg(string str)
{
    if (!inited)
        set_alarm(0.0, 0.0, "initialize", TP, str);
}

void
init()
{
    ::init();
    add_action("join", "join");
        
}

string
query_recover()
{
    return 0;
}

