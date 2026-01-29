/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"

#define H1 KRHERB + "mandrake"
#define H2 KRHERB + "sphagnum"
#define H3 KRHERB + "cranberry"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A murky swamp");
    set_long("@@long_descr");
    add_item(({"plants", "plant"}), "They grow up out of the water.\n"); 
    add_item(({"reeds", "cattails"}), "They thrive in the murky swamp.\n");
    add_item("insects", "They swarm around your head, waiting to bite.\n");
    add_item(({"water", "swamp"}),  "It is still and murky.\n");
    add_item(({"lights", "shimmering lights"}), "They seem to be magical " + 
        "portals of a sort.\n");

    seteuid(getuid(TO));
    set_search_places(({"water", "plants", "swamp"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    
    set_tell_time(200);
    add_tell("A fresh breeze blows through the swamp, refreshing you. It " + 
        "quickly dies down though.\n");
    add_tell("An annoying insect buzzes in your ear.\n");
    add_tell("Your foot sinks into the mud of the swamp, and makes a loud " + 
        "slurping sound as you pull it out.\n");

    add_invis_exit(KROOM + "nowhere", "west", "@@stop_message");
    add_exit(KROOM + "gnome07", "south", "@@go_south");
    add_exit(KROOM + "gnome09", "north", "@@go_north");
    add_invis_exit(KROOM + "nowhere", "east", "@@stop_message");
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
    return (tod_descr() + "You stand knee deep in a murky swamp. The " + 
        "water is still, and insects swarm about you. A few reeds and " + 
        "cattails grow around you. Shimmering lights shift to the north " + 
        "and south.\n");
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
go_north()
{
    write("You walk through the shimmering light to the north, leaving the " +
        "murky swamp behind and stepping onto a riverbank.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the north " +
        "and disappears.\n");
    return 0;
}

int
go_south()
{
    write("You walk through the shimmering light to the south, leaving the " +
        "murky swamp behind and stepping into an ancient oak forest.\n");
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

