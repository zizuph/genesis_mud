/*
 *  /d/Sparkle/area/tutorial/cliffs/cave.c
 *
 *  A cave along the path to Krolock's castle that happens to be
 *  inhabited by mountain lions. It also teaches about teaming.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    41  /* the chapter for the sign */

/* prototypes */
public void        create_silverdell();
public int         check_exit();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("within a dark cave");
    set_long("This dark cave is littered with bones which have been"
      + " picked clean of their flesh. Whatever typically inhabits"
      + " this place appears to have an appetite for meat. A dark"
      + " corridor winds further into the cliffs to the west. East"
      + " the cave opens onto a path.\n\n");

    add_item( ({ "here", "area", "cave", "dark cave" }), long);
    add_item( ({ "bone", "bones", "skeleton", "skeletons" }),
        "Various skeletons are piled along the corners of the cave,"
      + " having been carefully picked clean by hungry teeth and"
      + " tongues.\n");
    add_item( ({ "corridor", "west", "dark corridor" }),
        "To the west, the cave travels deeper into the cliffs.\n");
    add_item( ({ "east", "opening", "path" }),
        "The path is visible through the opening to the east which"
      + " leads out of this cave.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor of the cave is nothing more than ragged stone.\n");
    add_item( ({ "up", "roof", "ceiling", }),
        "The roof of the cave is rough and uneven, having been"
      + " formed by natural processes.\n");
    add_item( ({ "sky" }),
        "The sky is barely visible through the opening to the"
      + " east.\n");
    add_item( ({ "wall", "walls", "cave wall", "cave walls",
                 "stone", "rock", "rock walls" }),
        "The cave is comprised of rock which forms the walls, ceiling"
      + " and floor.\n");

    add_exit("cave_alcove", "west", check_exit, 1, 0);
    add_exit("cliffroad_2", "east");

    add_npc(NPC_DIR + "lion", 3 + random(3), &->arm_me());
    add_npc(NPC_DIR + "alpha_lion", 1, &->arm_me());

    //This room is instanced.
    instance_entrance = 0;

    reset_room();
} /* create_silverdell */


/*
 * Function name:        check_exit
 * Description  :        see if the player is allowed to use the exit.
 *                       if the mountain lions are present, they block.
 * Returns      :        int 1 - block, 0 - allow
 */
public int
check_exit()
{
    if (present("_tutorial_animal", this_object()))
    {
        write("As you try to travel further into the cave, a"
          + " lion leaps in front of you, and growls menacingly.\n");

        if (this_player()->query_wiz_level())
        {
            write("Of course, being a wizard, you pass anyway.\n");
            return 0;
        }
        return 1;
    }

    return 0;
} /* check_exit */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */
