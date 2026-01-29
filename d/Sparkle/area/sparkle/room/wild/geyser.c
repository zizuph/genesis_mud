/* 	geyser.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

int gstatus;

void geyser(int arg);

void
create_room()
{
    set_short("Site of the geyser");
    set_long("\n"+
             "This is a damp and misty area.\n"+
             "Small steaming pools and puddles have formed in cracks and hollows.\n"+
             "A sign has been planted in the ground beside a large hole from which\n"+
             "fumes of sulphur arise.\n");

    add_exit("trail_hi","east");

    add_item(({"area","misty area","ground" }),
             "It is very damp and the air is a little difficult to breathe.\n"+
             "");
    add_item(({"pools","puddles" }),
             "Some are quite deep while others seems to be favoured as birdbaths.\n"+
             "");
    add_item(({"cracks","hollows" }),
             "They are filled with hot water.\n"+
             "");
    add_item(({"sign" }),
             "There is something written on it.\n"+
             "");
    add_item(({"hole" }),
             "This is where the fumes come from. It is about one metre in diameter.\n"+
             "");
    add_item(({"fumes" }),
             "Fumes of sulphur and water vapor. It has a sticky smell to it.\n"+
             "");
    add_item(({"water" }),
             "The water is not very pure and not recommended for drinking.\n"+
             "Besides, it is also very hot.\n"+
             "");
    add_item("vapour", "It's all around you making things damp and moist.\n");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    set_alarm(itof(random(10) + 5), 0.0, &geyser(1));
}

int
read(string what)
{
    if (what != "sign") {
        notify_fail("Read what?");
        return 0;
    }
    say(QCNAME(this_player())+ " reads the sign.\n");
    write("\n"+
          "Warning. The geyser erupts at fairly regular intervals.\n"+
          "Normally at about every 15 minutes.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(read,"read");
}

int query_gstatus() { return gstatus; }

void
geyser(int arg)
{
    int delay;

    switch(arg) {
    case 1:
        tell_room(this_object(),
                  "\n\nThere is a faint rumble in the ground.\n");
        delay = random(10) + 15;
        break;
    case 2:
        tell_room(this_object(),
                  "\nThe ground shakes and hot vapour fumes from the hole.\n");
        delay = random(10) + 8;
        break;
    case 3:
        tell_room(this_object(),
                  "\nWith a tremendous roar a enormous geyser spurts high\n"+
                  "up in the air. The air is filled with hot vapour and\n"+
                  "you have serious trouble breathing.\n");
        add_item("geyser", "The geyser spurts high up in the air.\n");
        delay = random(15) + 35;
        break;
    case 4:
        tell_room(this_object(),
                  "\nThe roar from the geyser seems to subside a little.\n");
        delay = 8;
        break;
    case 5:
        tell_room(this_object(),
                  "\nSlowly the geyser loses its strength and within not too long\n"+              "all that remains is a few puddles on the steaming ground.\n");
        remove_item("geyser");
        delay = random(100) + 850;
        break;
    default:
        tell_room(this_object(),
                  "\nFumes rise from the pools around you, making you dizzy.\n");
        delay = 0;
        break;
    }

    if (!delay) return;

    if (arg == 5) {
        gstatus = 1;
        set_alarm(itof(delay), 0.0, &geyser(gstatus));
    }
    else {
        gstatus = arg + 1;
        set_alarm(itof(delay), 0.0, &geyser(gstatus));
    }
}

