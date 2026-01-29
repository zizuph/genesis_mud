/*
 *  /d/Sparkle/guilds/new_merc/rooms/adapt_train.c
 *
 *  Within the grounds of the Mercenary Guild beside the lodge and south
 *  of the sawmill wherein players may join the guild. This room is
 *  open to non-guild members.
 *
 *  Created April 2009, by Cooper Sherry (Gorboth)
 *
 *  Updated July 23, 2016 by Mercade (code) and Gronkas (this comment)
 *
 *  2020-06: Lucius
 *  - Fixed player_possessive() VBFC call 
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public void        set_up_skills();
public void        leave_inv(object ob, mixed to);
public void        init();
public varargs int sk_query_max(int snum, int silent);
public mixed       trainer_present();
public void        make_trainer();
public void        reset_room();
public int         try_skills(string str);
int                sk_hook_unknown_skill(string skill, string verb);
int                sk_hook_improve_unknown(string skill);
int                sk_hook_learn_known(string skill);
int                sk_hook_cant_pay(string skill, int to_lev, int cost);
int                sk_hook_no_list_learn();
int                sk_hook_no_list_improve();
int                sk_hook_improved_max(string skill);

/* definitions */
#define            TRAINER          NPC_DIR + "adapt_trainer"
#define            NPC              this_object()->trainer_present()

/* Global variables */
public mixed       Trainer;
public string      Trainer_Id = "_merc_adapt_trainer";


/* 
 * Function name:        create_merc_room
 * Description   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("just west of a large lodge in the training yard of"
      + " the Mercenary Guild");
    set_long("The sounds of intense combat which can be heard to"
      + " the north have all but ceased in this enclosed area of"
      + " the Mercenary training ground. Just to the south, a"
      + " guarded fence runs the perimeter of the clearcut between"
      + " the old lodge just to the east and the forest to the west."
      + " If the trainer is present, it may be possible to <learn>"
      + " or <improve> skills here. Also, a small area has been"
      + " cleared of vegetation, and a carpet laid down upon which"
      + " one could <meditate>.\n\n");

    try_item( ({ "small area" }),
        "This area appears devoted to meditation. Someone has gone"
      + " to the trouble to make sure it stays clean and free of"
      + " anything disruptive.\n");
    try_item( ({ "carpet" }),
        "It is a simple thing, but would help focus the mind were"
      + " one to wish to <meditate> here.\n");
    try_item( ({ "enclosed area", "area", "here" }),
        "This part of the training yard is enclosed on all sides"
      + " but to the north.\n");
    try_item( ({ "wood", "woods", "forest", "trees", "tree" }),
        "The forest to the west marks the point at which the loggers"
      + " must have ceased their efforts.\n");
    try_item( ({ "south", "fence", "guarded fence" }),
        "A fence of criss-crossed sharpened poles has been placed along"
      + " the perimeter between the lodge and the forest where the"
      + " training yard comes to an end. It doesn't look as if anyone"
      + " who is not welcome will be able to get past that blockade"
      + " very easily.\n");
    try_item( ({ "pole", "poles", "sharpened pole", "sharpened poles",
                 "criss-crossed poles", "criss-crossed sharpened poles",
                 "blockade", "route", "access route" }),
        "The fence clearly means business. No one is going through"
      + " that without first getting permission.\n");
    try_item( ({ "lawn", "wide lawn", "yard", "training yard",
                 "mercenary training yard", "training ground",
                 "training grounds" }),
        "These training grounds extend a ways to the north toward"
      + " the river and then curve around the lodge north and to the"
      + " east, where it appears as if various other types of"
      + " training might be available.\n");
    try_item( ({ "east" }),
        "The old logging lodge which houses the Mercenaries rises"
      + " directly east from here.\n");
    try_item( ({ "bridge" }),
        "The bridge is not visible from here.\n");
    try_item( ({ "mill", "old mill", "logging mill",
                 "old logging mill" }),
        "The mill is not visible from here.\n");
    try_item( ({ "river", RIVERNAME + " river", RIVERNAME,
                 "river " + RIVERNAME, }),
        "The river is a bit too far off to the north to see clearly"
      + " from here.\n");

    add_outdoor_view();
    add_lodge_view();

    add_exit("tactics_train", "north");

    set_no_exit_msg( ({ "northwest", "west", "southwest" }),
        "You wander through the stumps to the edge of the forest,"
      + " but find nothing interesting there, and return to where"
      + " you were.\n");
    set_no_exit_msg( ({ "east", "northeast", "southeast" }),
        "The lodge blocks your movement in that direction.\n");
    set_no_exit_msg( ({ "south" }),
        "There is no opening in the fence on this side of the"
      + " yard.\n");

    /* configure the training */
    set_up_skills();

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_merc_room */

/*
 * Function name: player_possessive
 * Description  : Support function for the VBFC / possessive in set_up_skills.
 * Returns      : string - the possessive of this_player()
 */
public string
player_possessive()
{
    return this_player()->query_possessive();
}

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
public void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_MERC_ADAPT_SKILL, ({ "adapt your skills effectively",
        "adapt "+ VBFC_ME("player_possessive") +" skills effectively" }),
        "adaptability", 80, 100);
} /* set_up_skills */


/*
 * Function name:        leave_inv
 * Description  :        provide support for some issues with adv_guilds
 */
public void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
} /* leave_inv */


/*
 * Function name:        init
 * Description  :        set up the commands for skill improvement
 */
public void
init()
{
    ::init();

    /* add the trainer's commands */
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
 * the Mercenary Guild are able to train to. The idea here is that
 * Mercs can instantly train to 100 minus the number of mudlib defined
 * skills that exist in the game. For each mudlib defined skill, they
 * first have to find the trainer somewhere in the larger game, and
 * train with them, thus earning one more level here.
 */
public varargs int 
sk_query_max(int snum, int silent)
{
    int  lvl;

    if (snum == SS_MERC_ADAPT_SKILL)
    {
        lvl = (m_sizeof(MERC_MASTER->get_info(this_player(),
            "skill_enhance")))
          + (100 - sizeof(MERC_MASTER->query_skillnum_index()));
        return lvl;
    } /* if (snum == SS_MERC_ADAPT_SKILL) */

    return ::sk_query_max(snum, silent);
} /* sk_query_max */


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
        write("The " + NPC + " says: I do not recognize you as"
          + " a Mercenary ... how did you get past the fence? It"
          + " does not matter. Leave now! You'll learn nothing"
          + " from me!\n");
        return 1;
    }

    return 0;
} /* try_skills */


/*
 * Function name: sk_hook_unknown_skill
 * Description  : Player tries to improve or learn an unknown skill.
 * Arguments    : string skill - The skill he sought for.
 *                string verb  - 'learn' or 'improve'.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    notify_fail("There is no skill named '" + skill + "' to " + verb + ".\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " says: I'm afraid I do not teach"
          + " any such skill, my friend.\n");
    }

    return 0;
} /* sk_hook_unknown_skill */


/*
 * Function name: sk_hook_improve_unknown
 * Description  : Player wants to improve a skill he has never learned.
 * Arguments    : string skill - the skill the player tried to improve.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_improve_unknown(string skill)
{
    if (skill != "adaptability")
    {
        notify_fail("You cannot improve that here.\n");
        return 0;
    }

    notify_fail("You must learn a skill before you can improve it.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " says: First, my friend, you must"
          + " <learn> the skill. Only then can we work toward improving"
          + " what you already know.\n");
    }

    return 0;
} /* sk_hook_improve_unknown */


/*
 * Function name: sk_hook_learn_known
 * Description  : Player wants to learn an already known skill.
 * Arguments    : string skill - the skill the player tried to learn.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_learn_known(string skill)
{
    if (skill != "adaptability")
    {
        notify_fail("You cannot do that here.\n");
        return 0;
    }

    notify_fail("You already know that skill, try to improve it.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " says: Ah, but my friend, you have"
          + " already learned the skill. Now, it is time to work to"
          + " <improve> it!\n");
    }

    return 0;
} /* sk_hook_learn_known */


/*
 * Function name: sk_hook_cant_pay
 * Description  : Player cannot pay for session. (Kill him?)
 * Arguments    : string skill  - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 *                int cost - the price that is required, in coppers.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    notify_fail("You do not have enough money with you.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " says: I fear I must refuse until"
          + " you can produce the appropriate funds. I, too, am a"
          + " Mercenary, my friend. We do not work for free!\n");
    }

    return 0;
} /* sk_hook_cant_pay */


/*
 * Function name: sk_hook_no_list_learn
 * Description  : This hook is called when there are no more skills the
 *                player can learn here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_learn()
{
    if (NPC)
    {
        write("The " + NPC + " says: I teach only the adaptability"
          + " skill, my friend. Perhaps you can try to improve it, or"
          + " seek new learning elsewhere in the training yard.\n");
    }
    else
    {
        write("You have learned all of the available skills trained here."
          + " Perhaps you could try to <improve> some of the skills you"
          + " have learned.\n");
    }

    return 1;
} /* sk_hook_no_list_learn */


/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    if (NPC)
    {
        if (!this_player()->query_skill(SS_MERC_ADAPT_SKILL))
        {
            write("The " + NPC + " says: Ah, I see that you are"
              + " new to the ways of adaptability. Before we can"
              + " begin, you must first <learn> what can be taught"
              + " here.\n");

            return 1;
        }

        if (this_player()->query_skill(SS_MERC_ADAPT_SKILL) < 100)
        {
            write("The " + NPC + " says: In order to futher your skill"
              + " in the art of adaptation, you will first need to seek"
              + " out the master trainers of any skills that have yet"
              + " to be trained for adaptation. You may <adapt list> to"
              + " see which skills remain untrained. Then, <ask> me"
              + " about any specific skill, and I will tell you where"
              + " to find the one who will show you how to adapt it.\n\n"
              + "There are levels of the adaptability skill that will"
              + " become available to you as soon as you follow the"
              + " trainers instructions.\n");
        }
        else
        {
            write("The " + NPC + " says: You have mastered all I am able"
              + " to teach you here. May what you have learned serve you"
              + " well, my friend!\n");
        }
    }
    else
    {
        if (this_player()->query_skill(SS_MERC_ADAPT_SKILL) < 100)
        {
            write("The trainer appears to be missing.\n");
        }
        else
        {
            write("There are no skills you can improve here."
              + " Perhaps you would feel like learning some new skills,"
              + " or try to find a new guild elsewhere?\n");
        }
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
    if (skill != "adaptability")
    {
        notify_fail("You cannot do that here.\n");
        return 0;
    }

    if (this_player()->query_skill(SS_MERC_ADAPT_SKILL) < 100)
    {
        notify_fail("You find yourself unable to improve your"
          + " skill with adaptability any further at present. To"
          + " advance in skill, you will need to first follow the"
          + " trainer's instructions.\n");
    }
    else
    {
        notify_fail("You have mastered this skill, and cannot train it"
          + " any further.\n");
    }

    if (NPC)
    {
        if (this_player()->query_skill(SS_MERC_ADAPT_SKILL) < 100)
        {
            write("The " + NPC + " says: In order to futher your skill"
              + " in the art of adaptation, you will first need to seek"
              + " out the master trainers of any skills that have yet"
              + " to be trained for adaptation. You may <adapt list> to"
              + " see which skills remain untrained. Then, <ask> me"
              + " about any specific skill, and I will tell you where"
              + " to find the one who will show you how to adapt it.\n\n");
        }
        else
        {
            write("The " + NPC + " says: You have become as adept with the"
              + " art of adaptation as I, my friend. Go forth, and seek"
              + " your fortune!\n\n");
        }
    }

    return 1;
} /* sk_hook_improved_max */
