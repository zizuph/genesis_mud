#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;

object kender;
object bird;

void
reset_kendermore_room()
{
    if (!kender)
        {
            kender = clone_object(KNPC + "std_kender");
            kender->move(TO);
        }
    if (!bird)
        {
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
        }
}

void
create_kendermore_room()
{
    set_short("A small roundabout");
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
    add_item("tree", "Its branches spread to the heavens. This tree " + 
        "must be very old. Perhaps here before Kendermore was even " + 
        "built.\n"); 
    add_item("branches", "You might be able to climb the tree into them.\n");
    add_item("roundabout", "It doesn't seem to lead anywhere specific, " +              "much like many of the streets in Kendermore.\n");

    add_cmd_item("tree", "climb", "@@climb_tree");
    add_cmd_item("house", "enter", "@@enter_house");

    add_exit(KROOM + "street44", "northeast", 0);
    add_exit(KROOM + "street42", "southeast", 0);

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
        "winding way to the northeast following a small roundabout, and to " + 
        "the southeast. A very large tree here seems to be the home for " + 
        "many songbirds. Numerous signs point " + 
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
climb_tree()
{
    if (TP->query_skill(SS_CLIMB) < 30)
    {
        write("Perhaps you'd better take climbing lessons from Vincint " +
            "first!\n");
        say(QCTNAME(TP) + " looks at the tree, perhaps thinking " +
            "of climbing it.\n");
        return "";
    }

    if ((TP->query_encumberance_weight() > 29) && 
        (TP->query_skill(SS_CLIMB) < 45))
    {
        write("You start to make your way up the ancient tree, but " + 
            "your foot slips and you fall to the ground with a heavy " + 
            "thud.\n");
        say(QCTNAME(TP) + " starts to make " + HIS(TP) + " way up the " + 
            "ancient tree, but " + HIS(TP) + " foot slips and " + HE(TP) +
            " falls to the ground with a heavy thud.\n");
        return "";
    }

    write("You make your way up the ancient tree.\n");
    say(QCTNAME(TP) + " climbs the ancient tree.\n");
    tell_room(KROOM + "tree", QCTNAME(TP) + " arrives from below.\n");
    TP->move_living("M", KROOM + "tree", 0, 0);
    return "";
}
        
