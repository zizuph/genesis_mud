/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"

/*
 * prototypes
 */
void reset_room();

/*
 * Global variables
 */
object *guards;

void
create_room()
{
  set_short("By the gates");
/*
// original descr
  set_long("You are standing on a small rocky opening. To the north is a "+
           "smooth mountain wall with massive wooden gates. The area "+
           "has been cleared of every tree, bush and even of grass "+
           "so only bare rock remains leaving no place where even a mouse "+
           "could hide.\n");
*/
    set_long("Tall grasses and overgrown bushes grow everywhere, " +
        "obstructing your view of the land. Grass-covered mounds are " +
        "more numerous here, memorial to fallen warriors. Hiding among " +
        "the grasses and bushes are sun bleached skeletons, some still " +
        "wearing the very armours and weapons they held during their " +
        "last battle.\n");
    
// add_prop(ROOM_M_NO_HIDE, "There is no place where even a mouse could hide.\n");
    add_prop(ROOM_I_HIDE, -1);

    add_item(({"gates","gate"}), 
        "These massive wooden gates once lead into the mountain. They " +
        "hang on broken hinges and swing in the breeze.\n");
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


    add_exit(NEW_ANGMAR + "c3", "north");
    add_exit(NEW_ANGMAR + "g3", "southwest");

  reset_room();
}

void 
reset_room()
{
/*
    object standard;

        if (!present("standard",TO))
    {
        standard = clone_object("/d/Shire/scav_hunt/standard");
        standard->move(TO);
    }
*/
}


void
init()
{
  ::init();

}
