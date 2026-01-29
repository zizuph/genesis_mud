#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;
inherit QEXITS;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("In front of a noisy inn");
    set_long("@@long_descr");
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds beyond your view.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");
    add_item(({"house", "houses"}), "Even the houses here have a " + 
        "carefree feeling. You might be able to enter one from here.\n");
    add_item("building", "It looks like an inn!\n");
    add_item(({"end", "dead end"}), "The street has come to the end in " + 
        "front of a noisy building. Either that, or the building has been " + 
        "built in the middle of the street.\n");
    add_item("inn", "It looks plain from the outside, but hearing the " + 
        "laughing and shouting coming from the inside, you can tell it's a " + 
        "rather rowdy inn.\n");

    add_exit(KROOM + "street04", "north", 0);
    add_exit(KROOM + "inn01.c", "southeast", "@@enter_inn", 0);

    add_cmd_item("house", "enter", "@@enter_house");

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " +
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " +
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("You can hear the sounds of merrymaking from the inn nearby.\n");
    add_tell("A small bug skitters under a bush.\n");

    reset_kendermore_room();
    return;
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "You have come to a dead end, " + 
        "something not uncommon in Kendermore. Houses stand on both sides " + 
        "of you, and to your southeast you can " + 
        "hear music and merrymaking coming from a hastily built building. " + 
        "To your north the street continues " + 
        "on its winding way.\n");
}

int
enter_inn()
{
    write("You open the front door and step into the inn.\nThe sound of " + 
          "laughter and chattering kender reaches your ears.\n");
    say(QCTNAME(TP) + " opens the door to the inn and steps in.\n");
    tell_room(KROOM + "inn01", "The front door opens, and " + QTNAME(TP) + 
        " enters the inn.\n");
    return 0;
}

string
enter_house()
{
    write("You look for a way into the house, but find none.\n");
    say(QCTNAME(TP) + " searches for a way into the house, but finds " +
        "none.\n");
    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

