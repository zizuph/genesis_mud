/*
 *  /d/Sparkle/area/tutorial/town/adv_guild4.c
 *
 *  The second floor of the Greenhollow Adventurer's Guild.
 *  This room trains and teaches about general skills.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/lib/skill_raise";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    14  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public void        set_up_skills();
int                sk_hook_no_list_improve();
int                sk_hook_no_list_learn();
public void        reset_room();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the training room for general skills");
    set_long("This room is absolutely huge! A swimming pool runs the"
      + " length of the east wall. The north wall has all sorts of"
      + " protrusions jutting from it, and looks geared toward"
      + " climbing. Here you can <learn> and <improve> general"
      + " skills, as the tutorial sign will explain in detail.\n\n");

    add_item( ({ "door", "doors", "doorway", "doorways", "west",
                 "west wall", "western wall" }),
        "The doorway leads through the west wall to a stairwell"
      + " which leads down to the first floor.\n");
    add_item( ({ "pool", "swimming pool", "east wall", "east",
                 "eastern wall" }),
        "A swimming pool runs the length of the east wall. Though"
      + " it is not very deep, it almost certainly provides the"
      + " necessary environment to learn the basics of swimming.\n");
    add_item( ({ "north", "north wall", "climbing wall",
                 "protrusion", "protrusions" }),
        "The north wall has been set up to simulate the typical"
      + " challenges one might face when climbing a vertical"
      + " cliff.\n");
    add_item( ({ "south wall", "south", "southern wall", "table",
                 "simple table" }),
        "A simple table rests against the south wall. Perhaps this"
      + " is where one might sit and learn the basics of things"
      + " like language and trading.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    create_skill_raise();
    set_up_skills();

    add_exit("adv_guild2", "west");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    init_skill_raise();

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
    write("Sure, here's a hint ... in here you can train skills"
      + " that will help you get around in the game. Use the <learn>"
      + " and <improve> commands to do so. You should also <ask>"
      + " the trainer about each skill to get a better idea about"
      + " what the skills do. Read the sign for more information.\n");

    return 1;
} /* hint */


/*
 * Function name:        set_up_skills
 * Description  :        add skill training to the room
 */
public void
set_up_skills()
{
    sk_add_train(SS_SWIM,      ({ "swim" }),
                 0, 0, 10 );
    sk_add_train(SS_CLIMB,     ({ "climb things" }),
                 0, 0, 17 );
    sk_add_train(SS_AWARENESS, ({ "notice things in your surroundings",
                                     "be aware of things" }),
                 0, 0, 10 );
    sk_add_train(SS_TRADING,   ({ "buy and sell for better prices" }),
                 0, 0, 10 );
    sk_add_train(SS_APPR_MON,  ({ "appraise an opponent" }),
                 0, 0, 3 );
    sk_add_train(SS_APPR_OBJ,  ({ "appraise the properties of items" }),
                 0, 0, 3 );
    sk_add_train(SS_APPR_VAL,  ({ "appraise the value of an item" }),
                 0, 0, 3 );
} /* set_up_skills */


/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    write("It seems that you have improved the general skills you know"
      + " to the maximum level that they can be trained in this guild."
      + " It is possible that you still have a few general skills yet"
      + " to <learn> here. If not, there are Adventurer Guilds"
      + " scattered throughout Genesis where you will be able to train"
      + " these and other general skills to a higher level than are"
      + " available to you in Greenhollow.\n");
    return 1;
} /* sk_hook_no_list_improve */


/*
 * Function name: sk_hook_no_list_learn
 * Description  : This hook is called when there are no more skills the
 *                player can learn here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_learn()
{
    write("You have learned all of the general skills that this"
      + " guild has to offer. If you have not already done so, you"
      + " should use the <improve> command to further your knowledge"
      + " of these skills.\n");
    return 1;
} /* sk_hook_no_list_learn */


/*
 * Function name: sk_hook_also_learn
 * Description  : This hook is called when there are skills to be learnt when
 *                the player asks about skills to improve.
 * Arguments    : int num - the number of skills to be learnt.
 */
void
sk_hook_also_learn(int num)
{
    if (num == 1)
        write("\nThere is also one skill available here that you can"
          + " acquire using the <learn> command.\n");
    else
        write("\nThere are also " + LANG_WNUM(num)
          + " skills available here that you can acquire using the"
          + " <learn> command.\n");
} /* sk_hook_also_learn */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object   npc;

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    if (!present("paulsen"))
    {
        npc = clone_object(NPC_DIR + "general_trainer")->move(
            this_object());
    }
} /* reset_room */

