/*
 *  /d/Sparkle/area/tutorial/town/adv_guild6.c
 *
 *  The second floor of the Greenhollow Adventurer's Guild.
 *  This room trains and teaches about thief skills.
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


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the training room for thief skills");
    set_long("Though dimly lit, this room provides enough light for you"
      + " to read the tutorial sign which stands prominently"
      + " beside the door. Shadows obscure the corners of the"
      + " room. Here, you can <learn> or <improve> thief"
      + " skills. You can read the sign for more information.\n\n");

    add_item( ({ "door", "doors", "doorway", "doorways", "east",
                 "east wall", "eastern wall" }),
        "A doorway leads through the eastern wall to a stairwell"
      + " which leads down to the first floor.\n");
    add_item( ({ "shadow", "shadows", "corner", "corners",
                 "corner of the room", "corners of the room" }),
        "This room seems designed to have deep shadows in many"
      + " places. Perhaps in the shadows, a thief is at his or"
      + " her best.\n");
    add_item( ({ "light", "darkness", "dark" }),
        "There is very little light here. Shadows crowd in on"
      + " all sides.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    create_skill_raise();
    set_up_skills();

    add_exit("adv_guild2", "east");
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
      + " that improve your thieving abilities. Use the <learn>"
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
    sk_add_train(SS_SNEAK, ({ "sneak around unnoticed" }),
                 0, 0, 10 );
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
    write("It seems that you have improved the thief skills you know"
      + " to the maximum level that they can be trained in this guild."
      + " It is possible that you still have a few thief skills yet"
      + " to <learn> here. If not, there are Adventurer Guilds"
      + " scattered throughout Genesis where you will be able to train"
      + " these and other thief skills to a higher level than are"
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
    write("You have learned all of the thief skills that this"
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

    if (!present("alivia"))
    {
        npc = clone_object(NPC_DIR + "thief_trainer")->move(
            this_object());
    }
} /* reset_room */

