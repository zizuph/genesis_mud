
 /* Path leading to Worshippers Guild */
 /* By Jaacar 04.27.96 */

#pragma save_binary

inherit "/std/room";
inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "/d/Krynn/common/herbsearch.h"

#define KRYNN_HERBS "/d/Krynn/common/herbs/"

void
reset_herb_room()
{
    set_searched(random(3));
}

void
reset_room()
{
    reset_herb_room();
}

void
create_room()
{
    set_short("A small path amongst the rocks");

    set_long("A small path is here among the rocks, leading "+
        "southward into a flatter area. You cannot see the "+
        "village from here, but can hear noises of villagers "+
        "talking to one another from it to the "+
        "north. There are large rocks rising up to the east, "+
        "obscuring your view of that area. A steep rocky cliff "+
        "is directly to the west of you, giving you a fantastic "+
        "view of the sea beyond it. A warm wind blows gently "+
        "across your face, coming up from the water far below.\n");

    add_item(({"steep rocky cliff","rocky cliff","steep cliff",
        "cliff"}),"A steep rocky cliff consisting of large, "+
        "very sharp looking pieces of stone leading downwards "+
        "into the sea, well over three rods beneath you.\n");

    add_item("sea","The sea is a beautiful blue colour, and "+
        "stretches as far out to the west as your eyes can see. "+
        "Large waves crash upon the cliff below you, sending a "+
        "fine spray of water upward, some even reaching your "+
        "face.\n");

    add_item(({"path","ground",}),"The path seems to be no more "+
        "than a little walked trail leading into the flat ground "+
        "to the south.\n");

    add_item(({"flat ground","flat area"}),"Southwards you "+
        "see a much flatter area of land comprised of small "+
        "rocks, grass, and bushes.\n");

    add_item("rocks","The rocks are fairly large, but "+
        "easy enough to climb over and around southwards "+
        "as you need to. Lying on the ground amongst the "+
        "larger rocks to the east are some small rocks.\n");

    add_item(({"small rock","small rocks"}),"These rocks appear "+
        "to be very light and you could probably collect a few if "+
        "you wanted to.\n");

    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");

    seteuid(getuid(TO));

    add_herb_file(KRYNN_HERBS+"cladina");
    add_herb_file(KRYNN_HERBS+"fireweed");
    add_herb_file(KRYNN_HERBS+"grey_willow");

    set_tell_time(80);

    add_tell("A gentle breeze blows on your face.\n");
    add_tell("A spray of water mist hits your face from the cliffs below.\n");
    add_tell("You hear noises that sound like villagers mumbling from the "+
        "north.\n");
    add_tell("A gust of wind picks up and almost blows you over the cliff "+
        "to the west.\n");

    add_exit(BEACH+"rocks","north",0,1);
    add_exit(WOR_TEMPLE+"archway","south",0,1);
    reset_herb_room();
}

void
init()
{
    ::init();
    add_action("collect","collect");
    add_action("dive","dive");
}

int
collect(string str)
{
    object rock;
    int num;
    if (str != "rocks")
    {
        NF("What?\n");
        return 0;
    }
    rock=clone_object("/d/Calia/worshippers/objects/rock");
    num = 3 + random(6);
    rock->set_heap_size(num);
    rock->move(TP,1);
    write("You collect "+num+" rocks from the ground.\n");
    say(QCTNAME(TP)+" collects some rocks from the ground.\n");
    return 1;
}

int
dive()
{
    write("Are you crazy? You'd be smashed against the rocks, and "+
        "split open wide like an oyster being shucked.\n");
    return 1;
}

