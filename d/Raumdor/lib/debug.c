#pragma strict_types
#pragma no_clone

#include "defs.h"

public void
dump(string *players, mixed var)
{
    object tmp,
           player,
           ob = previous_object();

    foreach (string str: players)
    {
        if (!str || !(player = FP(str)))
            continue;
        tmp = this_player();
        set_this_player(player);
        write("<" + ctime(time()) + " ");
        if (ob)
            write(file_name(ob) + " ");
        write("DUMP:\n");
        find_object("/cmd/std/tracer_tool")->print_value(var);
        write("END DUMP>\n");
        set_this_player(tmp);
    }
}

public string *
stack()
{
    string f, *stack = ({});
    int i = 0;
    while(f = calling_function(--i))
        stack += ({f});

    return stack; 
}

public mixed
fix_this_player(function f)
{
    mixed result;
    object tp = this_player();
    result = f();
    set_this_player(tp);
    return result;
}
