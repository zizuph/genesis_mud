#pragma strict_types

inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

void
create_object() 
{
    seteuid(getuid());
    set_name("_tree_climbers_curse_of_anti_levitation");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

void
init()
{
    ::init();
    add_action("stop_directions", "", 1);
}

int
no_walk()
{
    write("You must climb down from the tree first.\n");
    return 1;
}

public int
stop_directions(string str)
{
    string verb;
    string *allowed;

    allowed =   ({  "north",    "n",
                    "south",    "s",
                    "west",     "w",
                    "east",     "e",
                    "northwest","nw",
                    "northeast","ne",
                    "southwest","sw",
                    "southeast","se",
                    "up",       "u",
                    "down",     "d",
                    "out",      "in",
                });
    
    
    verb = query_verb();
    if (member_array(verb, allowed) != -1)
        return no_walk();
    else
        return 0;
    
    return 1;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
        remove_object();
        return;
    }

    if(!living(to))
    {
        remove_object();
        return;
    }
}
