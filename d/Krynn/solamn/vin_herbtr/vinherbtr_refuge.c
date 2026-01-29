/* 
   created by Vitwitch 08/2021 
   based closely on work of :
   Aridor (1993) /d/Krynn/solamn/vin_mount/room/road3
   Arman (2020) /d/Krynn/tharkadan/room/ledge6
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

#define ROOM "/d/Krynn/solamn/vin_herbtr/"

inherit "/d/Krynn/std/room";

/* FUNCTIONS */

public int
do_smell( string arg )
{
    this_player()->catch_mesg("Putting your nose up against " +
     "the rock surface, you get nostrils full of lichen.\n");
    return 1;
}

string
short_descr()
{
    return "A small cave; a shelter from the elements in a high mountain pass";
}

string
long_descr()
{
    return "Relatively warm and dark, this refuge is large enough for " +
        "a party of climbers to wait for bad weather to pass.\n";
}


void
create_krynn_room()
{

    set_short("@@short_descr");
    set_long("@@long_descr");

    INSIDE;
    DARK;

    add_exit(ROOM + "vinherbtr4n","out",0,1,0);
    add_exit(ROOM + "vinherbtr4n","exit",0,1,1);
    add_exit(ROOM + "vinherbtr4n","back",0,1,1);

}

