/*
 * Arwen's bedroom
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A private bedroom");
    set_long("This private bedroom appears to belong to a " +
        "beautiful woman. It is decorated tastefully with " +
        "paintings and furniture. The room has a " +
        "lovely bed set against the north wall. Next to the " +
        "bed is a small table. A vanity sits against " +
        "one wall while a dresser is against another. A soft " +
        "rug covers the floor.\n");

    add_item("bed",
        "The bed is large with four posts. It is ornately " +
        "carved from fine grained oak and covered with a " +
        "mattress, a bedcover, and some pillows.\n");
    add_item(({"post", "posts", "bedposts", "bedpost"}),
        "Each post is about the height of a elven lady. They are " +
        "cylindrical shaped and topped with a pointed end.\n");
    add_item("mattress",
        "The mattress is thick and comfortable looking. It is full of " +
        "feathers and covered with a white cotton linen cloth.\n");
    add_item(({"bedcover", "large bedcover"}),
        "The bedcover is light blue and decorated with a " +
        "flower motif. It is thick and luxurious and stuffed " + 
        "with down feathers. The bedcover is spread across " +
        "the bed.\n");
    add_item(({"pillows", "pillow"}),
        "Several soft pillows sit on the bed. They are blue " +
        "and decorated with a flower print.\n");
    add_item("furniture",
        "There is a vanity and a stool, a small table by the bed, " +
        "and a dresser.\n");
    add_item("vanity",
        "The vanity is made of maple and without decoration. " +
        "It sits against the wall. A large mirror hangs in " +
        "front of it. It has six drawers, three on each side, " +
        "which are closed. Some assorted jewelry is scattered " +
        "across the top. A small stool is under the vanity.\n");
    add_item("mirror",
        "The mirror is large. It is made from a large semi-" +
        "circle shaped piece of glass and hangs in front of " +
        "the vanity.\n");
    add_item(({"perfume", "perfumes"}),
        "You see none.\n");
    add_item("jewelry",
        "On the vanity, you see some brooches, necklaces, " +
        "bracelets, and rings. They were all made by the " +
        "elves. They are made from mithril and other precious " +
        "metals and gems.\n");
    add_item(({"brooches", "pins"}),
        "The brooches are different sizes. Some are large and " +
        "designed to fasten clothes together at the throat or " +
        "shoulder. Others are small and to be worn as decorative " +
        "pins. All are fashioned from gold, silver, and mithril " +
        "and set with jewels.\n");
    add_item(({"necklace", "necklaces"}),
        "These ornaments are strings of jewels and semi-precious " +
        "stones. They are priceless, fashioned by elven " +
        "jewelsmiths and stunning to behold. The necklaces are " +
        "truly for a regal lady.\n");
    add_item("bracelets",
        "The bracelets are made from jewels and metal. They are " +
        "beautiful and fit for a regal woman.\n");
    add_item("rings",
        "The rings are made of gold, silver, and mithril. They " +
        "were crafted by the elven jewelsmiths and have " +
        "precious jewels set into them.\n");
    add_item("windows",
        "The windows are large, filling the west and north " +
        "walls. Each window is divided vertically into two " +
        "sections each vertical section divided horizontally " +
        "into four squares. Large curtains cover the window.\n");
     add_item("curtains",
        "They are made from a heavy fabric and are open, " +
        "letting in sunlight during the day and star and " +
        "moonlight at night.\n");
    add_item("stool",
        "The stool is hand crafted from fine wood. It has a " +
        "low back and a cushion in the seat.\n");
    add_item(({"seat cushion", "chair cushion", "cushion"}),
        "The cushion is worn from use. It is green colored.\n");
     add_item("dresser",
        "The dresser is tall is carved of maple. It has six " +
        "large drawers which allow guests to store their " +
        "clothes. The drawers are closed. The top of the " +
        "dresser is empty. Each corner has been fluted which " +
        "extends from the top of the dresser down to the legs.\n");
    add_item("dresser legs",
        "The legs of the dresser are plain, except for the " +
        "fluting which extends up the corners of the dresser.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a maroon color " +
        "with a golden fringe. The rug is decorated with an " +
        "image of a golden forest.\n");
    add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");
    add_item(({"drawers", "dresser drawers", "vanity drawers",}),
        "The drawers are closed shut.\n");
    add_item(({"paintings", "ornate paintings", "painting", 
            "ornate painting", "portraits", "portrait"}),
        "The paintings depict three people. One is of a handsome elven man, " +
        "another is of a stately, regal female elf and the " +
        "third is of the woman's betrothed.\n");
    set_extra_wall("Ornate paintings decorate the walls.");
    set_extra_floor("A deep dark green rug covers the floor.\n");
    set_extra_window("The @@window_count@@ set into the " +
        "north and east walls.\n");
    set_extra_floor("A large rug covers the floor.");

    add_item(({"east window", "eastern window"}),
        "@@east_up@@\n");
    add_item(({"north window", "northern window"}), 
        "@@north_up@@\n");
    set_extra_window("@@window_position@@ set into the " +
        "north and east walls.");

    num_of_windows=2;

    add_cmd_item("rug", ({"move", "lift"}), "@@move_rug@@");
    add_cmd_item(({"bureau drawers", "dresser drawers"}), "open", 
        "@@open_dresser@@");
    add_cmd_item("vanity drawers", "open", "@@open_vanity@@");
    add_cmd_item("drawers", "open", "@@open_drawers@@");

 
    add_exit(VALLEY_DIR + "balcony01", "south");
    add_exit(VALLEY_DIR + "u_cor02",  "west");
}
 
void
init()
{
    ::init();
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "north");
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


string open_vanity()
{
    return "You rattle the drawers attempting to open them. All " +
        "you hear are some tinkling sounds within them. " +
        "Nonetheless, they remain closed.\n";
}
