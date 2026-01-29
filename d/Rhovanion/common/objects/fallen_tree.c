inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

static int state;

string longdes()
{
    string text;
    text = "This tree was chopped down, and lays smashed and " +
           "dead here on the ground.";

    switch(state)
    {
        case 0: return text += "\n";
        case 1:
        case 2:
        case 3: return text + " It looks slightly rotted.\n";
        case 4:
        case 5:
        case 6: return text + " It is rotting away.\n";
        case 7:
        case 8: 
        case 9: return text + " It is extremely rotted, and will " +
                              "probably disintegrate at any moment.\n";
        default: return text + "\n";
    }
}

create_object()
{
    set_name("tree");
    set_adj("fallen");
    set_long("@@longdes@@");
    add_prop(OBJ_I_NO_GET, 1);
    set_alarm(20.0, 20.0, "decay_tree");
}

decay_tree()
{
    tell_room(environment(this_object()), "The fallen tree rots " +
        "where it lays.\n");
    state++;
    if (state>9)
    {
        tell_room(environment(this_object()), "The tree rots " +
            "entirely away.\n");
        remove_object();
    }
}
