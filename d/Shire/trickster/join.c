/*
 * /d/Shire/trickster/join.c
 *
 * This is the join room of the Trickster lay guild. You may join here.
 * Modified from the join room of the Rockfriend guild, created by
 *
 * /Mercade, 9 January 1994
 *
 *
 * Adapted from the Hobbit Race guild for use
 * in the Tricksters, a splinter of the former Hin Warrior guild
 * Dunstable March 23, 1995
 */

#pragma save_binary

inherit "/d/Shire/std/room";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "trickster.h"
#include "titles.h"
#include "/d/Shire/skills.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/bits.h"

#define STICK_ID        "_trickster_stick_"
#define START          (TRICK_DIR + "start")
#define LOG_SIZE       25000
#define KIT_ID   "trickster_disguise_kit"
#define NEW_BREE "/d/Shire/bree/rooms/town/"

//   Prototypes
void dest_stick(object player);
nomask public void remove_player_changed_race(object tp);

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

int nojoin;

/*
 * Function name: create_room
 * Description : Called when the room is first loaded into memory.
 */
nomask public void
create_shire_room()
{
    set_short("a dirty hole in the ground");
    set_long("This dirty hole in the ground is a known hangout "+
      "for the unsavory element in Bree.  A sign is the lone decoration "+
      "on the west wall, while the east wall is a solid wall of dirt.  Water "+
      "drips from the ceiling into a puddle on the floor.  South leads deeper "+
      "into the hole and up is the way out. A notice hangs from "+
      "the east wall.\n");

    add_item(({"notice"}),"It is quite readable.\n");

    add_item(({"hole","hole in the ground","hangout"}),
      "The hole in the ground that is this room is the headquarters "+
      "for the Trickster guild.\n");

    add_item(({"east wall"}),
      "The east wall is made of dirt as are all the other walls. There is a "+
      "notice affixed to it.\n");

    add_item(({"west wall"}),
      "The west wall is made of dirt as are all the other walls. There is a "+
      "notice affixed to it.\n");

    add_item(({"east wall"}),
      "The east wall is made of dirt as are all the other walls. There is a "+
      "sign attached to it.\n");
    add_item(({"notice", "sign", }),
      "There are some words written on it. Perhaps it can be read.\n");

    add_cmd_item( ({ "sign" }), ({ "read" }),
      "The sign reads:\n\n"+
      "\tTrickster Guild\n"+
      "\t---------------\n"+
      "\tIf you want, you may:\n"+
      "\t<trick everyone>  - enter the guild\n"+
      "\t<beg stick>       - beg for a new stick\n"+
      "\t<become crusader> - leave the guild.\n\n"+
      "\tThis will cost you your skills and accumulated experience\n"+
      "\tin the guild. Currently the guild tax is moderate for this guild.\n\n");

    add_cmd_item("notice","read",
        "The notice reads:\n\n"+
        "\tThe Tricksters do not favor those who follow crusades.\n" +
        "\tThey do not allow those who become more holy than sweet\n" +
        "\tor more evil than nasty to remain in their ranks. For the\n"+
        "\tprivileges gained in this guild are skills such as \n"+
        "\tawareness, club, trading, and appraise value. Later,\n"+
        "\ta few more things will arrive.\n\n");

    add_exit(NEW_BREE + "backroom", "up");
    add_exit(TRICK_DIR + "train", "south","@@check_member@@");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    create_guild_support();


    nojoin = 0; /* set to 1 if you wish joining to be disallowed */
}

int
check_member()
{

    object tp = this_player();

    if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
    {
	write("Only guildmembers are allowed past this point.\n");
	return 1;
    }
    return 0;
}

/*
 * Function name: init
 * Description  : When someone enters the room, the commands are linked
 *                to him/her.
 */
nomask public void
init()
{
    ::init();

    init_guild_support();

    add_action("do_try",   "trick");
    add_action("do_become", "become");
    add_action("beg",  "beg");
    add_action("do_list",  "list");
}

/*
 * Function name: log_guild
 * Description  : This function logs some actions of members of the guild.
 *                It uses a larger cycle than basically coded.
 * Arguments    : string text - the message to log.
 */
nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(TRICKSTER_GUILD_LOG) > LOG_SIZE)
    {
	rename(TRICKSTER_GUILD_LOG, (TRICKSTER_GUILD_LOG + ".old"));
    }

    write_file(TRICKSTER_GUILD_LOG, text);
}

/*
 * Function name: do_try
 * Description  : When a Trickster wants to join the guild, this function
 *                makes him/her a member.
 * Arguments    : string str - the command line argument.
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_try(string str)
{
    object tp = this_player();
    object shadow;
    object itch;
    string family;
    int    result;

    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " who?  Everyone? To join " +
	  "the guild, you must trick everyone.\n");
	return 0;
    }

    if(str != "everyone")
    {
	write("Trick "+str+" ? Are you insane?\n");
	return 1;
    }


    if (tp->query_race_name() == "elf")
    {
	write("We don't take elves, you better leave before we kill you.\n");
	return 1;
    }

    if ((tp->query_alignment() < TRICKSTER_GUILD_ALIGN_MIN) ||
      (tp->query_alignment() > TRICKSTER_GUILD_ALIGN_MAX))
    {
	write("You are obviously some kind of crusader! "+
	  "True Tricksters don't follow anyone but themselves.\n");
	return 1;
    }

    if (IS_MEMBER(tp))
    {
	write("Idiot! You're already a trickster. If you don't like it, "+
	  "leave.\n");
	return 1;
    }

    if (tp->query_guild_member(TRICKSTER_GUILD_TYPE))
    {
	write("You're already in a layman guild, stupid.\n");
	return 1;
    }

    if (!TP->query_prop("_i_can_join_the_tricksters"))
    {
	NF("You have to have a trickster vouch for you first!\n");
	return 0;
    }
    if (nojoin)
    {
	write("No new members are being accepted at this time, sorry.\n");
	return 1;
    }


    shadow = clone_object(TRICKSTER_GUILD_SHADOW);

    if ((result = shadow->shadow_me(tp, TRICKSTER_GUILD_TYPE,
	  TRICKSTER_GUILD_STYLE, TRICKSTER_GUILD_NAME)) != 1)
    {
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
	  " failed to add shadow with result " + result + ".\n");
	shadow->remove_shadow();

	write("Umm, we don't want you to join.  If you want to "+
	  "join still, leave a bug report.\n");

	return 1;
    }

    //    write("You seem to have a shadow...");
    write("You are a silly Trickster.\n");
    set_alarm(1.0,0.0,"init_me",tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
      TRICKSTER_GUILD_NAME + ".\n");

    clone_object(TRICKSTER_GUILD_OBJ)->move(tp, 1);
    clone_object(DISGUISE_KIT)->move(tp, 1);
    //    write("Getting stick...\n");
    write("The training master enters and hits you over the head with "+
      "a stick, which he hands to you, smiles and leaves.\n");
    say(QCTNAME(tp) + " is suddenly hit over the head with a stick by "+
      "someone you didn't notice standing here.\n");
    itch = clone_object(TRICK_DIR +"obj/itchy_scratchy.c");
    itch->move(tp, 1);
    itch->start_itching(tp);

    tp->clear_guild_stat(SS_LAYMAN);
    tp->set_guild_pref(SS_LAYMAN, TRICKSTER_GUILD_TAX);
    tp->add_cmdsoul(TRICKSTER_GUILD_SOUL);
    tp->update_hooks();
    tp->set_bit(FOURTH_GROUP,TRICKSTER_BIT);
    //   write("Adding cmdsoul...\n");
    return 1;
}

int
init_me(object ob)
{
    ob->init_lay_shadow();
    return 1;
}

/*
 * Function name: lower_skill
 * Description  : When a member leaves the guild or is kicked out due
 *                to a change of race, this function punishes him/her,
 *                removes the soul, shadow, etcetera.
 * Arguments    : object tp - the object leaving.
 */
nomask private int
lower_skill(object tp)
{
    int    result;

    if ((result = tp->remove_guild_lay()) != 1)
    {
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
	  " failed to remove shadow with result " + result + ".\n");

	tp->catch_msg("We'd like you to reconsider.  In fact, you cannot leave "+
	  "the guild at this time due to a bug.  Please leave a report.\n");

	return 0;
    }
    tp->set_guild_pref(SS_LAYMAN, 0);
    tp->clear_guild_stat(SS_LAYMAN);
    tp->remove_cmdlist(TRICKSTER_GUILD_SOUL);
    tp->clear_bit(FOURTH_GROUP,TRICKSTER_BIT);
    if (tp->query_skill(SS_DISGUISE))
	tp->remove_skill(SS_DISGUISE);
    if (tp->query_skill(SS_SET_TRAPS))
	tp->remove_skill(SS_SET_TRAPS);
    tp->update_hooks();
    tp->setup_skill_decay();

    /* If the player starts in the guild by default, set this to
    * the default starting location for all players.
    */
    if (tp->query_default_start_location() == START)
    {
	tp->set_default_start_location(tp->query_def_start());
    }

    set_alarm(2.0,0.0,&dest_stick(tp));

    MEMBER_TRACKER->remove_member(tp);
    return 1;
}

void
dest_stick(object player)
{
    object stick;

    stick = present(STICK_ID, player);
    if (objectp(stick))
    {
	stick->remove_object();
    }
    if (objectp(stick = present(KIT_ID, player)))
    {
	stick->remove_object();
    }
}

/*
* Function name: do_become
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_become(string str)
{
    object tp = this_player();
    object stick;

    if (str != "crusader")
    {
	notify_fail("Become what? A crusader?\n");
	return 0;
    }

    if (!IS_MEMBER(tp))
    {
	write("You cannot become a crusader since you already are!\n");
	return 1;
    }

    if (!lower_skill(tp))
	return 1;

    write("You are no longer a silly Trickster.\n");
    stick = present(STICK_ID, tp);
    if (objectp(stick))
    {
	stick->remove_object();
	write("The trainmaster arrives, grabs your stick from your hand "+
	  "and beats you over the head with it until it breaks.\n");
	say(QCTNAME(tp) + " has " + tp->query_possessive() +
	  " stick broken over "+tp->query_possessive()+" head.\n");
    }
    stick = present(KIT_ID, tp);
    if (objectp(stick))
    {
	stick->remove_object();
    }

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      TRICKSTER_GUILD_NAME + ".\n");

    return 1;
}

/*
* Function name: do_list
* Description  : This function allows people to list their (major) guilds.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int
do_list(string str)
{
    if (str != "guilds")
    {
	notify_fail("List what? Your guilds?");
	return 0;
    }

    str = this_player()->list_major_guilds();

    if (strlen(str))
    {
	write("You are a member of the following major guilds:\n" + str);
    }
    else
    {
	write("You are not a member of any major guild.\n");
    }

    return 1;
}

/*
* Function name: request
* Description  : Members who have lost their stick, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int
beg(string str)
{
    object tp = this_player();

    if (str != "stick")
    {
	notify_fail("Beg what? A new stick?\n");
	return 0;
    }

    if (!IS_MEMBER(tp))
    {
	write("You are not a member of this guild. You have no right to a " +
	  "stick, dummy.\n");
	return 1;
    }

    if (objectp(present(STICK_ID, tp)))
    {
	write("Oops, what's this? You already have a stick!  Idiot!\n");
	return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(TRICKSTER_GUILD_OBJ)->move(tp, 1);

    write("The trainmaster arrives, beats you over the head twice "+
      "with a large stick and hands it to you, scowling.\n");
    say(QCTNAME(tp)  + " is beaten about the head and shoulders "+
      "by the guild trainmaster.\n");

    return 1;
}

nomask public void
test_player_changed_race_with_delay(object player)
{
    set_alarm(5.0,0.0, &remove_player_changed_race(player));
}

/*
 * Function name: remove_player_changed_race
 * Description  : Whenever a member changes his/her race (s)he is
 *                mercilessly kicked out the guild by this function.
 * Arguments    : object tp - the object to kick out.
 */
nomask public void
remove_player_changed_race(object tp)
{
    // Don't check the dead.
    if (tp->query_ghost())
	return;
    if (tp->query_race_name() != "elf")
	return;

    tp->catch_msg("\nYou are an elf.  We don't like elves in " +
      "the " + TRICKSTER_GUILD_NAME + " at all. You are being " +
      "kicked out of the guild.\n");

    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

/*
 * Function name: remove_player_low_alignment
 * Description  : Whenever the alignment of a player is too low, the player
 *                is mercilessly kicked out the guild by this function.
 * Arguments    : object tp - the object to kick out.
 */
nomask public void
remove_player_low_alignment(object tp)
{
    tp->catch_msg("\nWhat do we have here, a crusader for evil?" +
      "We don't like crusaders in the " + TRICKSTER_GUILD_NAME + " at all. " +
      "You are being expelled from the guild.  Don't involve us in your "+
      "ridiculous crusades again.\n");

    lower_skill(tp);

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
}

/*
 * Function name: remove_player_low_alignment
 * Description  : Whenever the alignment of a player is too low, the player
 *                is mercilessly kicked out the guild by this function.
 * Arguments    : object tp - the object to kick out.
 */
nomask public void
remove_player_high_alignment(object tp)
{
    tp->catch_msg("\nWhat do you want to do, save the world?" +
      "We don't like crusaders in the " + TRICKSTER_GUILD_NAME + " at all. " +
      "You are being expelled from the guild.  Don't involve us in your "+
      "ridiculous crusades again.\n");

    lower_skill(tp);

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
}


/*
 * Function name: leave_inv
 * Description  : Called to remove the guild support if it is stuck.
 * Arguments    : object obj - the leaving object.
 *                object to  - the new destination of the object.
 */
nomask public void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);

    gs_leave_inv(obj, to);
}

/*
 * Stuff for meditation.
 */

/*
 * Function name: gs_hook_start_meditate
 * Description  : Gives a nice description when someone starts to meditate.
 */
nomask public void
gs_hook_start_meditate()
{
    write("Sitting down on the floor, you let the tranquil surroundings have " +
      "their effect on you. You close your eyes and find your mind floating " +
      "away from your body. Finally, you become as relaxed as possible and " +
      "feel yourself able to \"estimate\" your different preferences for " +
      "concentration and \"set\" them to new values if desired. To go back " +
      "to the world outside, all you have to do is \"rise\".\n");
    say(QCTNAME(this_player()) + " sits down in order to meditate.\n");
}

/*
 * Function name: gs_hook_rise
 * Description  : Gives a nice description when someone is done meditating.
 */
nomask public void
gs_hook_rise()
{
    write("Having reached a new peace with yourself, you feel relaxed and " +
      "ready to conquer the world. You open your eyes and stand up.\n");
    say("Looking quite relaxed indeed, " + QTNAME(this_player()) + " opens " +
      this_player()->query_possessive() + " eyes and stands up.\n");
}

/*
 * Function name: gs_hook_already_meditate
 * Description  : Gives a nice message when someone tries to meditate
 *                when (s)he is already mediating.
 */
nomask public int
gs_hook_already_meditate()
{
    write("It is not possible to come to an even higher level of meditation. " +
      "Since you are already meditating, you can now \"estimate\" your " +
      "different preferences for concentration and \"set\" them to new " +
      "values if you please. To relax and get back to the outside world, " +
      "just \"rise\".\n");
    return 1;
}

/*
 * Function name: gs_hook_catch_error
 * Description  : Gives a friendly error message when someone gives the
 *                wrong command while meditating.
 */
nomask public int
gs_hook_catch_error(string str)
{
    write("It is not possible to do that in your current state. Since you are " +
      "meditating, you can only \"estimate\" your different preferences for " +
      "concentration and \"set\" them to new values if you please. To relax " +
      "and get back to the outside world, just \"rise\".\n");
    return 1;
}


/*
 * Function name: cap
 * Description  : Map-function to capitalize strings.
 * Arguments    : string str - the string to capitalize.
 * Returns      : string - the capitalized string.
 */
string
cap(string str)
{
    return capitalize(str);
}
