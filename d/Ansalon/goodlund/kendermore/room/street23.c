#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

inherit STREET_DESC;
inherit KENDERMORE_OUT;

#define GET_MONTH (CLOCK->query_month())

void switch_street();

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
    set_short("Outside a loud smithy");
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
    add_item("smithy", "From the noise and the thin trailing " + 
        "smoke coming from it, you can tell that it is a smithy.\n");

    add_cmd_item("house", "enter", "@@enter_house");

    switch_street();

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
        "of you, and a small smithy stands to the south. " + street_descr() + 
        " The road continues on its winding way to the northwest and " + 
        "to the southeast it ends up at a wall of some house. Numerous signs " +
	"point in all directions, but they " + 
        "tend to contradict each other and point in directions where there " + 
        "are no exits.\n");
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
switch_street()
{
    if (GET_MONTH > 6)
    {
        add_invis_exit("null", "northeast", "@@blocked_street");
        add_exit(KROOM + "street24", "southeast", 0);
        add_exit(KROOM + "street22", "northwest", 0);
        add_exit(KROOM + "smithy", "south", 0);
    }
    else
    {
        add_invis_exit("null", "southeast", "@@blocked_street");
        add_exit(KROOM + "street24", "northeast", 0);
        add_exit(KROOM + "street22", "northwest", 0);
        add_exit(KROOM + "smithy", "south", 0);
    }
}
        
int
blocked_street()
{
    write("A house has been built in that direction!\nMaybe there's " + 
        "another way around.\n");
    return 1;
}
