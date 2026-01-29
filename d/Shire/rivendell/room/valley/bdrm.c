/*
 * Elrond's Bedroom
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;

 
void
create_house_room()
{
    set_short("Elrond's bedroom");
    set_long("You stand in Elrond's bedroom. The room is large " +
        "and comfortable looking. A large bed sits towards the " +
        "north end of the room. The walls are decorated with " +
        "paintings and a large rug covers the floor. A door " +
        "leads south out to the balcony and another door leads " +
        "west to his study.\n");


    add_item(({"painting", "paintings", "portrait", "portraits"}),
        "Over the bed is a large portrait of a beautiful elven " +
        "woman, Elrond's wife. She is beautiful to behold and " +
        "resembles her parents, Celeborn and Galadriel. Looking " +
        "closer, you see painted in one corner 'All my love, " +
        "Celebrian'.\n");
    add_item(({"large bed", "bed"}),
		"The bed is made of light maple. It has four posters " +
        "and a large mattress. A large bedcover covers the " +
        "bed with some pillows at the head of the bed.\n");
    add_item(({"poster", "posters"}),
        "Each poster is about the height of a man. They are " +
        "cylindrical shaped and topped with a pointed end.\n");
    add_item("mattress",
        "The mattress is thick and comfortable looking. It is full of " +
        "feathers and covered with a white cotton linen cloth.\n");
    add_item(({"bedcover", "large bedcover"}),
        "The bedcover is dark purple and covered with a leaf motif. " +
        "It is thick and luxurious and stuffed with down feathers. " +
        "The bedcover is spread across the bed.\n");
    add_item(({"pillows", "pillow"}),
        "There are five soft and fluffy pillows on the bed. Like " +
        "the bedcover, they are deep purple and covered with a " +
        "leaf motif.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a maroon color " +
        "with a golden fringe. The rug is decorated with a " +
        "large sailing ship upon a blue ocean.\n");
    add_item("windows",
        "The windows are large. During the day they fill the " +
        "room with bright sunlight and at night fill the room " +
        "with star and moonlight,\n");
    add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");

    set_extra_wall("Some paintings decorate the walls.");
    set_extra_floor("A beautiful rug covers the floor.");
    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");
    add_item(({"west windows", "western windows", "west window",
        "western windows"}), "@@west_up@@\n");
    add_item(({"south windows", "southern windows", "south window",
        "southern windows"}), "@@south_up@@\n");

    num_of_windows=2;

 
    add_exit(VALLEY_DIR + "balcony02",   "south");
    add_exit(VALLEY_DIR + "elrond_study", "west");
}
 
 
void
init()
{
    ::init();
//    add_action("exa_window",    "look out window");
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_stand",      "rise");
    add_action("do_nothing",    "west");
    add_action("do_nothing",    "south");
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
    mixed	*indices;
    int i;

    if(str != "on bed" || str != "down" )
    {
        write("Sit where? On the bed, maybe??\n");
        return 1;;
    }
 
    if(TP->query_prop("i_am_sat"))
    {
	notify_fail("You are already lying on the bed!\n");
	return 0;
    }
    TP->add_prop(LIVE_S_EXTRA_SHORT, " lying on a large bed");
//    TP->add_prop("i_am_sat",indices[i]);
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
    write("You jump up off the bed.\n");
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
