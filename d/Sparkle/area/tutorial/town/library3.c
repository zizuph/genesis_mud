/*
 *  /d/Sparkle/area/tutorial/town/library3.c
 *
 *  This is the west wing of the library. This room teaches
 *  players about statistics and races.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 *  Updated description to fit the updated sign. Cherek, March 2023.
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    8  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the west wing of the Library of Greenhollow");
    set_long("This is the west wing of the Library of Greenhollow which"
      + " is dedicated to information about the races of Genesis."
      + " Down the hall to the east, you could re-enter the main"
      + " hall of the library.\n\n");

    add_item( ({ "library", "here", "building", "area",
                 "greenhollow library", "library of greenhollow" }), long);
    add_item( ({ "east", "hall", "main hall", "main hall of the library" }),
        "You would need to travel east to get a closer view.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("library", "east");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint? Sure ... here you can <read sign> and then <exa>"
      + " each of the statues in the room. For example, you could"
      + " <exa gnome statue> or <exa elf statue> to learn about"
      + " each of those races.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object  statue;
	object  npc;
    string *races = ({ "human", "elf", "dwarf", "gnome",
                       "hobbit", "goblin" });

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    if (present("_tutorial_statue"))
    {
        return;
    }

    foreach (string race: races)
    {
        statue = clone_object(OBJ_DIR + "race_statue");
        statue->set_statue(race);
        statue->add_adj(race);
        statue->add_name(race);
        statue->move(this_object());
    }
	
	if (!present("_tutorial_priest"))
    {
        npc = clone_object(NPC_DIR + "priest")->move(this_object());
    }
} /* reset_room */
