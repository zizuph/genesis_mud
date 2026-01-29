#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;
inherit QEXITS;

string *things = ({(KOBJ + "bells"), (KOBJ + "cloth"), (KOBJ + "lollipop"),
    (KOBJ + "cfeather"), (KOBJ + "stone"), (KOBJ + "string2")});

object junk;
int found_junk = 0;

void
reset_kendermore_room()
{
    found_junk = 0;
}

void
create_kendermore_room()
{
    set_short("A noisy side street");
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
    add_item(({"post", "lamp post"}), "It's a wide based bronze lamp post " + 
        "with a glass encasing on the top. Inside the glass there is oil " + 
        "and a wick.\n");
    add_item(({"panel", "hidden panel"}), "There must be some trick in " + 
        "opening it.\n");

    add_cmd_item("house", "enter", "@@enter_house");
    add_cmd_item(({"post", "lamp post", "base"}), "search", "@@lamp_post");    

    add_exit(KROOM + "street12", "east", 0);
    add_exit(KROOM + "street14", "northwest", 0);

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
        "of you. " + street_descr() + " A lamp post stands in front of " + 
        "one of the houses. The road continues on its " + 
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

string
lamp_post()
{
    if (found_junk)
    {
        write("You find what looks to be a hidden panel, but nothing is " + 
            "behind it right now.\n");
        say(QCTNAME(TP) + " looks over the lamp post.\n");
        return "";
    }

    clone_object(things[random(6)])->move(TP, 1);
    found_junk = 1;

    write("You find what looks to be a hidden panel in the base of the " + 
        "lamp post. Pushing it aside, you find something and quickly " + 
        "pocket it.\n");
    say(QCTNAME(TP) + " looks over the lamp post.\n");
    return "";
}

