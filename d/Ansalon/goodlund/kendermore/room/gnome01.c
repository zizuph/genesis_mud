/* Gnome's magic herb garden, Gwyneth, June 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit KENDERMORE_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define KRHERB "/d/Krynn/common/herbs/"
#define H1 KRHERB + "breadroot"
#define H2 KRHERB + "crocus"
#define H3 KRHERB + "sm_camas"
#define H4 KRHERB + "soapweed"

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A dry desert in the middle of nowhere");
    set_long("@@long_descr");
    add_item(({"plants", "desert plants", "plant"}), "Their roots must " + 
        "be very deep to survive in this climate, but they seem to be " + 
        "thriving.\n");
    add_item("ground", "It is dry and cracked, but a few hardy plants " + 
        "survive here.\n");
    add_item("desert", "This is a parched land with mostly sand.\n");
    add_item("sky", "There's not a cloud to be found.\n");
    add_item(({"light", "shimmering light"}), "It seems to be a magic " + 
        "portal of sorts.\n");

    seteuid(getuid(TO));
    set_search_places(({"ground", "plants"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    add_exit(KROOM + "gnome02", "south", "@@move_message");
    add_invis_exit(KROOM + "nowhere", "east", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "west", "@@stop_message");
    add_invis_exit(KROOM + "nowhere", "north", "@@stop_message");
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
    return tod_descr() + "The air here whips around your skin, drawing " +
      "all the moisture from your body. The ground is slightly cracked " + 
      "from lack of rain. A few tough desert plants and the cloudless " + 
      "deep blue sky are all that can be seen. A shimmering light shifts " + 
      "to the south.\n";
}

int
stop_message()
{
    write("You cannot make your feet move in that direction.\n");
    say(QCTNAME(TP) + " lifts " + HIS(TP) +  " foot, then sets it " + 
        "down again, a puzzled expression on " + HIS(TP) + "face.\n");
    return 1;
}

int
move_message()
{
    write("You walk through the shimmering light, leaving the aird desert " + 
        "behind and stepping into a humid jungle.\n");
    say(QCTNAME(TP) + " steps through the shimmering light to the south.\n");
    return 0;
}

