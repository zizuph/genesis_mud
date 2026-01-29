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
    set_short("Behind a noisy inn");
    set_long("@@long_descr");
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds beyond your view.\n");
    add_item("building", "It appears to be an inn built in the middle " + 
             "of the road! A backdoor to the west leads inside.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");
    add_item(({"end", "dead end"}), "The street has come to the end in " +
        "front of a noisy building. Either that, or the building has been " +
        "built in the middle of the street.\n");
    add_item("inn", "It looks plain from the outside, but hearing the " +
        "laughing and shouting coming from the inside, you can tell it's a " +
        "rather rowdy inn.\n");

    add_exit(KROOM + "street01", "south", 0);
    add_exit(KROOM + "inn01.c", "west", "@@enter_inn", 0);

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
    if (interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "You have come to a dead end, " + 
        "something not uncommon in Kendermore. " + street_descr() + " To " + 
        "your west you can hear " + 
        "music and merrymaking coming from a hastily built building. " + 
        "Numerous signs point in all directions, but they tend to " + 
        "contradict each other and point in directions where there are no " + 
        "exits. To your south the street continues " + 
        "on its winding way.\n");
}

int
enter_inn()
{
    write("You open the back door and step into the inn.\nThe sound of " + 
          "laughter and chattering kender reaches your ears.\n");
    tell_room(KROOM + "inn01", "The backdoor opens and " + QTNAME(TP) + 
        " enters the house.\n");
    return 0;
}

