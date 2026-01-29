
#pragma save_binary
#pragma strict_types

inherit "/std/message";

#include "/d/Khalakhor/sys/basic.h"
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <macros.h>

public varargs void
hook_message_destroyed(object room, object player)
{
    tell_room(room, "The inkblot fades from view.\n");
}

public void
create_message()
{
    set_name("inkblot all over");
    set_pname("inkblots all over");
    set_short("inkblot all over");
    set_pshort("inkblots all over");

    add_name("inkblot");

    set_long("An interpretable inkblot -- delivered by pendragon.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);

    add_prop(OBJ_I_NO_DROP,
       "You cannot just drop an inkblot -- you really must <scrub> it.\n");
}

public string
message_description()
{
    return "The message within the inkblot can be interpreted as:\n" 
         + EXPAND_LINE("~", 60) +
        "\n\n"+ query_message() + "\n"+ EXPAND_LINE("~", 60) + "\n\n";
}

int
scrub_it(string str)
{
    if(!strlen(str))
    {
        write("Scrub what?\n");
        return 0;
    }
    if((str == "inkblot") || (str == "interpretable inkblot"))
    {
        remove_object();
        write("You scrub an inkblot from your body.\n");
        say(QCTNAME(this_player()) + " scrubs off some ink.\n");
        return 1;
    }
}

int
interpret_it(string str)
{
    if(!strlen(str))
    {
        write("Interpret what?\n");
        return 0;
    }
    if((str == "inkblot") || (str == "interpretable inkblot"))
    {
        write(message_description());
        return 1;
    }
}

public void
init()
{
    ::init();
    add_action(interpret_it, "interpret");
    add_action(scrub_it, "scrub");
}


