#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>

inherit KENDERMORE_OUT;

string *things=({(KOBJ + "hat"), (KOBJ + "metal"), (KOBJ + "shell"),
    (KOBJ + "ring"), (KOBJ + "bells")});

object junk;

void
reset_kendermore_room()
{
    if (!junk)
    {
        junk = clone_object(things[random(5)]);
        junk->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("At the base of a water tower");
    set_long("@@long_descr");

    add_exit(KROOM + "aguild", "southeast", 0);

    add_item(({"water tower", "tower"}), "It holds water meant to be used " + 
        "by the citizens of Kendermore. Oddly enough, there doesn't seem " + 
        "to be a tap to get the water out.\n");
    add_item("water", "You don't see any way to get to it without the " + 
        "necessary tap.\n");

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " + 
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " + 
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("A small bug skitters under a bush.\n");

    add_cmd_item("tower", "climb", "@@climb_tower");

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
    return (tod_descr() + season_descr() + "You stand at the base of " +
        "a very tall water tower. You imagine that this is a favorite " + 
        "place for kender to test their climbing skills. The only way " + 
        "out is to a large courtyard to the southeast.\n"); 
}

string
climb_tower()
{
    if (TP->query_skill(SS_CLIMB) < 30)
    {
        write("Perhaps you'd better take climbing lessons from Vincint " + 
            "first!\n");
        say(QCTNAME(TP) + " looks at the water tower, perhaps thinking " + 
            "of climbing it.\n");
        return "";
    }

    if ((TP->query_skill(SS_CLIMB) < 45) &&
        (TP->query_encumberance_weight() >29))
    {
        write("You start to make your way up the water tower, but slip " + 
            "suddenly and fall to the ground. Luckily you escape with " + 
            "only a slight bruising.\n");
        say(QCTNAME(TP) + " starts to make " + HIS(TP) + " way up the " + 
            "water tower, but slips suddenly and falls to the ground.\n");
        return "";
    }

    write("You scurry up the water tower.\n");
    say(QCTNAME(TP) + " scurries up the water tower.\n");
    tell_room(KROOM + "up_tower", QCTNAME(TP) + " arrives from below.\n");
    TP->move_living("M", KROOM + "up_tower", 1, 0);                          
    return "";
}
