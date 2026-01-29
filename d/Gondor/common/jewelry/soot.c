/*
 * /d/Gondor/common/jewelry/soot.c
 *
 * A soot object that gives a player a sooty look after entering
 * the fireplace.
 *
 * Coded by Gwyneth, 09/06/02
 */
inherit "/std/object";

#include <macros.h>

#define SOOT_SUBLOC "_fireplace_soot_subloc_"

public void create_object();
public void remove_soot();
public string show_subloc(string subloc, object on, object for_obj);
public void get_sooty();
public int soot_wash(string str);
public void init();

public void
create_object()
{
    set_name("soot");
    set_short("soot");
    set_long("It's a piece of soot, but you shouldn't be able to see it. " +
        "Please make a bug report in the Gondor domain.\n");

    set_no_show();

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_GET, 1);

    set_alarm(1.0, 0.0, &get_sooty());
}

public void
remove_soot()
{
    remove_object();
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == SOOT_SUBLOC)
    {
        if (for_obj != on)
        {
            return (capitalize(on->query_pronoun()) + " is covered " +
                "in soot.\n");
        }
        else
        {
            return ("You are covered in soot.\n");
        }
    }
}

public void
get_sooty()
{
    object ob = environment();

    if (!living(ob))
    {
        remove_object();
        return;
    }
    else
    {
        ob->add_subloc(SOOT_SUBLOC, this_object());
    }

    set_alarm(3600.0, 0.0, &remove_soot());
}

public int
soot_wash(string str)
{
    if (!environment(this_player())->query_prop(OBJ_I_CONTAIN_WATER))
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Wash what?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, ({}), " [off] 'soot' / 'myself' [off] "))
    {
        notify_fail("Wash what?\n");
        return 0;
    }

    write("You wash the soot off of yourself. Now you're all clean!\n");
    say(QCTNAME(this_player()) + " washes the soot off of " +
        this_player()->query_possessive() + "self.\n");

    set_alarm(1.0, 0.0, &remove_soot());
    return 1;
}

public void
init()
{
    ::init();

    add_action(soot_wash, "wash");
}
