#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;
inherit QEXITS;

object kender;

void
reset_kendermore_room()
{
    if (!kender)
    {
        kender = clone_object(KNPC + "std_kender");
        kender->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("Outside a sturdy house");
    set_long("@@long_descr");
    add_item(({"end", "dead end"}), "The street comes to an end here, or " + 
        "a house has been built in the middle.\n");
    add_item(({"house", "sturdy house"}), "It looks strong and " + 
        "well-built. You doubt a kender could have put such attention " + 
        "to its construction.\n");
    add_item(({"doors", "door", "window", "windows"}), "They are covered " + 
        "with iron bars, and would keep even the kender out.\n");
    add_item(({"bars", "iron bars"}), "They look very sturdy.\n");
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds beyond your view.\n");

    add_exit(KROOM + "street02", "north", 0);

    add_cmd_item("house", "enter", "@@enter_house");
    add_cmd_item("on door", "knock", "@@knock_door");

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

string
knock_door()
{
    write("You knock on the door, but get no response.\n");
    say(QCTNAME(TP) + " knocks on the barred door.\n");
    return "";
}


string
long_descr()
{
    return (tod_descr() + season_descr() + "You have come to a dead end, " + 
        "something not uncommon in Kendermore. " + street_descr() + " To " + 
        "your east a sturdy " + 
        "looking house has been built. To your " + find_exits() + " the " + 
        "street continues " + 
        "on its winding way.\n");
}

string
enter_house()
{
/*
    write("You open the door of the house and walk in.\n");
    say(QCTNAME(TP) + " opens the door to the house and walks in.\n");
    tell_room(KROOM + "small_house", "The door opens, and " + QTNAME(TP) +
        " enters the house.\n");
    TP->move_living("M", KROOM + "small_house", 1, 0);
    return "";
*/
    write("The doors and windows are barred from entry. Not even a " + 
        "determined kender could get in there.\n");
    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

