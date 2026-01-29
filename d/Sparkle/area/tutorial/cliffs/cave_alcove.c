/*
 *  /d/Sparkle/area/tutorial/cliffs/cave_alcove.c
 *
 *  An alcove in a cave. Players must defeat a family of mountain
 *  lions to get in here. It contains treasure, and also teaches
 *  players about the praise, bug, and idea commands.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("deep in a dark cave");
    set_long("Though deep inside the cliff here, light filters down"
      + " from some mysterious source high above. This area is hardly"
      + " big enough to stand in, and the only way to get out is to"
      + " go back the way you came.\n\n");

    add_item( ({ "here", "area", "cave", "dark cave" }), long);
    add_item( ({ "corridor", "east", "dark corridor" }),
        "To the east, the cave travels deeper into the cliffs.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor of the cave is nothing more than ragged stone.\n");
    add_item( ({ "up", "roof", "ceiling", }),
        "The roof of the cave is rough and uneven, having been"
      + " formed by natural processes.\n");
    add_item( ({ "sky" }),
        "The sky is not visible here.\n");
    add_item( ({ "wall", "walls", "cave wall", "cave walls",
                 "stone", "rock", "rock walls" }),
        "The cave is comprised of rock which forms the walls, ceiling"
      + " and floor.\n");
    add_item( ({ "light" }),
        "The light appears natural. Perhaps there is a crack in the"
      + " rocks of the ceiling which allow light to enter from the"
      + " outside.\n");

    add_exit("cave", "east");

    //This room is instanced.
    instance_entrance = 0;

    reset_room();
} /* create_silverdell */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object  corpse;

    if (!objectp(corpse = present("_tutorial_corpse", this_object())))
    {
        clone_object(OBJ_DIR + "corpse")->move(this_object());
    }
} /* reset_room */
