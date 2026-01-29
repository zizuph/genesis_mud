/*
 *  /d/Sparkle/area/tutorial/town/adv_guild3.c
 *
 *  The second floor of the Greenhollow Adventurer's Guild.
 *  This room trains and teaches about fighting skills.
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
public int         get_rack(string arg);
public void        reset_room();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the training room for fighting skills");
    set_long("This room of the Adventurers Guild looks dedicated"
      + " to combat training. A mat on the floor stretches the length"
      + " of the room. Combat dummies are scattered about the place,"
      + " and the wall holds a rack filled with an assortment of"
      + " various weapons. Here you can <learn> and <improve>"
      + " skills related to combat, as the tutorial sign will"
      + " explain in detail.\n\n");

    add_item( ({ "door", "doors", "doorway", "doorways" }),
        "The doorway leads back toward the south to the stairwell"
      + " which leads down to the first floor.\n");
    add_item( ({ "thick mat", "mat", "floor", "ground" }),
        "A thick mat covers the floor to protect trainees from"
      + " harsh falls which might be injurious otherwise.\n");
    add_item( ({ "dummy", "dummies", "combat dummy",
                 "combat dummies" }),
        "Combat dummies have been set up around the room to assist"
      + " in the training process.\n");
    add_item( ({ "wall", "walls", "rack", "weapon rack",
                 "weapon racks", "weapon", "weapons",
                 "various weapons", "sword", "swords", "axe",
                 "axes", "club", "clubs", "knife", "knives",
                 "dagger", "daggers", "rack of weapons",
                 "racks of weapons" }),
        "The walls are lined with racks which contain weapons of"
      + " all shapes and sizes. You see different types of swords,"
      + " axes, clubs, knives, and daggers - all of which look to"
      + " have been dulled a bit to avoid any serious injuries"
      + " while training is taking place.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    create_skill_raise();
    set_up_skills();

    add_exit("adv_guild2", "south");
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
    add_action(get_rack, "get");
    add_action(get_rack, "take");
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
    write("Need a hint? No problem ... in here you can train skills"
      + " that will make you a better fighter. Use the <learn>"
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
    sk_add_train(SS_UNARM_COMBAT, ({ "fight without weapons" }),
                 0, 0, 20 );
    sk_add_train(SS_DEFENCE,      ({ "defend yourself",
                                     "defend against attackers" }),
                 0, 0, 20 );
    sk_add_train(SS_WEP_SWORD,    ({ "fight with a sword" }),
                 0, 0, 20 );
    sk_add_train(SS_WEP_KNIFE,    ({ "fight with knives and daggers" }),
                 0, 0, 20 );
    sk_add_train(SS_WEP_CLUB,     ({ "fight with blunt weapons" }),
                 0, 0, 20 );
    sk_add_train(SS_WEP_AXE,      ({ "fight with an axe" }),
                 0, 0, 20);
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
    write("It seems that you have improved the fighting skills you know"
      + " to the maximum level that they can be trained in this guild."
      + " It is possible that you still have a few fighting skills yet"
      + " to <learn> here. If not, there are Adventurer Guilds"
      + " scattered throughout Genesis where you will be able to train"
      + " these and other fighting skills to a higher level than are"
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
    write("You have learned all of the fighting skills that this"
      + " guild has to offer. If you have not already done so, you"
      + " should use the <improve> command to further your knowledge"
      + " of these skills.\n");
    return 1;
} /* sk_hook_no_list_learn */


/* 
 * Function name:        get_rack
 * Description  :        Allow players to try to take things from the
 *                       weapon rack.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
get_rack(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* the mudlib can handle such basic commands */
    }

    if (!parse_command(arg, ({}),
        "[a] [the] 'weapon' / 'weapons' / 'sword' / 'swords'"
      + " / 'axe' / 'axes' / 'club' / 'clubs' / 'knife' /"
      + " 'knives' / 'dagger' / 'daggers' [from] [the] [weapon]"
      + " [rack]"))
    {
        return 0; /* again, send it to the mudlib */
    }

    write("You lift one of the weapons from the rack and swing it"
      + " around a bit. The blade is too dull to be useful to you"
      + " in anything other than training, so you put it back.\n");
    return 1;
} /* get_rack */



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
        write("\nThere are also " + LANG_WNUM(num) +
            " skills available here that you can acquire using the"
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

    if (!present("_fighting_trainer"))
    {
        npc = clone_object(NPC_DIR + "fighting_trainer")->move(
            this_object());
    }
} /* reset_room */

