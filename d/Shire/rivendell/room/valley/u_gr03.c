/*
 * Guestroom in Elrond's House
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A guestroom");
    set_long("This is a guestroom in Elrond's house. The room " +
        "is quiet, peaceful, and simply furnished. It is " +
        "decorated simply with some paintings on " +
        "the walls. A large window is on the west wall. A night " +
        "stand, a bed, and a dresser are in the room.\n");
 
 
    add_item(({"painting", "paintings"}),
        "Both paintings are of long forgotten elven battles.\n");
    add_item(({"large bed", "bed"}),
        "The bed is made of light maple. A large headboard sits " +
        "at the head of the bed and a small baseboard sits at " +
        "the end. A large bedcover covers the bed with some " +
        "pillows at the head of the bed.\n");
    add_item("baseboard", 
        "The baseboard is as tall as the bed. It is plain " +
        "except for the top. It is carved so that it sweeps " +
        "outward live a wave on the sea.\n");
    add_item("headboard", 
        "The headboard is taller than the bed, allowing the " +
        "guest to sit up in bed comfortably. The headboard is " +
        "plain except for the top. It is carved so that it " +
        "sweeps outward live a wave on the sea.\n");
    add_item("mattress",
        "The mattress is thick and comfortable looking. It is full of " +
        "feathers and covered with a white cotton linen cloth.\n");
    add_item(({"bedcover", "large bedcover"}),
        "The bedcover is beige and covered with a shell pattern. " +
        "It is thick and luxurious and stuffed with down feathers. " +
        "The bedcover is spread across the bed.\n");
    add_item(({"pillows", "pillow"}),
        "There are five soft and fluffy pillows on the bed. Like " +
        "the bedcover, they are beige and covered with a " +
        "shell motif.\n");
    add_item("night stand",
        "The night stand is a small table next to the bed. " +
        "It allows guests a place to put their personal items " +
        "before retiring for the night. It has been carved out " +
        "of maple.\n");
    add_item("dresser",
        "The dresser is tall is carved of maple. It has six " +
        "large drawers wich allow guests to store their " +
        "clothes. The drawers are closed. The top of the " +
        "dresser is empty. Each corner has been fluted which " +
        "extends from the top of the dresser down to the legs.\n");
    add_item("top of dresser",
        "The top of the dresser is bare.\n");
    add_item("top of night stand",
        "The top of the night stand is bare.\n");
    add_item("dresser legs",
        "The legs of the dresser are plain, except for the " +
        "fluting which extends up the corners of the dresser.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a maroon color " +
        "with a golden fringe. The rug is decorated with a " +
        "large sailing ship upon a blue ocean.\n");
   add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");
 
    set_extra_wall("Some pictures decorate the walls.");
    set_extra_floor("A beautiful rug covers the floor.");

    add_item(({"west window", "western window"}),
        "@@west_up@@\n");
    add_item(({"south window", "southern window"}), 
        "@@south_up@@\n");
    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");

    num_of_windows=2;

 
    add_exit(VALLEY_DIR + "u_cor01", "east");
}
 
 
void
init()
{
    ::init();
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "east");
    add_action("on_bed",        "jump");
    add_action("do_nothing",    "tackle");
    add_action("do_nothing",    "dance");
    add_action("do_nothing",    "bow");
    add_action("do_nothing",    "curtsey");
    add_action("do_nothing",    "wiggle");
    add_action("do_nothing",    "strut");
    add_action("do_nothing",    "kill");
 
}
 
int
do_sit(string str)
{
    if(str != "on bed")
    {
        write("Sit where? On the bed, maybe??\n");
        return 1;;
    }
 
    TP->add_prop(LIVE_S_EXTRA_SHORT, " lying on a large bed");
    TP->add_prop("i_am_sat",1);
    write("You climb onto the bed.\n");
    say(QCTNAME(TP)+ " lies on a large bed.\n");
    return 1;
 
}
 
int
do_stand()
{
    if(!TP->query_prop("i_am_sat"))
    {
        write("But you're not lying on the bed!\n");
        say(QCTNAME(TP)+ " gazes out the windows.\n");
        return 1;
    }
 
    TP->remove_prop("i_am_sat");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You jumps up off the bed.\n");
    say(QCTNAME(TP)+ " jumps up off the bed and " +
        "looks around.\n");
    return 1;
 
}
 
int
do_nothing()
{
    if(TP->query_prop("i_am_sat"))
    {
        write("You can't do that while lying on the bed!\n");
        say(QCTNAME(TP)+ " looks around.\n");
        return 1;
    }
}
 
 
int
on_bed()
{
    if(TP->query_prop("i_am_sat"))
    {
        write("You jump up and down on the bed, before landing " +
            "on your bottom!\n");
        say(QCTNAME(TP)+ " jumps up and down on the bed.\n");
        return 1;
    }
}

