/*
 *  /d/Emerald/common/guild/aod/rooms/ogre_train.c
 *
 *  This is the basic training hall for all ogres who are members of
 *  the Army of Darkness. Here, Ogres may improve their innate abilities.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "blackwall_room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit AOD_LIB_DIR + "train_hooks";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

/* definitions */
#define            TRAINER          AOD_NPC_DIR + "ogre_trainer"

/* Global variables */
public mixed       Trainer;
public string      Trainer_Id = "_aod_ogre_trainer";

/* prototypes */
public void        create_blackwall_room();
public void        set_up_skills();
public mixed       trainer_present();
public void        make_trainer();
public void        reset_room();
public int         try_skills(string str);
public void        init();
public varargs int sk_query_max(int snum, int silent);


/*
 * Function name:        create_blackwall_room
 * Description  :        set up the room
 */
public void
create_blackwall_room()
{
    set_short("a large rugged plateau used for basic training");
    set_em_long("A large rugged plateau spreads out before the base"
      + " of the hills which ring this area to the north. This is"
      + " the basic training zone for Ogres who are part of the"
      + " Army of Darkness. If the trainer is present, you may"
      + " try to <learn> or <improve> your skills here. Two paths"
      + " lead up into the hills northeast and northwest, and the"
      + " trail to the southeast travels back down the cliffs.\n");

    add_item( ({ "here", "area", "plateau", "large plateau",
                 "rugged plateau", "large rugged plateau",
                 "training area", "training zone", "zone",
                 "basic training zone", "terrain", "rugged terrain" }),
        "A great training pit has been dug into the otherwise"
      + " rugged terrain of this plateau. It is perhaps twelve"
      + " feet deep and thirty yards square. Within, ogres may"
      + " spar with one another to improve their basic combat"
      + " abilities.\n");
    add_item( ({ "pit", "training pit", "great pit",
                 "great training pit" }),
        "One can only imagine how long it would have taken to dig"
      + " such a pit without the use of ogres on the job.\n");
    add_item( ({ "base", "path", "paths", "two paths", "north" }),
        "Two paths make their way up the base of the hills to the"
      + " northeast and northwest. Each of them leads to more"
      + " more advanced training grounds.\n");
    add_item( ({ "trail", "southeast", "cliff", "cliffs", "base",
                 "base of the cliffs", "cliff base" }),
        "Southeast of here, the trail descends from this plateau back"
      + " to the base of the cliffs.\n");

    add_outdoor_items();

    create_guild_support();
    set_up_skills();

    add_exit("defensive_train", "northwest");
    add_exit("offensive_train", "northeast");
    add_exit("courtyard", "southeast");

    reset_room();
} /* create_blackwall_room */


/*
 * Function name:        set_up_skills
 * Description:          Initialize the trainer and set the skills
 *                       we train.
 */
public void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_UNARM_COMBAT, "smash faces with fists",
                 "unarmed combat", 0, 90);
    sk_add_train(SS_DEFENSE, "trick enemies with movement",
                 "defense", 0, 75);
    sk_add_train(SS_SWIM, "wade in the water",
                 "swim", 0, 50);
} /* set_up_skills */


/*
 * Function name:        trainer_present
 * Description  :        Function to see if the trainer is present.
 *                       If so, we return the string of their nonmet
 *                       name
 * Returns      :        int 1 -- trainer present, int 0 -- not present
 */
public mixed
trainer_present()
{
    object  npc_trainer;

    if (!objectp(npc_trainer = present(Trainer_Id, this_object())))
    {
        return 0;
    }

    return npc_trainer->query_nonmet_name();
} /* trainer_present */


/*
 * Function name:        make_trainer
 * Description  :        Move the trainer into this room.
 */
public void
make_trainer()
{
    if (objectp(Trainer))
    {
        return;
    }

    Trainer = clone_object(TRAINER);
    Trainer->add_name(Trainer_Id);
    Trainer->move_living("down", this_object());
} /* make_trainer */


/*
 * Function name:        reset_room
 * Description  :        Upon reset, make sure the room has a trainer.
 */
public void
reset_room()
{
    make_trainer();
} /* reset_room */


/*
 * Function name:        try_skills
 * Description  :        We only want to allow skill training if the
 *                       trainer is present, and can see the player.
 * Arguments    :        string str - what was typed after the verb
 * Returns      :        1 - no training possible
 *                       0 - allow training.
 */
public int
try_skills(string str)
{
    object  npc_trainer;

    this_player()->reveal_me(1);
    if (!objectp(npc_trainer = present(Trainer_Id, this_object())))
    {
        write("There is no one present who could train you.\n");
        return 1;
    }
    if (!CAN_SEE(npc_trainer, this_player()))
    {
        write("The " + npc_trainer->query_nonmet_name()
         + " cannot see you!\n");
        return 1;
    }
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
    {
        write("The " + NPC + " bellows: What?! Who you??"
          + " ARMY TRAINING ONLY!!!\n");
        return 1;
    }

    return 0;
} /* try_skills */


/*
 * Function name:        init
 * Description  :        Add some actions to the player
 */
public void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();
    add_action(try_skills, "learn");
    add_action(try_skills, "improve");
} /* init */


/*
 * Function name: sk_query_max
 * Description  : Give the max skill we can teach to for a skill.
 * Arguments    : int snum - the skill-number to check.
 *                int silent - don't tell anything to the player if true.
 * Returns      : int - the maximum you can train the skill to.
 *
 * The mask of this function is to control the skill level players in
 * the Army are able to train to.
 */
public varargs int 
sk_query_max(int snum, int silent)
{
    int     skulls = AOD_MASTER->query_skull_total(this_player(), 0);

    if (snum == SS_UNARM_COMBAT)
    {
        return 90;
    }

    if (snum == SS_DEFENCE)
    {
        return 75;
    }

    return ::sk_query_max(snum, silent);
} /* sk_query_max */
