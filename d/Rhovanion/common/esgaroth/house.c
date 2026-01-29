inherit "/d/Rhovanion/common/esgaroth/esroom";

#define TO this_object()
#include <stdproperties.h>

create_esgaroth() {}
create_exits() {}

reset_house()
{
    if (!present("_man_", TO))
        add_a_monster("townsman");
    if (!present("_woman_", TO))
        add_a_monster("townswoman");
    if (!present("_child_", TO))
        add_a_monster("townschild");
}

nomask void
reset_room()
{
    reset_house();
}

string longdesc()
{
    string text;
    text = "You are in one of the modest houses of Esgaroth.  ";
    switch(ctime())
    {
        case "evening": case "night": 
            text += "Moonlight streams into the house through the window, " +
                "but fails to illuminate the house.  ";
            break;
        case "morning": case "early morning": case "noon" :case "afternoon":
            text += "The sun shines brightly through the window.  ";
            break;
    }
    return text + query_extras();
}

create_room()
{
    set_short("A house in Esgaroth");
    set_long("@@longdesc@@");
    add_prop(ROOM_I_INSIDE, 1);
    create_exits();
    reset_room();
}
