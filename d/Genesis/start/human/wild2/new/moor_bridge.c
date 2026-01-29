/*      moor_bridge.c
 *
 *  This is a hastily constructed room meant to extend certain roads
 *  and make Style's map consistent with the actual room layouts.
 *  (Gorboth, May 2010)
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_driver();
    set_items_moor();
    set_herbs();

    set_short("Misty Moor");
    set_long("You are standing on the eastern side of an old stone bridge " +
        "which arches over the rushing waters of the Diamond River. The " +
        "land here is lush, filled with tall wet grasses and brightly " +
        "coloured flowers, yet everything is covered in a faint mist that " +
        "hovers in the air and obscures your view east across the moors. " +
        "Someone has laid down a small stone path that crawls east across " +
        "the wetlands, winding around low hills and groves of trees as " +
        "if searching for the Pen Sea that lies beyond. On the other " +
        "side of the river, the tall peaks of the Grey Mountains jut " +
        "high into the sky as they surround the rest of the valley.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor1", "east");
    add_exit(THIS_DIR + "moor_path", "west");
    add_exit(THIS_DIR + "moor_bridge", "northwest","@@riv@@",1,1);
    add_exit(THIS_DIR + "moor_bridge", "southwest","@@riv@@",1,1);
    add_exit(THIS_DIR + "moor_bridge", "north","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor_bridge", "south","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor_bridge", "northeast","@@moor@@",1,1);
    add_exit(THIS_DIR + "steam3", "southeast",0,1,1);

    add_item(({"old bridge","bridge","old stone bridge","stone bridge"}),
        "This is an old stone bridge, yet still in good repair, that " +
        "will lead you across the rushing waters of the Diamond River " +
        "and into the wet moorlands on the other side.\n");
    add_item(({"northwest horizon","northwestern horizon","northwest"}),
        "Looking to the northwest, you can see the jagged peaks of the Grey " +
        "Mountains enclose the valley, separating it from distant " +
        "destinations such as Dwarfheim or the city of Larton.\n");
    add_item(({"west horizon","western horizon","west"}),
        "Looking to the west, the Grey Mountains are at their most " +
        "intimidating, blocking all passage save where the Orc Road " +
        "cuts through the high pass and into the orcish homelands " +
        "beyond.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "Looking to the west, the Grey Mountains are at their most " +
        "intimidating, blocking all passage save where the Orc Road " +
        "cuts through the high pass and into the orcish homelands " +
        "beyond.\n");
    add_item(({"river","diamond river"}),
        "Crashing through the land just east of you, the Diamond River " +
        "tumbles south on its journey to the Pen Sea.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_drink_from(({"stream", "river", "diamond river"}));
}

void
init()
{
    ::init();
    init_drink();
}

/*
 * Function name:        drink_message
 * Description  :        Gives a description of drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}

/*
 * Function name:        riv
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the Diamond River
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
riv()
{
    write("The wide blue waters of the Diamond River prevents you from " +
        "going in that direction. If you want to cross the river, why " +
        "don't you use the bridge to the west?\n");
    return 1;
}
/* riv */

/*
 * Function name:        moor
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the moors in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
moor()
{
    write("You attempt to leave the stone path to make your own way across " +
        "the moors, but you find that the land here is too wet here. You " +
        "will have to try to find an alternative route.\n");
    return 1;
}
/* moor */