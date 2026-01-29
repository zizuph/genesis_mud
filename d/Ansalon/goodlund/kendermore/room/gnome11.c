/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "bch_plum"
#define H2 KRHERB + "bch_willow"
#define H3 KRHERB + "cord_grass"
#define H4 KRHERB + "salt_wort"
#define H5 KRHERB + "ss_grass"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A white sandy beach");
    set_long("@@long_descr");
    add_item("sand", "It's been bleached white by the sun.\n");
    add_item("waves", "They are some of the largest waves you've seen.\n");
    add_item(({"weeds", "rocks", "shells"}), "They are washed onto the sand " + 
        "by the crashing waves.\n");
    add_item("grass", "It grows tall, almost three feet high.\n");
    add_item("water", "It is blue-green tipped with foam, but too " + 
        "salty to drink.\n");
    add_item(({"trees", "tropical trees"}), "Many different types of fruit " + 
        "hang from the branches amidst shiny green leaves.\n");
    add_item("fruit", "You can identify guava, mango and papaya fruits. Many " +
        "hang from the branches, but a lot sits on the ground in various " + 
        "stages from ripe to rotten.\n");
    add_item("branches", "They hang heavy with fruit, but are too high to " + 
        "reach.\n");
    add_item("leaves", "They are a shiny green.\n");
    add_item("ground", "You can make out some ripe pieces of fruit on the " + 
        "ground amidst some of the more rotten pieces. All in all, it " + 
        "smells like a winery.\n");
    add_cmd_item("fruit", "pick", "@@pick_fruit");
    add_cmd_item("tree", "climb", "@@climb_tree");
     
    set_tell_time(200);
    add_tell("The rythmic sound of waves crashing on the beach relaxes you.\n");
    add_tell("A salty breeze blows in from the ocean, brushing your hair " + 
        "from your face.\n");
    add_tell("A piece of fruit drops from the laden branches.\n");
    add_tell("A small hermit crab scurries into a hole.\n");

    seteuid(getuid(TO));
    set_search_places(({"sand", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
    add_herb_file(H5);

    add_invis_exit(KROOM + "nowhere", "north", "@@stop_message");
    add_exit(KROOM + "gnome10", "east", "@@go_east");
    add_exit(KROOM + "gnome12", "west", "@@go_west");
    add_invis_exit(KROOM + "nowhere", "south", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northeast", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@stop_message");

    reset_kendermore_room();
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

string
climb_tree()
{
    write("The branches are too high here.\n");
    return "";
}

int
go_west()
{
    write("You walk through the shimmering light to the west, leaving the " +
        "sandy beach behind and stepping into a dark wet forest.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the west " +
        "and disappears.\n");
    return 0;
}                                                                            

int
go_east()
{
    write("You walk through the shimmering light to the east, leaving the " +
        "sandy beach behind and stepping onto a vast green plain.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the east " +
        "and disappears.\n");
    return 0;
}                                                                            

string
long_descr()
{
    return (tod_descr() + "You are on a long sandy beach. Waves crash " + 
        "against the sand, bringing weeds, rocks, and shells to rest " + 
        "on the land. Long grass waves in the breeze a short distance " + 
        "from the water, and a few tropical trees surround you. Shimmering " + 
        "lights shift to the east and west.\n");
}

int
stop_message()
{
    write("You cannot make your feet move in that direction.\n");
    say(QCTNAME(TP) + " lifts " + HIS(TP) + " foot, then sets it " + 
        "down again, a puzzled expression on " + HIS(TP) + " face.\n");
    return 1;
}

/* Function name : Pick fruit
 * Description : Gives you a piece of tropical fruit on a 50/50 chance.
 * Returns : Null
*/

string
pick_fruit()
{
    int num = (random(2));

    if (num == 0)
    {
        write("You find nothing but rotten fruit here.\n");
        return "";
    }
    else
    {
        clone_object(KOBJ + "trop_fruit")->move(TP, 1);
        write("You search around the pieces of rotten fruit, and find a " + 
            "nice ripe one!\n");
        say(QCTNAME(TP) + " searches around the pieces of rotten fruit, and " + 
            "finds a nice ripe one.\n");
        return "";
    }
}

