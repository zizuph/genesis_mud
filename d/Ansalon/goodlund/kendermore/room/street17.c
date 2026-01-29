/*
 * 2005-01-06 - Cotillion
 * - Fixed mosue infestation problem.
 */
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
object kender;
object mouse1, mouse2;

void
reset_kendermore_room()
{
    found_junk = 0;

    if (!kender)
    {
        kender = clone_object(KNPC + "std_kender");
        kender->move(TO);
    }

    if (!mouse1)
    {
        mouse1 = clone_object(KNPC + "mouse");
        mouse1->move(TO);
    }
    
    if (!mouse2)
    {
        mouse2 = clone_object(KNPC + "mouse");
        mouse2->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A crooked side street");
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
    add_item("stone", "It looks like there is a loose stone in the cobbled " + 
        "street.\n");

    add_cmd_item("stone", ({"search", "lift", "move"}), "@@lift_stone");
    add_cmd_item("house", "enter", "@@enter_house");

    add_exit(KROOM + "street18", "north", 0);
    add_exit(KROOM + "street10", "southwest", 0);

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
    write("You open the door of the house and walk in.\n");
    say(QCTNAME(TP) + " opens the door to the house and walks in.\n");
    tell_room(KROOM + "house3", "The door opens, and " + QCTNAME(TP) +
        " enters the house.\n");
    TP->move_living("M", KROOM + "house3", 1, 0);
    return "";
}

string
lift_stone()
{
    if (found_junk)
    {
        write("You wiggle the stone, pulling it from its place. There " + 
            "doesn't seem to be anything under the stone anymore.\n");
        say(QCTNAME(TP) + " wiggles a stone loose from the cobbled street.\n");
        return "";
    }

    clone_object(things[random(6)])->move(TP, 1);
    found_junk = 1;

    write("You wiggle the stone, pulling it from its place. You find " + 
        "something underneath, and quickly pocket it!\n");
    say(QCTNAME(TP) + " wiggles a stone loose from the cobbled street.\n");
    return "";
}        
