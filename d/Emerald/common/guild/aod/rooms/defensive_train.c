/*
 *  /d/Emerald/common/guild/aod/rooms/defensive_train.c
 *
 *  This is the Defensive Training Hall for the Army of Darkness guild.
 *  Guild members who have collected 250 skulls or more have access here.
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
#define            TRAINER          AOD_NPC_DIR + "defensive_trainer"

/* Global variables */
public mixed       Trainer;
public string      Trainer_Id = "_aod_defensive_trainer";

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
    set_short("the defensive training zone for the Army of Darkness");
    set_em_long("A sheer cliff rises to the west, providing a boundary"
      + " to what appears to be a small arena for specialized training."
      + " This is the defensive training zone for the Army of Darkness."
      + " If the trainer is present, you could probably <learn> or"
      + " <improve> skills here. The path runs southeast down to the"
      + " basic training pit, and winds up a steep"
      + " ledge to enter a cave to the northeast.\n");

    add_item( ({ "cliff", "cliffs", "sheer cliff", "sheer cliffs",
                 "west", "boundary", "cliff face", "sheer cliff face" }),
        "The Blackwall mountains have risen up directly to the west,"
      + " with this sheer cliff face marking their very feet.\n");
    add_item( ({ "arena", "small arena", "zone", "training zone",
                 "specialized training zone",
                 "defensive training zone" }),
        "Small rocks been placed in a wide circle beneath the cliff"
      + " to designate an defensive training zone.\n");
    add_item( ({ "path", "trail" }),
        "A path runs beside the training zone here before winding its"
      + " way along a ledge to the northeast, eventually entering a"
      + " cave in that direction. Southeast, the path travels back down"
      + " to the basic training zone.\n");
    add_item( ({ "slope", "gradual slope", "north", "higher ground" }),
        "The terrain rises steadily to the north, where the path"
      + " travels to higher ground.\n");
    add_item( ({ "basic training", "pit", "basic trining pit" }),
        "The basic training pit is far below this area, down the"
      + " path to the southeast.\n");
    add_item( ({ "cave" }),
        "The cave to the northeast is still some ways off. The path"
      + " leads up to it from here.\n");

    add_outdoor_items();

    create_guild_support();
    set_up_skills();

    add_exit("elite_train", "northeast");
    add_exit("ogre_train", "southeast");

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
  
    sk_add_train(SS_PARRY, "use clubs for fancy swishing",
                 "parry", 0, 85);
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

    if (snum == SS_PARRY)
    {
        return AOD_TRAINING->aod_training_check(snum, skulls);
    } /* if (snum == SS_PARRY) */

    return ::sk_query_max(snum, silent);
} /* sk_query_max */


/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    int     skulls = AOD_MASTER->query_skull_total(this_player(), 0);

    if (skulls < 10000)
    {
        if (!this_player()->query_skill(SS_PARRY))
        {
            write("The " + NPC + " bellows: No! Not improve! First,"
              + " you <learn> skill!\n");
        }
        else
        {
            write(MIND_JUICE_MESSAGE + "\n");
        }
    }
    else
    {
        write("The " + NPC + " bellows: No training! Maybe <learn>"
          + " new skill or ask other trainer to teach.\n");
    }        

    return 1;
} /* sk_hook_no_list_improve */


/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    int     skulls = AOD_MASTER->query_skull_total(this_player(), 0);

    if (skulls < 10000)
    {
        notify_fail("The " + NPC + " bellows: Brain too dumb! You"
          + " go drink more mind juice! Then more learning to"
          + " swish club in fancy way.\n");
    }
    else
    {
        notify_fail("The " + NPC + " bellows: No more improve fancy"
          + " club swishing. You ready now! All done improving "
          + " ... FOREVER! YOU GO SMASH FACES! Smash! Smash!!"
          + " SMASH!!!\n");
    }        

    return 0;
} /* sk_hook_improved_max */


/*
 * Function name: sk_hook_no_list_learn
 * Description  : This hook is called when there are no more skills the
 *                player can learn here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_learn()
{
    if (!this_player()->query_skill(SS_PARRY))
    {
        write("The " + NPC + " bellows: You not ready to learn!"
          + " Go drink more mind juice!\n");
        return 1;
    }

    write("The " + NPC + " bellows: You learn already! Maybe"
      + " try <improve> or go ask other trainer.\n");

    return 1;
} /* sk_hook_no_list_learn */
