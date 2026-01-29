#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;
inherit QEXITS;

object this_mouse;
object kender;

void
reset_kendermore_room()
{
    if (!this_mouse)
    {
        this_mouse = clone_object(KNPC + "mouse");
        this_mouse->move(TO);
    }

    if(!kender)
    {
        kender = clone_object(KNPC + "std_kender");
        kender->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A three-way fork");
    set_long("@@long_descr");
    add_item(({"house", "houses"}), "Even the houses here have a " + 
        "carefree feeling. " +
        "There doesn't seem to be any way in from here.\n"); 
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds " + 
        "beyond your view.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");

    add_cmd_item("house", "enter", "@@enter_house");

    add_exit(KROOM + "street09", "south", 0);
    add_exit(KROOM + "street11", "west", 0);
    add_exit(KROOM + "street17", "northeast", "@@loose_stone");

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " + 
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " + 
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
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
    return (tod_descr() + season_descr() + "Houses stand on both sides " + 
        "of you. " + street_descr() + " The road continues on its " + 
        "winding way to the " + find_exits() + ". Numerous signs point " + 
        "in all directions, but they tend to contradict each other and " + 
        "point in directions where there are no exits.\n");
}

string
enter_house()
{
    write("You look for a way into the house, but find none.\n");
    say(QCTNAME(TP) + " searches for a way into the house, but finds " + 
        "none.\n");
    return "";
}

int
loose_stone()
{
    write("You trip over a loose stone as you walk to the northeast.\n");
    return 0;
}

        
