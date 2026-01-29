inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("leaf_master");
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 15);
}

public int
leaf_win(string str)
{
    notify_fail("Declare victory?\n");
    if (!strlen(str))
        return 0;

    if (environment(this_object()) != this_player())
    {
        notify_fail("You must have the leaf first.\n");
        return 0;
    }
    if (lower_case(str) == "victory")
    {
        find_living("stern")->catch_tell(this_player()->query_name() +
            " thinks " + this_player()->query_pronoun() + " won the " +
            "leaf contest!\n");
        find_living("gwyneth")->catch_tell(this_player()->query_name() +
            " thinks " + this_player()->query_pronoun() + " won the " +
            "leaf contest!\n");
        write("You raise your hands and declare victory..." +
            "Have you won? Only time will tell.\n");
        say(QCTNAME(this_player()) + " raises " + 
            this_player()->query_possessive() + " hands and declares " +
            "victory.\n");
        return 1;
    }
    return 0;
}

public void
init()
{
    ::init();

    add_action(leaf_win, "declare");
}

