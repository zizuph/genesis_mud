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
    set_long("You are on the small path that climbs the slope of Misty "+
             "Mountains. You can either go down west towards the valley "+
             "or crawl up northeast.\n");
*/
    set_long("Grass covered mounds are scattered about the valley. " +
        "The path winds past them and through the tall grass and bushes. " +
        "The mountains rise in front of you, dominating your view.\n");

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

    add_exit(NEW_ANGMAR + "g2",     "west", 0,    3);
    add_exit(NEW_ANGMAR + "gates", "northeast", 0, 3);
    reset_room();
}

void
reset_room()
{

}
