/*
 *  /d/Sparkle/area/tutorial/pre_creation/elf_chamber.c
 *
 *  This room describes the elf race for the pre-creation
 *  player tutorial.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit PRE_DIR + "hobbit_chamber";
inherit LIB_DIR + "skip";

#include <stdproperties.h>
#include "/d/Sparkle/area/tutorial/lib/statue_items.h"

/* prototypes */
public void        create_room();
public void        reset_room();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    add_name("elf_chamber");
    set_short("a small room set off of a main chamber");
    set_long("This room is little more than an alcove set off"
      + " of a larger chamber. There is a statue of some kind"
      + " here beside a familiar looking sign.\n\n");

    add_statue_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("7", "east", &log_move("7"), 1, 0);

    reset_room();
} /* create_room */


/*
 * Function name:        reset_room
 * Description  :        add a sign to the room
 */
public void
reset_room()
{
    object   statue;
    object   sign;

    if (!present("_tutorial_statue"))
    {
        statue = clone_object(OBJ_DIR + "race_statue");
        statue->set_statue("elf");
        statue->add_adj("elf");
        statue->add_name("elf");
        statue->move(this_object());
    }

    if (!present("_tutorial_sign"))
    {
        sign = clone_object(OBJ_DIR + "sign");
        sign->config_sign("sign");
        sign->set_chapter(8);
        sign->add_adj( ({ "familiar" }) );
        sign->move(this_object());
    }

    return;
} /* reset_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(tutorial_stat, "stats");
    add_action(tutorial_quit, "quit");
} /* init */


