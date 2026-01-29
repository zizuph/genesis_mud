/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "bkd_sedge"
#define H2 KRHERB + "fdlhead"
#define H3 KRHERB + "horsetail"
#define H4 KRHERB + "onoclea"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A humid jungle forest");
    set_long("@@long_descr");
    add_item("sky", "It is partly blocked by the tree branches, but it " + 
        "looks like a storm is brewing.\n");
    add_item(({"plants", "plant", "greenery"}), "They're all around you! " + 
        "Towering trees, vines and ground plants all thrive in the moist " + 
        "heat.\n");
    add_item(({"trees", "jungle trees"}), "They soar above you, and many " + 
        "vines hang from their branches.\n");
    add_item("branches", "They are strong, with broad green leaves growing " + 
        "on them.\n");
    add_item("ground", "It is damp, and covered with vines and ground " + 
        "plants.\n");
    add_item(({"vine", "vines"}), "They cover the ground and hang down from " + 
        "the trees. They look sturdy enough to swing on!\n");
    add_item(({"leaves", "broad leaves"}), "They look perfect for soaking " + 
        "up the sun.\n");
    add_item("ground plants", "They don't get as much sun as the trees, but " + 
        "they look healthy and green.\n");
    add_item(({"light", "lights", "shimmering light", "shimmering lights"}),
        "They seem to be a magic portal of sorts.\n");
    add_item(({"forest", "jungle"}), "Towering green jungle trees soar " + 
        "above you, reaching for the sky.\n");
    add_cmd_item(({"vine", "on vine", "on vines"}), "swing", "@@vine_swing");
    add_cmd_item(({"tree", "trees", "branches"}), "climb", "@@vine_swing");

    seteuid(getuid(TO));
    set_search_places(({"trees", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    add_exit(KROOM + "gnome03", "south", "@@go_south");
    add_invis_exit(KROOM + "nowhere", "west", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "east", "@@stop_message");
    add_exit(KROOM + "gnome01", "north", "@@go_north");
    add_invis_exit(KROOM + "nowhere", "northwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northeast", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@stop_message");

    reset_kendermore_room();
}

string
long_descr()
{
    return (tod_descr() + "You are surrounded by greenery on all sides. " +
      "Towering jungle trees reach to the sky with their branches. They " + 
      "must be sixty feet at least! A soft rain falls through the branches, " + 
      "beading up on the plants' leaves and dampening your hair. Shimmering " + 
      "lights shift to your north and south.\n");
}

int
stop_message()
{
    write("You cannot make your feet move in that direction.\n");
    say(QCTNAME(TP) + " lifts " + HIS(TP) + " foot, then sets it " + 
        "down again, a puzzled expression on " + HIS(TP) + "face.\n");
    return 1;
}

string
vine_swing()
{
    write("You clamber up a tree, grab hold of a vine and swing down from " + 
        "the tree to the ground with a loud yell!\n");
    say(QCTNAME(TP) + " clambers up a nearby tree, grabs hold of a vine and " + 
        "swings down to the ground with a loud yell.\n");
    return "";
}

int
go_south()
{
    write("You walk through the shimmering light to the south, leaving the " + 
        "humid jungle behind and stepping into a peaceful pine forest.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the south and " + 
        "disappears from sight.\n");
    return 0;
}

int
go_north()
{
    write("You walk through the shimmering light to the north, leaving the " + 
        "humid jungle behind and stepping into an arid desert.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the north and " +
        "disappears from sight.\n");
    return 0;
}


