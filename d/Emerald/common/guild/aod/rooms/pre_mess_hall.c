/*
 *  /d/Emerald/common/guild/aod/rooms/pre_mess_hall.c
 *
 *  This is the room that exists before the mess hall has been built.
 *
 *  Created November 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("in a large cavernous area");
    set_em_long("This place seems to have been only partially"
      + " completed. A large cavernous area has been opened in the"
      + " rock, seemingly to allow many very large persons to be"
      + " in here at the same time. A few dead animals litter the"
      + " floor. Otherwise, the room is empty.\n");

    add_item( ({ "chamber", "room", "here" }), long);
    add_item( ({ "area", "cavern", "cavernous area", "large area",
                 "large cavernous area" }),
        "Large. Large and cavernous.\n");
    add_item( ({ "animal", "animals", "dead animal", "dead animals" }),
        "These animals have been pretty much ripped apart. It is hard"
      + " to tell, but they might have once been cows.\n");
    add_item( ({ "cow", "cows" }),
        "A hoof here, a tail there ... yep, these were cows alright."
      + " It almost looks like someone was trying to figure out how to"
      + " do something with them. Hmmm ... you do notice a few tools"
      + " near the carnage.\n");
    add_item( ({ "hoof", "hooves" }),
        "Oh, the bovinity of it all!\n");
    add_item( ({ "tail", "tails" }),
        "Just ........... sit right back and you'll hear a tail ...\n");
    add_item( ({ "carnage" }),
        "Bloody hell!\n");
    add_item( ({ "tool", "tools", "few tools" }),
        "Well, they wouldn't exactly be called cooking tools, but it"
      + " may perhaps have been the case that an Ogre was actually"
      + " trying to figure out how to get some cooking going in here."
      + " Obviously, all efforts so far have been a dismal failure.\n");

    add_cave_items();
    add_spike("mess_hall");

    add_exit("tunnel4", "west");
} /* create_cave_room */
