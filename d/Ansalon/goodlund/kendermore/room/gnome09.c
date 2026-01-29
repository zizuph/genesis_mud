/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "poison_ivy"
#define H2 KRHERB + "saskatoon"
#define H3 KRHERB + "horsetail"
#define H4 KRHERB + "wild_cuke"
#define H5 KRHERB + "grey_willow"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("By a swiftly running river");
    set_long("@@long_descr");
    add_item(({"plants", "plant", "tree", "trees"}), "Several plants and " + 
        "trees grow by the abundant water supply.\n");
    add_item(({"river banks", "river bank", "bank", "banks",}), "The banks " + 
        "are very muddy near the river.\n");
    add_item("mud", "It looks slippery, better not fall!\n");
    add_item(({"willow", "willows", "willow tree", "willow trees"}), "The " + 
        "willow trees grow on the banks of the river. Its graceful branches " + 
        "hang down over the water.\n");
    add_item("branches", "They are long, hanging down almost to the ground.\n");
    add_item("water", "It looks cold, but clean.\n");
    add_item(({"lights", "shimmering lights"}), "They seem to be magic " + 
        "portals of a sort.\n");
    add_item("river", "It looks wide and fast. You would be swept away if " + 
        "you tried to enter it.\n");

    add_cmd_item("tree", "climb", "@@climb_tree");
    set_tell_time(200);
    add_tell("Your foot slips in the mud, but you catch your balance " + 
        "quickly.\n");
    add_tell("A cool breeze blows from the river, tossling your hair and " + 
        "making the branches sway.\n");
    add_tell("A snake slithers into a nearby hole.\n");

    seteuid(getuid(TO));
    set_search_places(({"mud", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
    add_herb_file(H5);

    add_invis_exit(KROOM + "nowhere", "north", "@@stop_message");
    add_exit(KROOM + "gnome08", "south", "@@go_south");
    add_exit(KROOM + "gnome10", "west", "@@go_west");
    add_invis_exit(KROOM + "nowhere", "east", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northeast", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@stop_message");

    reset_kendermore_room();
    return;
}

void
init()
{
    ::init();
    add_action("drink_water", "drink");
}

/* Function name : Drink water
 * Description : Slightly fills a PC with water.
 * Returns : 0 or 1
*/

int
drink_water(string str)
{
    NF("Drink what?\n");
    if ((str == "from water") || (str == "water") ||
        (str == "from river") || (str == "water from river"))
    {
        if (TP->drink_soft(TP->drink_max() / 16,0))
        {
            say(QCTNAME(TP) + " kneels down and takes a drink of water " + 
                "with " + HIS(TP) + " cupped hand.\n");
            write("You kneel down and take a drink of water with your " + 
                "cupped hand, refreshing you.\n");
        }
        else
            write("You can't drink another drop!\n");
        return 1;
    }
    return 0;
}

string
climb_tree()
{
    write("You slip in the wet river mud, falling flat on your face, as " + 
        "you try to reach the nearest branch.\n");
    say(QCTNAME(TP) + " slips in the wet river mud, falling flat on " +
        HIS(TP) + " face.\n"); 
    return "";
}

int
go_west()
{
    write("You walk through the shimmering light to the west, leaving the " +
        "river behind and stepping onto a vast green plain.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the west " +
        "and disappears.\n");
    return 0;
}

int
go_south()
{
    write("You walk through the shimmering light to the south, leaving the " +
        "river behind and stepping into a murky swamp.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the south " +
        "and disappears.\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return (tod_descr() + "A small river runs swiftly here. Willows " +
        "grow on the muddy river bank. Healthy green plants grow in " + 
        "abundance by the river. Every so often, a wild animal approaches " + 
        "the river cautiously for a drink. Shimmering lights shift to the " + 
        "west and south.\n");
}

int
stop_message()
{
    write("You cannot make your feet move in that direction.\n");
    say(QCTNAME(TP) + " lifts " + HIS(TP) + " foot, then sets it " + 
        "down again, a puzzled expression on " + HIS(TP) + " face.\n");
    return 1;
}

