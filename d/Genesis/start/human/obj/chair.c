#pragma save_binary

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

static object sitter;

public void
create_object()
{
    set_name("chair");
    set_adj("comfortable");
    add_adj("looking");
    set_long("@@my_long");
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_M_NO_GET, "The armchair is too heavy to lift.\n");
}

public void
init()
{
    ::init();
    add_action("sit_down", "sit");
    add_action("stand_up", "stand");
    add_action("stand_up", "rise");
}

public int
sit_down(string arg)
{
    object *ob;
    if (sitter)
    {
        notify_fail("The chair is already occupied by " +
            sitter->query_the_name(this_player()) + ".\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Sit on what?\n");
        return 0;
    }
    if (sscanf(arg, "on %s", arg) != 1)
    {
        notify_fail("Sit how?\n");
        return 0;
    }

    ob = FIND_STR_IN_OBJECT(arg, environment(this_player()));
    if (!sizeof(ob) || ob[0] != this_object())
    {
        notify_fail("Sit on what?\n");
        return 0;
    }

    if (this_player()->query_prop("_live_i_sit"))
    {
        write("You are already sitting down. Enjoy it.\n");
        return 1;
    }

    write("You sit down in the " + short() + ".\n");
    say(QCTNAME(this_player()) + " sits on the " + short() + ".\n");
    sitter = this_player();
    sitter->add_prop(LIVE_S_EXTRA_SHORT, " (sitting on a chair)");
    sitter->add_prop("_live_i_sit", this_object());
    return 1;
}

public int
stand_up(string arg)
{
    if (sitter != this_player())
    {
        notify_fail("But you are not sitting down!\n");
        return 0;
    }
    if (strlen(arg) && (arg != "from chair") && (arg != "up"))
    {
        notify_fail("How did you want to stand?\n");
        return 0;
    }
    sitter = 0;
    write("You stand up from the chair.\n");
    say(QCTNAME(this_player()) + " rises from the " + short() + ".\n");
    this_player()->remove_prop("_live_i_sit");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

public string
my_long()
{
    if (this_player() == sitter)
        return "This is the chair you are sitting in.\n";
    if (sitter)
        return "It looks comfortable, but " + sitter->query_the_name(this_player())
            + " is sitting on it.\n";
            "on it.\n";
    return "This chair looks comfortable, perhaps you could sit on it.\n";
}

public object
query_sitter()
{
    return sitter;
}