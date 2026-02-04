/* Basic room, ready-made for modification, Azireon. */
/* Modified by Azireon, September 11, 1992, concert_hall.c */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

create_room()
{
    set_short("Concert Hall");
    set_long(break_string(
        "The size of this chamber is incredible.  Its floor is " +
        "contoured in such a way that it slopes into the center " +
        "where a large ovalur marble stage has been raised.  Water " +
        "seeps and drips from the ceiling and walls and a pool has " +
        "formed around the stage.  Hundreds of padded wooden chairs, " +
        "in various stages of decay, lay scattered about.  The smell " +
        "of mildew is unbearable.  There is a large opening in the " +
        "vaulted ceiling.\n", 70) );

    add_item( ({ "opening", "ceiling" }),
        break_string(
        "Far above, you can make out strange bas-relief work that " +
        "covers the ceiling with a maze of images.  You would have " +
        "to take a look from the stage to really see through the " +
        "opening in the ceiling.\n", 70) );

    add_item("stage",
        break_string(
        "There seems to be a pile of blankets or something on the " +
        "stage as well as a large case.  You could go north and " +
        "take a closer look.\n", 70) );

    add_item( ({ "water", "pool" }),
        break_string(
        "The pool is quite rancid;  the water and humidity have " +
        "rotted anything of value in the chamber.\n", 70) );

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room. */
    add_prop(ROOM_HAS_WATER, 1);  /* For Dust's quest! */

    add_exit(MANSION + "second/stage", "north", 0);
    add_exit(MANSION + "second/antechamber", "south", 0);
}
