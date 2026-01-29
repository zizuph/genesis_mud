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
        "a village set in a deep valley of the South Farthing in the Shire. " +
        "On the southwest side of the road, various circular doors and " +
        "windows reveal the smials set into the steep ravine wall that " +
        "rises high above you. To the northeast, you see a short, wooden " +
        "building, nestled up against a small stream which runs parallel " +
        "to the road you are on. Beyond the stream, you can see endless " +
        "fields growing the famous longbottom leaf. This road continues " +
        "further into town to the northwest and out of the valley to the " +
        "southeast.\n");

    add_item(({"building", "wooden building", "inn"}),
        "Nestled against the banks of the small stream near the road, " +
        "is a short wooden building which appears to be the local inn. " +
        "A sign out front displays a picture of a hobbit taking his " +
        "ease while smoking a pipe. The words 'The Silver Tree' have " +
        "been carved above the hobbit in the sign.\n");
    add_item(({"sign", "wooden sign", "hobbit"}),
        "This sign reads 'The Silver Tree' and pictures " +
        "a hobbit resting against a tree, a pipe in his mouth, " +
        "and smoke rings encircling his head.\n");

    lb_road();

// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook"}));

    add_exit(LB_RM_DIR + "inn", "northeast");
    add_exit(NS_RD_DIR + "rooms/road06", "southeast", "@@valley@@",);
    add_exit(LB_RM_DIR + "lb02", "northwest");
}

int
valley()
{
    write("You follow the road as it climbs up and out of the " +
        "valley of Longbottom.\n\n\n");
    return 0;
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
     TP->move_living("M",LB_SMIAL_DIR + "1_front",1);
     return 1;
    }

   write("Enter what, the smial?\n");
   return 1;
}