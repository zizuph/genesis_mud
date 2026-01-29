/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "hazelnut"
#define H2 KRHERB + "labr_tea"
#define H3 KRHERB + "lady_slipper"
#define H4 KRHERB + "tiger_lily"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A peaceful pine forest");
    set_long("@@long_descr");
    add_item(({"forest", "plants", "plant", "tree", "trees","greenery"}), 
        "Numerous " + 
        "pine trees surround you. Other ground plants and shrubs spot the " + 
        "area.\n");      
    add_item(({"ground plants", "shrubs"}), "They look healthy and green.\n");
    add_item(({"needles", "ground"}), "Needles blanket the ground.\n");
    add_item(({"light", "shimmering light"}), "It seems to be a magic " + 
        "portal of sorts.\n");

    set_tell_time(300);
    add_tell("A bird bursts into glorious song, trilling and warbling, then " +
        "sings quietly again.\n");
    add_tell("The wind whispers through the branches and ruffles your hair " +
        "gently.\n");
    add_tell("A squirrel runs out in front of you and scampers up a nearby " +
        "tree.\n");
    add_tell("A rabbit hops out from a nearby hole, but quickly retreats " +
        "when he sees you.\n");
    add_cmd_item("tree", "climb", "@@climb_tree");
    seteuid(getuid(TO));
    set_search_places(({"herbs", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    add_invis_exit(KROOM + "nowhere", "north", "@@stop_message");
    add_exit(KROOM + "gnome03", "west", "@@go_west");
    add_exit(KROOM + "gnome05", "east", "@@go_east");
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

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return tod_descr() + "You are surrounded by greenery on all sides. Pine " +
      "needles cover the ground amidst the ground plants. The smell of pine " + 
      "fills your nose, and the sound of birds chirping reaches your ears. " + 
      "A shimmering light shifts to the east.\n";
}

int
go_west()
{
    write("You step further into the pine forest.\n");
    say(QCTNAME(TP) + " steps further into the pine forest.\n");
    return 0;
}

int
go_east()
{
    write("You walk through the shimmering light to the east, leaving the " + 
        "smell of pine behind and stepping into a an ancient oak forest.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the east " + 
        "and disappears.\n");
    return 0;
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
climb_tree()
{
    write("The branches are too high here.\n");
    return "";
}


