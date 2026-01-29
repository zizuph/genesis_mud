/*
 * Upper corridor in Elrond's house
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A private bedroom");
    set_long("This private bedroom looks unlived in. It seems " +
        "the person who stays here does not get to spend much " +
        "time here. Nevertheless, the room is spotless and seems " +
        "to be treated with special care. Under a large window " +
        "sits a large bed. Some furniture is scattered around " +
        "the room. A large rug covers the floor.\n");
 
    add_item("bed",
        "The bed is large, constructed of strong maple and " +
        "polished to a golden shine. The grain of the wood " +
        "stands out nicely in contrast with the large mattress, " +
        "bedcover, and pillows.\n");
    add_item("mattress",
        "The mattress is thick and comfortable looking. It is full of " +
        "feathers and covered with a white cotton linen cloth.\n");
    add_item(({"bedcover", "large bedcover"}),
        "The bedcover is dark green and covered with a leaf motif. " +
        "It is thick and luxurious and stuffed with down feathers. " +
        "The bedcover is spread across the bed.\n");
    add_item(({"pillows", "pillow"}),
        "Several soft pillows sit on the bed. They are dark " +
        "purple and are decorated with a leaf motif.\n");
    add_item("furniture",
        "You see a small table by the bed and a dresser.\n");
    add_item(({"seat cushion", "chair cushion", "cushion"}),
        "The cushion is worn from use. It is maroon colored.\n");
     add_item("dresser",
        "The dresser is tall is carved of maple. It has six " +
        "large drawers which allow guests to store their " +
        "clothes. The drawers are closed. The top of the " +
        "dresser is empty. Each corner has been fluted which " +
        "extends from the top of the dresser down to the legs.\n");
    add_item("dresser legs",
        "The legs of the dresser are plain, except for the " +
        "fluting which extends up the corners of the dresser.\n");
    add_item(({"painting", "paintings"}),
        "The paintings are portraits of two people. One of a " +
        "fair woman and the other of a regal looking man.\n");
    add_item(({"first portrait", "portrait of a fair woman",
            "portrait of fair woman"}),
        "The portrait depicts a fair elven woman. She is " +
        "wearing a simple white robe with a single star brooch. " +
        "Her hair is like the color of spun gold and a light " +
        "seems to fill her face. She is slender and stands in a " +
        "classic pose.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a deep maroon " +
        "color accented with a leaf motif with a gold fringe.\n");
    add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");

    set_extra_wall("Ornate paintings decorate the walls.");
    set_extra_floor("A deep rug covers the floor.\n");
    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");
    add_item(({"west windows", "western windows", "west window",
            "western windows"}),
        "@@east_up@@\n");
    add_item(({"south windows", "southern windows", "south window",
            "southern windows"}),
        "@@south_up@@\n");
 
    num_of_windows=2;
 
    add_exit(VALLEY_DIR + "balcony01", "north");
    add_exit(VALLEY_DIR + "u_cor06",  "west");
}
 
void
init()
{
    ::init();
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "north");
    add_action("do_nothing",    "west");
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
    if(str == "in chair")
        {
            write("You try to sit on the chair but are " +
                "unable to.\n");
            return 1;
        }
 
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
        write("You jump up and down on the bed doing several " +
             "somersaults!\n");
        say(QCTNAME(TP)+ " jumps up and down on the bed doing " +
             "several somersaults!.\n");
        return 1;
    }
}
