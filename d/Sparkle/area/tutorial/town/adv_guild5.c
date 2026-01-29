/*
 *  /d/Sparkle/area/tutorial/town/adv_guild5.c
 *
 *  The second floor of the Greenhollow Adventurer's Guild.
 *  This room trains and teaches about magic skills.
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
    set_short("the training room for magic skills");
    set_long("An odd odor hits your nose as you enter this room."
      + " Whether it is from incense, or the many dried herbs"
      + " which hang from the ceiling, you are uncertain. Shelves"
      + " crowded with books line walls which are covered in"
      + " arcane symbols you cannot understand. Here, it is"
      + " possible to <learn> and <improve> skills dedicated"
      + " to magic, as you can learn more about by reading"
      + " the sign.\n\n");

    add_item( ({ "odor", "scent", "scents", "smell", "aroma" }),
        "The smell in this room is neither sweet nor foul. It"
      + " is brings to mind hints of musk, old leather, and"
      + " saffron, mixed with a multitude of herbal essences.\n");
    add_item( ({ "door", "doors", "doorway", "doorways", "north",
                 "north wall", "northern wall" }),
        "A doorway leads through the northern wall to a stairwell"
      + " which leads down to the first floor.\n");
    add_item( ({ "herb", "herbs", "dried herb", "dried herbs",
                 "many herbs", "many dried herbs", "up",
                 "roof", "ceiling" }),
        "A large assortment of dried herbs hang from the ceiling,"
      + " filling the room with strange scents and aromas.\n");
    add_item( ({ "shelf", "shelves", "book", "books",
                 "bookshelf", "bookshelves",
                 "shelf crowded with books",
                 "shelves crowded with books" }),
        "There are enough books in this room to consider it a"
      + " small library of sorts. Most of the books seem to be"
      + " about magic of one sort or another.\n");
    add_item( ({ "wall", "walls", "symbol", "symbols",
                 "arcane symbol", "arcane symbols" }),
        "The walls are a deep midnight blue, and have been"
      + " painted in gold with many arcane symbols. Though"
      + " they are quite beautiful to look at, you have no idea"
      + " what they might mean.\n");

    add_cmd_item( ({ "book", "books" }),
                  ({ "read" }),
        "You flip through a few of the books. Many are in"
      + " languages that you do not understand, and those that"
      + " you do are more complicated than your young mind can"
      + " begin to comprehend.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    create_skill_raise();
    set_up_skills();

    add_exit("adv_guild2", "north");
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
      + " that improve your ability with magic. Use the <learn>"
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
    sk_add_train(SS_SPELLCRAFT, ({ "control spellcasting" }),
                 0, 0, 15 );
    sk_add_train(SS_HERBALISM,  ({ "identify and harvest useful herbs" }),
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
    write("It seems that you have improved the magic skills you know"
      + " to the maximum level that they can be trained in this guild."
      + " It is possible that you still have a few magic skills yet"
      + " to <learn> here. If not, there are Adventurer Guilds"
      + " scattered throughout Genesis where you will be able to train"
      + " these and other magic skills to a higher level than are"
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
    write("You have learned all of the magic skills that this"
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

    if (!present("bibbiss"))
    {
        npc = clone_object(NPC_DIR + "magic_trainer")->move(
            this_object());
    }
} /* reset_room */

