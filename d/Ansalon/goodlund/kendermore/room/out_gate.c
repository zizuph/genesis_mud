#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_OUT;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("Just outside the walls of Kendermore");
    set_long("@@long_descr");
    add_item(({"large gap", "gap"}), "You could enter the gap in the wall " + 
        "to get to the city of Kendermore.\n");
    add_item(({"city", "kendermore"}), "You can glimpse the city of " + 
        "Kendermore through the gap in the wall. It is the home of many " + 
        "kender when they are not wandering Krynn.\n");
    add_item(({"wall", "walls"}), "The tops of the walls contain " + 
        "holes where construction was paused. It doesn't look like " + 
        "anyone is planning on finishing it, though. Where the gates to " + 
        "the city should be, lies a large gap. It looks like the only " + 
        "obvious way in or out of the city on the west side.\n");
    add_item("forest", "It lies a short distance to the west, and looks " + 
        "like interesting exploring.\n");
    add_item(({"road", "stone road"}), "It winds west into a dark forest.\n");

    add_exit(KROOM + "trail1", "west", 0);

    add_cmd_item("gap", "enter", "@@enter_gap");
    set_tell_time(100);
    add_tell("You hear shouts and yells as a bunch of merchants try to " + 
        "fit their wagon through the gap.\n");
    add_tell("A cat bounds across your path.\n");
    add_tell("A high voice rings a biting taunt.\nA kender runs by " + 
        "followed closely by a flushed looking dwarf.\n");
    add_tell("The wind brings the sweet melody of a songbird to your ears.\n");
    add_tell("A stone falls down from above, followed by a loud 'Oops!'\n");
    add_tell("A small bug skitters under a bush.\n");
 

    reset_kendermore_room();
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
 
string
long_descr()
{
    return (tod_descr() + season_descr() + "You stand just outside the " + 
        "city of Kendermore. A tall stone wall towers to your east. " +
        " A stone road starts here and heads west, winding " + 
        "beyond your view into a forest.\n");  
}

string
enter_gap()
{
    write("You walk through the gap in the wall, entering Kendermore.\n");
    say(QCTNAME(TP) + " walks through the gap in the wall, entering " + 
        "Kendermore.\n");
    tell_room(KROOM + "in_gate", QCTNAME(TP) + " arrives from the gap " + 
        "in the wall.\n");
    TP->move_living("M", KROOM + "in_gate", 1, 0);
    return "";
}

