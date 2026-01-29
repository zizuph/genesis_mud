#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_IN;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave", }));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "fforest13","out",0);
    add_exit(ROOM + "fwatchtower_platform","up",0);

    add_item(({"floor","ground floor","watchtower","ruins","tower",
        "hollow tower"}),
        "The ground floor of the watchtower is overgrown and in ruins, " +
        "with the only structure of note being the spiral staircase " +
        "going up to the platform above.\n");
    add_item(({"spiral staircase","staircase","stairs"}),
        "A 10-foot-wide spiral staircase runs up the hollow tower to a " +
        "platform above you.\n");
    add_item(({"platform","top"}),"The spiral staircase leads to a " +
        "platform above you, where the light from a fire makes the " +
        "shadows dance morbidly against the walls of the tower.\n");
    add_item(({"light","fire","shadows","walls"}), "The light from a " +
        "fire up on the platform above casts shadows against the wall " +
        "that seem to dance morbidly before you.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "tower","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "ground floor of a partially collapsed watchtower";
}

string
long_descr()
{
    return "You stand on the ground floor of an a partially collapsed " +
        "watchtower. Crafted over 300 years ago during the Dwarfgate " +
        "Wars, it has stood the test of time... just... in spite of " +
        "abandonment and neglect. A 10-foot-wide spiral staircase leads " +
        "up the hollow tower to a platform at the top.\n";
}

