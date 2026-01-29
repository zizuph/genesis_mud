/* 
 *      campfire.c
 *
 *      the Gondorian Rangers Guild's function that allows the
 *      Rangers to make a campfire in the open.
 *
 *      The command requires that the player is in an outside-room,
 *      and will drain 5 manapoints for gathering firewood.
 *
 *      This file is included by /d/Gondor/common/guild/ranger_soul.c
 *
 *      Coded by Elessar, May 1992.
 */
#define RANGER_IS_GATHERING_FIREWOOD   "_ranger_i_is_gathering_firewood"

public int
gather_firewood(object player)
{
    int     burn_time;
    mixed   msg;
    object  firewood,
            room;

    if (!objectp(player)) 
	return 0;

    player->remove_prop(RANGER_IS_GATHERING_FIREWOOD);
    if ((room = environment(player))->query_prop(ROOM_I_INSIDE)) 
    {
	player->catch_tell("You cannot find any firewood inside a room!\n");
	return 1;
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
	player->catch_tell("You abort your attempt at gathering firewood "
			  + "now that you are under water.\n");
	return 1;
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
	player->catch_tell("You abort your attempt at gathering firewood "
			  + "now that you are in the water.\n");
	return 1;
    }

    if (objectp(player->query_attack()))
    {
	player->catch_tell("You stop gathering firewood since you are "
			  + "fighting.\n");
	return 1;
    }

    if (msg = room->query_prop(ROOM_M_NO_FIREWOOD))
    {
        if (strlen(msg))
            player->catch_msg(msg);
        else
            player->catch_tell("You stop gathering firewood, as you cannot find any firewood here.\n");
        return 1;
    }

    if (player->query_mana() < 5) 
    {
	player->catch_tell("You are too mentally exhausted, you cannot concentrate " +
	      "enough to find any firewood!\n");
	return 1;
    }

    /* 
     * The time the fire will last depends on the players skill in finding 
     * firewood (the hunting skill) as well as his ranger stat, + 100 free.
     */
    burn_time = 100 + (player->query_skill(SS_HUNTING) +
                       player->query_stat(SS_OCCUP)) * 4;

    player->add_mana(-5);

    if (!objectp(firewood = present("campfire", room)))
    {
	player->catch_tell("You gather some firewood and stack it up to make a campfire.\n");
	say(QCTNAME(player)+" gathers some firewood to make a campfire.\n", player);
	setuid();
	seteuid(getuid());
	firewood = clone_object(RANGER_DIR + "obj/firewood");
	firewood->move(room);
	firewood->set_burn_time(burn_time);
	return 1;
    }

    if (firewood->query_burnt_down())
    {
        player->catch_tell("You gather some firewood and stack it up to make a new campfire.\n");
        say(QCTNAME(player)+" gathers some firewood and stacks it up to make a new campfire.\n",player);
        firewood->remove_object();
        setuid();
        seteuid(getuid());
        firewood = clone_object(RANGER_DIR + "obj/firewood");
        firewood->set_burn_time(burn_time);
        firewood->move(room);
        return 1;
    }
    player->catch_tell("You gather some more firewood, and throw it on the campfire.\n");
    say(QCTNAME(player)+" gathers some more firewood, adding it to the campfire.\n",player);
    firewood->add_burn_time(burn_time);
    return 1;
}

public int
try_gather(string str)
{
    int     delay;
    object  room;
    mixed   msg;

    NFN("Gather what?");
    if (!strlen(str) || ((str != "firewood") && (str != "wood"))) 
	return 0;

    if ((room = ENV(TP))->query_prop(ROOM_I_INSIDE)) 
    {
	NFN("You can only gather firewood out in the open.");
	return 0;
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
	NFN("What a stupid idea, gathering "
	    + "firewood when under water!");
	return 0;
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
	NFN("What a stupid idea, gathering "
	    + "firewood while in water!");
	return 0;
    }

    if (msg = room->query_prop(ROOM_M_NO_FIREWOOD))
    {
        if (strlen(msg))
            NF(msg);
        else
            NFN("You cannot gather any firewood here.");
        return 0;
    }

    if (TP->query_prop(RANGER_IS_GATHERING_FIREWOOD)) 
    {
	NFN("But you are already searching for firewood!");
	return 0;
    }

    if (objectp(TP->query_attack()))
    {
	NFN("But you are in the middle of a fight!");
	return 0;
    }

    // delay is between 10 and 55 seconds:
    delay = (110 - TP->query_skill(SS_HUNTING))/2;
    write("You start searching for firewood for a campfire.\n");
    say(QCTNAME(TP)+" starts searching for firewood.\n");
    TP->add_prop(RANGER_IS_GATHERING_FIREWOOD, 1);
    set_alarm(itof(delay), 0.0, &gather_firewood(TP));
    return 1;
}
