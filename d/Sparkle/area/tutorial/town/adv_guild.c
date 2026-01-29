/*
 *  /d/Sparkle/area/tutorial/town/adv_guild.c
 *
 *  The main room of the Greenhollow Adventurer's Guild.
 *  This room teaches about meditation.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    12  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        leave_inv(object ob, mixed to);
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in the Adventurers Guild of Greenhollow");
    set_long("You stand in the Adventurers Guild of Greenhollow."
      + " A large carpet is spread out along the floor here, and"
      + " a stairway leads <up> to the second floor of the guild"
      + " above. A tutorial sign here explains what can be done"
      + " in adventurer guilds such as this.\n\n");

    add_item( ({ "carpet", "large carpet" }),
        "The carpet along the floor looks extremely comfortable, with"
      + " a deep purple shag that looks designed for sitting or"
      + " kneeling. You can <meditate> upon the carpet to adjust"
      + " your stat preferences. Read the sign for more information.\n");
    add_item( ({ "stair", "stairs", "stairway" }),
        "The stairs lead to a higher level of this building. Exits such"
      + " as <up> and <down> also appear in the list of obvious exits"
      + " in most situations, and are abbriviated to <u> and <d>.\n");
    add_item( ({ "here", "area", "guild", "adventurers guild",
                 "room", "building" }), long);

    add_indoor_items();
    add_window_items();
    add_door_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("street_1", "south");
    add_exit("adv_guild2", "up");
} /* create_silverdell */


/*
 * Function name:        do_climb
 * Description  :        allow players to climb the stairs
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to climb?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] 'stair' / 'stairs' / 'stairway'"))
    {
        return 0; /* let the mudlib handle it */
    }

    write("You climb up the stairs to the second floor.\n");
    if (this_player()->query_wiz_level())
    {
        write("Here, we normally move the player 'up' using"
          + " command(). Since you are a wizard, that won't"
          + " work. Simply move yourself <up> manually.\n");
    }

    this_player()->command("$up");
    return 1;
} /* do_climb */


public void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
} /* leave_inv */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();

    add_action(hint, "hint");
    add_action(do_climb, "climb");
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
    write("Need a hint? No problem ... all you have to do here is"
      + " type <meditate> in order to set your stat preferences."
      + " You can go <u> here, to get to the higher levels of the"
      + " guild.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    write("Improving skills is not possible here. You must go upstairs"
      + " and locate the trainer for each specific skill type.\n");
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
    write("Learning skills is not possible here. You must go upstairs"
      + " and locate the trainer for each specific skill type.\n");
    return 1;
} /* sk_hook_no_list_learn */
