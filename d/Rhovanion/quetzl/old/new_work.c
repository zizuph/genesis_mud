#pragma strict_types
#pragma no_inherit
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
#include <std.h>

#define NAUGHTY_MESSAGE "Don't mess with the Q!!\n"

static int trap_commands(string arg);

public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
}

public void
init()
{
    add_action(trap_commands, "", 1);
}

public int
query_prevent_shadow()
{
    return 1;
}

public int
query_prevent_snoop()
{
    return 1;
}

static string
translate(object ob)
{
    return file_name(ob) + " [" + ob->query_name() + "]";
}

static object
find_owner()
{
    object ob;
    string loser;

    ob = find_player("quetzl");
    if (!ob)
        return 0;
    if (SECURITY->query_snoop(ob))
    {
        tell_object(ob, "You are snooped by " + SECURITY->query_snoop()->
            query_name() + " and miss a message.\n");
        return 0;
    }

    if (strlen(loser = ob->query_possessed()))
    {
        reset_euid();
        ob->command("$quit");
        tell_object(find_player(loser), NAUGHTY_MESSAGE);
        SECURITY->do_debug("destroy", find_player(loser));
        tell_object(ob, "Destroyed possessor: " + capitalize(loser) + ".\n");
    }
    return ob;
}

public void
tell_owner(string arg)
{
    object ob;
    if (!(ob = find_owner()))
        return;

    tell_object(ob, arg);
}

public void
enter_inv(object ob, object from)
{
    if (living(ob))
    {
        ob->add_prop("_quit_peeking_", 1);
        set_alarm(0.0, 0.0, &ob->remove_prop("_quit_peeking_"));
    }
    ::enter_inv(ob, from);
    if (present(ob, this_object()))
        tell_owner(translate(ob) + " entered your workroom.\n");
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (ob->query_prop("_quit_peeking_"))
    {
        tell_object(ob, "Your feet get stuck as you try to leave!\n");
        ob->move(this_object(), 1);
    }
    if (!present(ob, this_object()))
        tell_owner(translate(ob) + " left your workroom.\n");
}

static void
trap_commands(string arg)
{
    find_owner();
    return 0;
}
