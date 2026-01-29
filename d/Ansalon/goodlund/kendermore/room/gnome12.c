/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_IN;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "greenslime"
#define H2 KRHERB + "brownslime"
#define H3 KRHERB + "angeltear"
#define H4 KRHERB + "skullcap"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A dark wet forest");
    set_long("You are in a dark wet forest. The branches of the towering " + 
        "trees completely block the sky. Moss and slime cover the rocks on " + 
        "the ground around you. Shimmering lights shift to the west and " + 
        "east.\n");
    add_item("branches", "Water drips from the branches to the ground.\n");
    add_item("trees", "They look ancient and crooked.\n");
    add_item(({"moss", "slime"}), "It grows well in the damp darkness.\n");
    add_item("ground", "It's covered in rocks and boulders.\n");
    add_item("sky", "It is hidden behind the branches.\n");

    set_tell_time(200);
    add_tell("A drop of water falls onto your nose from the branches above.\n");
    add_tell("Glowing eyes blink from the darkness.\n");
    add_tell("A creature scurries up a tree.\n");

    seteuid(getuid(TO));
    set_search_places(({"rocks", "plants","moss","slime"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
    DARK;
    add_invis_exit(KROOM + "nowhere", "north", "@@stop_message");
    add_exit(KROOM + "gnome11", "east", "@@go_east");
    add_exit(KROOM + "g_house", "west", "@@go_west");
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
        "dark wet forest behind and stepping into a crowded room.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the west " +
        "and disappears.\n");
    return 0;
}

int
go_east()
{
    write("You walk through the shimmering light to the east, leaving the " +
        "dark wet forest behind and stepping onto a white sandy beach.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the east " +
        "and disappears.\n");
    return 0;
}


