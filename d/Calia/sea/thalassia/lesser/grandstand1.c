
/* 	Grandstand in the Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Royal Grandstand of Thalassia");
    set_long("You have entered the Royal Grandstand of Thalassia. "+
        "This is where the animal races take place on the racetrack "+
        "that circles above the Grove of Lord Diabrecho. There are "+
        "stairs heading up to the upper levels of the building. At "+
        "the moment, the stairs are blocked off.\n");
    add_item("stairs","There is a sign next to the stairs.\n");
    add_item("sign","The sign reads: Opening soon.\n");

    add_swim_exit(THALL+"lesser5","north",0,1);
    add_swim_exit(GROVE+"grove1","northwest",0,1);
    add_swim_exit(THALL+"lesser6","northeast",0,1);
    add_swim_exit(THALL+"lesser3","west",0,1);
  /*  add_swim_exit(THALL+"grandstand3","up",0,1);  */
}

int
do_read(string str)
{
    notify_fail("Read what? The sign?\n");

    if (!str || (str != "sign"))
        return 0;

    write("The sign reads: Opening Soon.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
}
