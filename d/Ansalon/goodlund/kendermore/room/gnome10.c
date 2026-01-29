/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "locoweed"
#define H2 KRHERB + "chicory"
#define H3 KRHERB + "raspberry"
#define H4 KRHERB + "dandelion"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A vast green plain");
    set_long("@@long_descr");
    add_item(({"plants", "plant"}), "The plants here grow close to the " + 
        "ground to avoid the strong winds that sweep across the plains.\n");
    add_item("ground", "It looks like good soil.\n");
    add_item(({"lights", "shimmering lights"}), "They seem to be magic " + 
        "portals of a sort.\n");
    add_item(({"plain", "plains"}), "It extends to the horizon.\n");
    add_item("sky", "It is overcast and grey.\n");

    set_tell_time(200);
    add_tell("A strong wind sweeps across the plains, almost knocking you " + 
        "over.\n");
    add_tell("A rodent scurries across your path, and disappears into the " + 
        "grass.\n");
    add_tell("A light breeze ruffles your hair, refreshing you.\n");

    seteuid(getuid(TO));
    set_search_places(({"ground", "plains", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    add_invis_exit(KROOM + "nowhere", "north", "@@stop_message");
    add_exit(KROOM + "gnome09", "east", "@@go_east");
    add_exit(KROOM + "gnome11", "west", "@@go_west");
    add_invis_exit(KROOM + "nowhere", "south", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "northeast", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southwest", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@stop_message");

    reset_kendermore_room();
    return;
}

string
long_descr()
{
    return (tod_descr() + "You stand on a wide green plain. Plants are " +
        "abundant, but grow close to the ground. There is nothing but " + 
        "sky, plains and shimmering lights to your east and west for miles.\n");
}

int
stop_message()
{
    write("You cannot make your feet move in that direction.\n");
    say(QCTNAME(TP) + " lifts " + HIS(TP) + " foot, then sets it " + 
        "down again, a puzzled expression on " + HIS(TP) + " face.\n");
    return 1;
}

int
go_west()
{
    write("You walk through the shimmering light to the west, leaving the " +
        "green plains behind and stepping onto a sandy beach.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the west " +
        "and disappears.\n");
    return 0;
}

int
go_east()
{
    write("You walk through the shimmering light to the east, leaving the " +
        "green plains behind and stepping onto a muddy riverbank.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the east " +
        "and disappears.\n");
    return 0;
}


