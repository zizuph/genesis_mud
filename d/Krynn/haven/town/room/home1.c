/*
 * home1.c
 * One of the local residences
 * Haven town
 * Created by Tibbit, 10 Mar 1998
 */

#include "../local.h"
#include <macros.h>

inherit HAVENINBASE;

object citizen;
int did_quest;

void
reset_haven()
{
    reset_euid();

    if(!citizen)
        (citizen = clone_object(HNPC + "citizen_" +
            (random(2) ? "m" : "f")))->move(TO);

    did_quest=0;
}

void
init()
{
    ::init();
    add_action("reach","reach");
}

void
create_haven()
{
    set_short("Simple wooden home");

    set_long("This is one of the simple, wooden-constructed "+
        "homes of the citizens of Haven. "+
        "You note the one-room habitation, subdivided into "+
        "sleeping and eating areas. The room is mostly bare, "+
        "save for a few simple pieces of furniture."+
        "\n");

    add_item(({"habitation","house","home"}),
        "This home is quite simple, though comfortable. It is made "+
        "from wood.\n");
    add_item(({"area","areas","sleeping area","eating area",
        "sleeping areas","eating areas"}),
        "This house is neatly divided into the area where food is "+
        "prepared and eaten, and the area where the local folks "+
        "lie down at the end of their long day.\n");
    add_item(({"furniture","pieces"}),
        "A simple wooden table is attended by a few stools. "+
        "All appear handmade.\n");
    add_item(({"stool","stools"}),
        "There is nothing unusual about the wooden stools here. "+
        "Perhaps you want to look more closely at the table, though.\n");
    add_item("table",
        "You think that you catch a glimpse of something metallic "+
        "up underneath the table. Perhaps you can reach under the table "+
        "and find out what it is?\n");

    add_exit(HROOM+"st5","west");

}

int
reach(string str)
{
    notify_fail("Reach where?\n");
    if((!str) || (!strlen(str)) || (str != "under table"))
        return 0;

    if(did_quest)
    {
        write("You reach under thet table, but don't find anything.\n");
        say(QCTNAME(TP)+" reaches under the table, but doesn't appear "+
            "to find anything.\n");
        return 1;
    }

    did_quest=1;

    write("You reach under the table, and disturb something which was "+
        "hidden there.  It falls to the floor.\n");
    say(QCTNAME(TP)+" reaches under the table, and something falls to the "+
        "floor with a clatter.\n");

    reset_euid();

    clone_object(HOBJ+"chalice")->move(TO);

    return 1;
}


