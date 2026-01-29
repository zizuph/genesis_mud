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
        "rises high above you. To the northeast, near a small stream, " +
        "you see a low building with signs of a bright fire burning inside" +
        "a steady stream of smoke coming from the chimney. Beyond the stream, " +
        "you can see endless fields growing the famous longbottom leaf. " +
        "This road continues further into town to the northwest and out " +
        "of the valley to the southeast.\n");
    add_item(({"building", "low building", "forge"}),
        "From everything you can see, this building appears to be the " +
        "forge, where the local blacksmith works. The steady light of " +
        "a bright fire burns within, while a steady stream of smoke " +
        "drifts up out of the chimney and into the sky above.\n");
    add_item(({"fire", "smoke", "chimney"}),
        "The fires of the forge near you here are burning brightly, " +
        "working hard if you are any judge of the smoke that constantly " +
        "puffs out of the chimney.\n");
    lb_road();

// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook"}));

    add_exit(LB_RM_DIR + "forge.c", "northeast");
    add_exit(LB_RM_DIR + "lb02.c", "southeast");
    add_exit(LB_RM_DIR + "lb04.c", "northwest");
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
     TP->move_living("M",LB_SMIAL_DIR + "3_front",1);
     return 1;
    }

   write("Enter what, the smial?\n");
   return 1;
}