inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>

string
query_fork_colour()
{
    return "brass";
}
    
int
query_chance_to_break()
{
    // This is the base fork code, this value should be altered
    // in the file this is inherited from.

    return 100;
}

void
create_fork()
{
}

nomask void
create_object()
{
    string colour = query_fork_colour();

    set_name("fork");
    add_name("minstrel_tuning_fork");
    set_adj(({ colour, "tuning" }));

    set_long("This " + colour + " tuning fork is a hallmark of the " +
         "Minstrel. When struck, it produces a clear tone to which the " +
         "Minstrel's instrument may be tuned.\n");

    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);

    create_fork();
}

void
break_fork(int silent)
{
    if (!silent)
    {
        tell_room(environment(), "The " + short() + " breaks!\n");
    }

    set_long("This " + query_fork_colour() + " tuning fork is a hallmark of the " +
        "Minstrel. Unfortunately, it is broken and useless; though, it might still " +
        "have some value.\n");

    add_adj("broken");

    add_prop(OBJ_I_VALUE, query_prop(OBJ_I_VALUE) / 10);
    add_prop(OBJ_I_BROKEN, 1);
}

int
strike(string str)
{
    mixed *oblist;

    if (!strlen(str) ||
        !parse_command(str, all_inventory(this_player()), "[the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail("Strike what?\n");
        return 0;
    }

    if (!oblist[0]->strike_minstrel_fork())
    {
        notify_fail(capitalize(LANG_THESHORT(oblist[0])) + " won't produce a " +
            "clear enough tone for tuning.\n");
        return 0;
    }

    return 1;
}

int
strike_minstrel_fork()
{
    if (query_prop(OBJ_I_BROKEN))
    {
        write("The " + short() + " produces only a muffled 'clank'.\n");
        say(QCTNAME(this_player())+ " strikes " + this_player()->query_possessive() +
	    " " + short() + ", which produces only a muffled 'clank'.\n");
        return 1;
    }

    write("You strike the tuning fork, which rings forth with a beautifully pure, " +
        "mellow tone.\n");
    say(QCTNAME(this_player()) + " strikes " + this_player()->query_possessive() +
        " " + short() + ", which issues forth with a bright, clear tone.\n");

    if (random(100) < query_chance_to_break())
    {
        break_fork(0);
    }

    return 1;
}

string
query_auto_load()
{
    if (!query_prop(OBJ_I_BROKEN))
    {
        return MASTER + ":";
    }

    return 0;
}

int
query_minstrel_fork()
{
    return 1;
}
