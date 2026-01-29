inherit "/std/room";

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <config.h>

#define MSG_FREQ itof((10 + random(10)))

static object eagle;
static int fly_alarm, msg_alarm;

public int query_eagle_free();

public string
fly_msg()
{
    if (!query_eagle_free())
    {
        return "";
    }

    return "To take off, simply \"fly to <destination>\".";
}

void
create_room()
{
    set_short("Mounted on the giant eagle");
    set_long("   You are mounted on the back of a giant eagle.  " +
        "@@fly_msg@@\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop("_room_m_no_earthmeld", 1);
    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}

public void
arrive(string dest)
{
    object *all;
    int i;

    remove_alarm(msg_alarm);

    fly_alarm = 0;
    eagle->move(dest, 1);

    tell_room(this_object(), "The giant eagle lands, and you dismount.\n");

    all = all_inventory(this_object());
    for (i = 0; i < sizeof(all); i++)
    {
        if (!living(all[i]))
	{
            continue;
	}

        if (interactive(all[i]) || all[i]->query_npc())
	{
            all[i]->move_living("off the giant eagle", dest, 1);
            continue;
	}

        all[i]->move_living("M", OWN_STATUE, 1);
        OWN_STATUE->set_revive_dest(all[i], dest);
    }
}

public void
give_flight_messages()
{
    string msg = ({
        "A small bird passes below.\n",
        "The giant eagle dips down then levels out.\n",
        "The giant eagle flaps its wings heavily, flying ever faster.\n",
        "The giant eagle adjusts its coarse, rolling slightly to the side " +
        "and making you feel as if you might topple off.\n", })[random(4)];

    tell_room(this_object(), msg);

    msg_alarm = set_alarm(MSG_FREQ, 0.0, give_flight_messages);
}

public int
fly(string str)
{
    string dest, name;

    if (!strlen(str) || !sscanf(str, "to %s", str))
    {
        notify_fail(capitalize(query_verb()) + " to where?\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    str = lower_case(str);

    if (!(dest = EAGLE_MANAGER->query_open_destination(str)))
    {
        notify_fail(capitalize(str) + " is not a valid destination.\n");
        return 0;
    }

    if (dest == file_name(environment(eagle)))
    {
        write("You are already there!\n");
        return 1;
    }

    if (!query_eagle_free())
    {
        write("You are already en-route to a destination.\n");
        return 1;
    }

    if (!this_player()->query_kot_member() && !this_player()->query_wiz_level())
    {
        write("The giant eagle refuses to obey.\n");
        return 1;
    }

    name = 
        EAGLE_MANAGER->query_destination_name(file_name(environment(eagle)));

    fly_alarm = set_alarm(EAGLE_MANAGER->query_destination_time(name, str),
        0.0, &arrive(dest));
    msg_alarm = set_alarm(MSG_FREQ, 0.0, give_flight_messages);

    eagle->move(TEMP_EAGLE_ROOM, 1);
    
    tell_room(this_object(), "The eagle takes off!\n");

    return 1;
}

public void
set_eagle(object ob)
{
    eagle = ob;
}

public void
drop(object ob)
{
    object *all;
    int i;

    if (environment(ob) != this_object())
    {
        return;
    }

    ob->move(environment(eagle), 1);

    all = all_inventory(this_object());
    for (i = 0; i < sizeof(all); i++)
    {
        if (!interactive(all[i]) || !CAN_SEE_IN_ROOM(all[i]) ||
            !CAN_SEE(all[i], ob))
        {
            continue;
        }

        all[i]->catch_tell("The " + ob->short(all[i]) + 
            " falls to the ground.\n");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob))
    {
        if (!ob->query_no_show())
        {
            set_alarm(0.0, 0.0, &drop(ob));
        }
    }
    else
    {
        eagle->stop_leave();
    }
}

public int
query_eagle_free()
{
    return !fly_alarm;
}

public int
query_eagle_occupied()
{
    return !!sizeof(FILTER_PLAYERS(all_inventory(this_object())));
}

public int
dismount(string str)
{
    if (strlen(str) && (str != "eagle") && (str != "giant eagle"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (file_name(environment(eagle)) == TEMP_EAGLE_ROOM)
    {
        write("Dismounting now would be suicide!\n");
        return 1;
    }

    say(({ METNAME + " dismounts the giant eagle.\n",
        NONMETNAME + " dismounts the giant eagle.\n",
        "", }));
    this_player()->move_living("M", environment(eagle), 1);
    say(({ METNAME + " dismounts the giant eagle.\n",
        NONMETNAME + " dismounts the giant eagle.\n",
        "", }));

    return 1;
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!query_eagle_occupied() && query_eagle_free())
    {
        eagle->start_leave();
    }
}

public int
prevent_leave(object ob)
{
    int i;

    /* Don't allow linkdead players to leave */
    if (living(ob) && !ob->query_npc() && !interactive(ob))
    {
        while ((ob = calling_object(-i++)) && (file_name(ob) != OWN_STATUE));
        return !!ob;
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(fly, "fly");
    add_action(dismount, "dismount");
}
