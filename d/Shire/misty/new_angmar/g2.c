/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"


void
create_room()
{
    set_short("small path");
/*
// original long descr
    set_long("You are on the path, south above the valley. The path climbs up "+
             "east to the Misty Mountains.\n");
*/
    set_long("Standing amid overgrown bushes and grasses, you notice " +
        "the worn path running northwest and east. It is nothing more " +
        "than a trail threading its way through the overgrown growth " +
        "and grass covered mounds that litter the area. Broken armours " +
        "and weapons lie rusting amidst the bushes, and here and there " +
        "sun-bleached skeletons lie buried in the grass.\n");

    add_item("valley", 
        "This is a fair green valley, punctuated with grass-covered " +
        "mounds. Tall grasses and bushes grow everywhere hiding the skeletons.\n");
    add_item("mountains", 
        "The mountains look somehow dark. Maybe there is hidden danger " +
        "there.\n");
    add_item(({"bushes", "bush"}), 
        "They are overgrown and large. They grow everywhere, making " +
        "travel difficult.\n");
    add_item(({"mounds", "grass-covered mounds"}),
        "They are scattered about the valley, some large and others " +
        "small. They are fallen warriors and stand as reminders of " +
        "the terrible battles fought here.\n");
    add_item(({"grasses", "tall grasses"}),
        "It is green and lush, coming up to your waist. The grass " +
        "grows everywhere, and waves in the breeze.\n");
    add_item(({"path", "worn path"}),
        "It is nothing more that trampled grass that meanders through " +
        "the valley, past the bushes and mounds.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(NEW_ANGMAR + "g1", "northwest",    0,    3);
    add_exit(NEW_ANGMAR + "g3", "east",    0,    3);
    reset_room();
}

void
reset_room()
{
}
