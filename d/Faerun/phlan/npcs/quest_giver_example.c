/*
 *  An example monster to show if-functionality with add_ask
 */

inherit "/std/monster";

#include <stdproperties.h>

// Set this to different values in yourself and ask the monster something
#define QUEST_PROP      "_live_i_quest_example_prop"
#define TP              this_player()

// Prototype, so we can use the function before we have defined it
string ask_func();

void
create_monster()
{
    setuid();
    seteuid(getuid());

    set_name(({ "monster", "quest-monster" }));
    set_adj(({ "ask", "quest" }));

    set_short("quest-monster");
    set_long(
        "This is a " + short() + ". It is designed to be asked about quest and "
        + "task.\n"
    );

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_default_answer("Did you want to ask me about a task?\n");
    add_ask(
        ({ "help", "task", "tour", "quest"}),
        "@@ask_func@@"
    );
}

// string means the function returns a string, and add_ask needs a string to
// print.
string
ask_func()
{
    int prop_val = TP->query_prop(QUEST_PROP);

    if (prop_val == 0)
    {
        // didn't have the prop or prop set to null
        TP->add_prop(QUEST_PROP, 1);
        return "Oh my, it seems I haven't given you a task!\n";
    }
    if (prop_val == 1)
    {
        TP->add_prop(QUEST_PROP, 2);
        return "Dear " + TP->query_nonmet_name() + ", you are on my first "
            + "task.\n";
    }
    if (prop_val == 2)
    {
        TP->add_prop(QUEST_PROP, 3);
        return "Dear " + TP->query_nonmet_name() + ", you are on my second "
            + "task.\n";
    }
    if (prop_val == 3)
    {
        TP->add_prop(QUEST_PROP, 0);
        return "Dear " + TP->query_nonmet_name() + ", you are on my third "
            + "task.\n";
    }

    // If we get to here, it means none of the above if statements matched,
    // or they would've returned. Thus we add a default return value since
    // our function is expected to return a string
    return "Dear " + TP->query_nonmet_name() + ", you are on some task that I "
        + "haven't heard about.\n";
}
