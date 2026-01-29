/*
 *  /d/Sparkle/area/tutorial/guild/train.c
 *
 *  This is the training room for the Patrol Guild in the tutorial.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* Base file for skill trainers */
inherit "/lib/skill_raise";

#include "guild.h"
#include <ss_types.h>
#include <stdproperties.h>

#define TUTORIAL_CHAPTER  49  /* the chapter for the sign */

/* Prototypes */
void              set_up_skills();
public void       create_silverdell();
void              init();
public void       reset_room();


/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_PARRY, "parry incoming attacks", "parry", 20, 30);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "punch things", "guildpunch",
	20, 30);
}

/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("Training room for the Patrol Guild");
    set_long("This is the training hall for the " + GUILD_NAME + ". Here you may"
      + " spend your coins to <improve> the important skills that you may"
      + " learn exclusively as a member of this occupational guild.\n\n");

    add_item( ({ "here", "hall", "training hall", "room", "area" }),
        "This is a place where you can <improve> skills to increase your"
      + " abilities.\n");
    add_item( ({ "guild", "patrol guild", "building" }),
        "This hall is but a part of the Patrol Guild.\n");
    add_item( ({ "training", "train" }),
        "If you wish to train, you can <improve> various skills here.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor here is rather scuffed-up. Probably from all the activity"
      + " that takes place during training.\n");
    add_item( ({ "up", "roof", "ceiling" }),
        "The ceiling of this room is far out of reach.\n");
    add_item( ({ "sky", "outside" }),
        "You can't see that from indoors.\n");

    add_exit("joinroom", "north");

    /* configure the trainer */
    set_up_skills();

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
}


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */
