#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

private static int level_filled = -1;

public void
set_level_filled(int level)
{
    level_filled = level;
}

public int
query_level_filled()
{
    return level_filled;
}

public string 
short_desc()
{
    switch(level_filled)
    {
        case 0:
            return "freshly dug";
        break;
        case 1:
            return "half filled";
        break;
        case 2:
            return "almost filled";
        break;
        default:
            return "error";
        break;
    }
}

public string
long_desc()
{
    switch(level_filled)
    {
        case 0:
            return "A freshly dug hole in the sand. Someone just " +
                "finished digging this hole. The waves have just " +
                "started to fill it up with sand washed up from " +
                "the sea.\n";
        break;
        case 1:
            return "A half filled hole in the sand. The waves have " +
                "filled this hole with sand half way.\n";
        break;
        case 2:
            return "A hole almost complete filled up by sand. " +
                "The waves have been bringing in sand from the " +
                "sea to fill this hole. It is almost completely filled.\n";
        break;
        default:
            return "error\n";
        break;
    }
}

public void
decay_msg()
{
    string decay_message = "A wave comes rushing in from the " +
        "sea and covers the sand. Sand from the sea carried by " +
        "the wave fills the hole.\n";
    object room = environment(this_object());
    int decay_alarm;

    level_filled++;
    tell_room(room, decay_message);

    if(level_filled < 2)
    { 
      decay_alarm = set_alarm(35.0, 0.0, &decay_msg());
      tell_room(room, "\n");
    } else {
        tell_room(room, "The sand completely " +
            "fills the hole.\n");
        remove_object();
    }
}

public void
create_object()
{
    set_name("hole");
    set_pname("holes");
    set_short("@@short_desc@@ hole in the sand");
    set_pshort("@@short_desc@@ holes in the sand");
    set_long("@@long_desc@@");
    add_prop(OBJ_M_NO_GET, "What kind of silly notion is that? " +
        "There is no way you can get a hole from the sand.\n");
    decay_msg();
}
