/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <macros.h>


#ifdef RHOVANION_CLOSED
#define SHIRE_MISTY_DIR  "/d/Shire/misty/"
#else 
#define SHIRE_MISTY_DIR  MISTY_DIR
#endif


void
create_room()
{
    set_short("small path");
/*
// original descr
    set_long("You have found the beginning of a small path that climbs the "+
      "south slope of the valley full of bushes and turns towards "+
      "the Misty Mountains.\n");
*/
    set_long("You stand on an overgrown path beyond the bushes. Tall " +
        "grasses and bushes grow everywhere, obstructing your view and " +
        "your movement. The feet of the Misty mountains rise before " +
        "you to the north. Grass-covered mounds are scattered about " +
        "the area, silent reminders of a devastating battle.\n");
    
    add_item("valley", 
        "This is a fair green valley, punctuated with grass-covered " +
        "mounds. Tall grasses and bushes grow everywhere. \n");
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
    add_exit(NEW_ANGMAR + "g2", "southeast",    0,    3);
    reset_room();
}

void
init()
{
    ::init();
    add_action("enter_bushes", "enter");
}

int
enter_bushes(string str)
{
    NF("Enter what?\n");
    if((str != "bushes") && (str != "bush")) return 0;
    tell_room(SHIRE_MISTY_DIR + "p1", QCTNAME(TP)+" jumps out of the bushes.\n");
    TP->catch_msg("You wade through the bushes to the other side.\n");
    TP->move_living("M", SHIRE_MISTY_DIR+"p1", 1);
    tell_room(TO, QCTNAME(TP)+" wades "+HIS_HER(TP)+" way through the bushes.\n");
    return 1;
}


void
reset_room()
{
}
