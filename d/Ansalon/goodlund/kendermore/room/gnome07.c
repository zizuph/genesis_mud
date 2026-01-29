/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "sarsaparilla"
#define H2 KRHERB + "veronica"
#define H3 KRHERB + "fireweed"
#define H4 KRHERB + "wild_plum"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A forest of ancient oaks");
    set_long("@@long_descr");
    seteuid(getuid(TO));
    set_search_places(({"ground", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
    add_item(({"plants", "forest", "oaks", "plant", "tree", "trees"}), 
        "Numerous ancient " +
        "trees surround you. Other ground plants and shrubs spot the " +
        "area.\n");
    add_item("sky", "A few white clouds dot the sky.\n");
    add_item(({"underbrush", "ground"}), "Underbrush covers the ground in " +
        "a green carpet.\n");
    add_item(({"ground plants", "shrubs"}), "They look healthy and green.\n");
    add_item(({"light", "shimmering light"}), "It seems to be a magic " +
        "portal of sorts.\n");
    add_item("branches", "They sway gently in the wind.\n");
    add_item("shadows", "They shift as the branches sway in the wind.\n");
    add_cmd_item("tree", "climb", "@@climb_tree");
    set_tell_time(300);
    add_tell("A bird bursts into glorious song, trilling and warbling, then " +
        "sings quietly again.\n");
    add_tell("The wind whispers through the branches and ruffles your hair " +
        "gently.\n");
    add_tell("A squirrel runs out in front of you and scampers up a nearby " +
        "tree.\n");
    add_tell("A rabbit hops out from a nearby hole, but quickly retreats " +
        "when he sees you.\n");


    add_invis_exit(KROOM + "nowhere", "east", "@@stop_message");
    add_exit(KROOM + "gnome08", "north", "@@go_north");
    add_exit(KROOM + "gnome06", "south", "@@go_south");
    add_invis_exit(KROOM + "nowhere", "west", "@@stop_message");
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
    return tod_descr() + "Ancient oak trees raise their branches to " +
      "the sky. Their branches partially block the sky, and draw mottled " + 
      "shadows on the ground where plants cover the ground. The sound of " + 
      "of birds chirping reaches your ears. A shimmering light shifts to " + 
      "the north.\n";
}

int
stop_message()
{
    write("You cannot make your feet move in that direction.\n");
    say(QCTNAME(TP) + " lifts " + HIS(TP) + " foot, then sets it " + 
        "down again, a puzzled expression on " + HIS(TP) + " face.\n");
    return 1;
}

string
climb_tree()
{
    write("The branches are too high here.\n");
    return "";
}

int
go_north()
{
    write("You walk through the shimmering light to the north, leaving the " +
        "ancient oak forest behind and stepping into a murky swamp.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the north " +
        "and disappears.\n");
    return 0;
}

int
go_south()
{
    write("You step further into the ancient oak forest.\n");
    say(QCTNAME(TP) + " steps further into the ancient oak forest.\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

