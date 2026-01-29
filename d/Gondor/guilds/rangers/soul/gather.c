/*
 * /d/Gondor/guilds/rangers/soul/gather.c
 *
 * Included in the soul. Ability for a Ranger to gather firewood in
 * an outside room. It drains a small amount of mana.
 *
 * Originally coded by Elessar
 *
 * Modification log:
 * 13 April 2001 Gwyneth: General recode and move.
 */

#define RANGER_IS_GATHERING_FIREWOOD   "_ranger_i_is_gathering_firewood"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../rangers.h"     /* For RANGERS_OBJ define */
#include "/d/Gondor/defs.h" /* For ROOM_M_NO_FIREWOOD define */

public void gather_firewood(object player);

/* Function name: gather
 * Description  : 
 * Arguments    : string str - the argument
 * Returns      : 1 on success, 0 on failure
 */
public int
gather(string str)
{
    int delay;
    object room;
    mixed msg;
 
    if (!strlen(str) || ((str != "firewood") && (str != "wood")))
    {
        notify_fail("Gather what?\n");
        return 0;
    }
 
    if ((room = environment(this_player()))->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You can only gather firewood out in the open.\n");
        return 0;
    }
 
    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
      room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
        notify_fail("Any firewood you could find here would be too wet " +
            "to be of any use.\n");
        return 0;
    }
 
    if (msg = room->query_prop(ROOM_M_NO_FIREWOOD))
    {
        if (strlen(msg))
            notify_fail(msg + "\n");
        else
            notify_fail("You cannot gather any firewood here.\n");
        return 0;
    }
 
    if (this_player()->query_prop(RANGER_IS_GATHERING_FIREWOOD))
    {
        notify_fail("But you are already searching for firewood!\n");
        return 0;
    }
 
    if (objectp(this_player()->query_attack()))
    {
        notify_fail("You are in the middle of a fight!");
        return 0;
    }
 
    write("You start searching for firewood for a campfire.\n");
    say(QCTNAME(this_player()) + " starts searching for firewood.\n");

    /* delay is between 10 and 55 seconds */
    delay = (110 - this_player()->query_skill(SS_HUNTING)) / 2;
    this_player()->add_prop(RANGER_IS_GATHERING_FIREWOOD, 1);
    set_alarm(itof(delay), 0.0, &gather_firewood(this_player()));
    return 1;
}

/* Function name: gather_firewood
 * Description  : Called by the alarm in gather to actually gather the
 *                firewood.
 * Arguments    : object player - the gatherer
 */
public void 
gather_firewood(object player)
{
    int burn_time;
    mixed  msg;
    object firewood,
           room;
 
    if (!objectp(player))
        return;
 
    set_this_player(player);
    player->remove_prop(RANGER_IS_GATHERING_FIREWOOD);
    room = environment(player);
    if (room->query_prop(ROOM_I_INSIDE))
    {
        write("You cannot find any firewood inside a room!\n");
        return;
    }
 
    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
      room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
        write("You abort your attempt at gathering firewood now that you " +
            "are under water.\n");
        return;
    }
 
    if (objectp(player->query_attack()))
    {
        write("You stop gathering firewood since you are fighting.\n");
        return;
    }

    msg = room->query_prop(ROOM_M_NO_FIREWOOD);
    if (msg)
    {
        if (strlen(msg))
            write(msg);
        else
            write("You stop gathering firewood, as you cannot find any " +
                "firewood here.\n");
        return;
    }
 
    if (player->query_mana() < 5)
    {
        write("You are too mentally exhausted. You cannot " +
            "concentrate enough to find any firewood!\n");
        return;
    }
 
    /*
     * The time the fire will last depends on the players skill in finding
     * firewood (the hunting skill) as well as his ranger stat, + 100 free.
     */
    burn_time = 100 + (player->query_skill(SS_HUNTING) +
                       player->query_stat(SS_OCCUP)) * 4;
 
    player->add_mana(-5);
 
    firewood = present("campfire", room);
    if (!objectp(firewood))
    {
        write("You gather some firewood and stack it up to make a campfire.\n");
        say(QCTNAME(player) + " gathers some firewood to make a campfire.\n", 
            player);
        setuid();
        seteuid(getuid());
        firewood = clone_object(RANGERS_DIR + "obj/firewood");
        firewood->move(room);
        firewood->set_burn_time(burn_time);
        if (present("taskmaster", ENV(player)) &&
          player->query_prop(RANGER_I_TASK) == FIRE_TASK)
            player->add_prop(RANGER_O_FIRE_TASK, firewood);
        return;
    }
 
    if (firewood->query_burnt_down())
    {
        write("You gather some firewood and stack it up to make a " +
            "new campfire.\n");
        say(QCTNAME(player) + " gathers some firewood and stacks it up " +
            "to make a new campfire.\n");
        firewood->remove_object();
        setuid();
        seteuid(getuid());
        firewood = clone_object(RANGERS_DIR + "obj/firewood");
        firewood->set_burn_time(burn_time);
        firewood->move(room);
        return;
    }

    write("You gather some more firewood, and throw it on the campfire.\n");
    say(QCTNAME(player) + " gathers some more firewood, adding it to " +
        "the campfire.\n");
    firewood->add_burn_time(burn_time);
    return;
}
