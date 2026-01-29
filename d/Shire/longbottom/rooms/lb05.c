/*
 * Longbottom
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

inherit "/d/Shire/std/room";
inherit "/d/Gondor/common/lib/time.c";
inherit LB_BASE_ROAD;

void

create_room()

{
    set_short("The village of Longbottom");
    set_long("You are walking along a street in the middle of Longbottom, " +
        "a village set in a deep valley of the Southfrthing in the Shire. " +
        "On the southwest side of the road, various circular doors and " +
        "windows reveal the smials set into the steep ravine wall that " +
        "rises high above you. " +

//"To the northeast, a long, ornate building " +
//        "reaches around to sit along the banks of a small stream which " +
//        "runs parallel to the road. " +

        "To the northeast run a stream. On it banks is a small ornate " +
        "building. " +

        "Beyond the stream " +
        "are endless fields growing the famous longbottom leaf. " +
        "This road continues further into town to the southeast and out " +
        "of the valley to the northwest.\n");
    add_item(({"building", "square building"}),
        "This small ornate building looks exquisitely taken care of, " +
        "from the neatly trimmed shrubs on the lawn to the swirling " +
        "decorative carvings on the wall of the building itself. \n");
//    add_item(({"sign", "blue and green sign", "beautiful sign"}),
//        "Someone has obviously put a lot of effort into crafting this sign! " +
//        "Deep green letting, bordered in yellow sits on a field of bright " +
//        "blue reading 'The Pipesmokers Guild of Longbottom'. You can " +
//        "even spot the artists impression of wispy pipesmoke drifting " +
//        "up from each individual letter.\n");

    lb_road();

// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook"}));

//    add_exit(LB_RM_DIR + "pipe1", "northeast", "@@pipe@@");
    add_exit(LB_RM_DIR + "mayor", "northeast", "@@mayor@@");

    add_exit(LB_RM_DIR + "lb04", "southeast");
    add_exit(NS_RD_DIR + "rooms/road11", "northwest", "@@valley@@");
}

int
valley()
{
    write("You follow the road as it climbs up and out of the " +
        "valley of Longbottom.\n\n\n");
    return 0;
}

int
mayor()
{
    write("The mayor's house is closed. He's gone away on vacation!\n");
    return 1;
}

int
pipe()
{
    write("The Pipesmokers Club of Longbottom is currently closed for " +
        "renovations, but it is expected to be open before Christmas.\n");
    return 1;
}

public void
init()
{
    ::init();
// This initializes the drink function.
    init_drink();
    add_action("do_enter","enter");
}

int
do_enter(string str)
{

   if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
   {
     write("You enter the open burrow.\n");
     say(QCTNAME(TP)+ " leaves into the open burrow.\n");
     TP->move_living("M",LB_SMIAL_DIR + "5_front",1);
     return 1;
    }

   write("Enter what, the smial?\n");
   return 1;
}
