/*
 *  /d/Shire/guild/dunlinde/join.c
 *
 *  This is the join room of the Dunlinde Occ guild.
 *  Here functions are called to enter and eject a player.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/dunlinde/dunlinde.h"
#include "/d/Shire/bits.h"

#define START          (LINDE_DIR + "start")
#define LOG_SIZE       25000


#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))


/*
 * Function name: create_room
 * Description : Called when the room is first loaded into memory.
 */
nomask public void
create_shire_room()
{
    set_short("The Dunlinde Join room");
    set_long("The Dunlinde Join room.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    create_guild_support();
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

    if (file_size(LINDE_GUILD_LOG) > LOG_SIZE)
    {
	rename(LINDE_GUILD_LOG, (LINDE_GUILD_LOG + ".old"));
    }

    write_file(LINDE_GUILD_LOG, text);
}

/*
 * Function name: do_serve
 * Description  : When an Dunlinde wants to join the guild, this function
 *                makes him/her a member.
 * Arguments    : string str - the command line argument.
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_serve(string str)
{
    object tp = this_player();
    object shadow;
    string family;
    int    result;

    string buffoon;

    buffoon = tp->query_race_name();
    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " whom?\n");
	return 0;
    }

    if (str != "the lords of the west")
    {
	write("Serve whom?\n");
	return 1;
    }


    if (buffoon != "human" && buffoon != "elf" && buffoon != "hobbit" && 
        buffoon != "half-elf" && buffoon != "gnome" && tp->query_wiz_level() < 1)
    {
	write("You don't have a singing voice worthy of praising the Valar.\n");
	return 1;
    }

    if (tp->query_wiz_level() < 1 && tp->query_guild_name_race() == "Drow race guild")
    {
	write("You are incapable of serving both Lolth and the Valar.\n");
	return 1;
    }

    if (tp->query_wiz_level() < 1 && tp->query_alignment() < 400)
    {
	write("Only those who are clearly devoted to the Song of Illuvatar are "+
	  "welcome here.\n");
	return 1;
    }

    if (IS_MEMBER(tp))
    {
	write("You are already a member.\n");
	return 1;
    }

    if (tp->query_wiz_level() < 1 && tp->query_guild_member(LINDE_GUILD_TYPE))
    {
	write("You still belong to another occupational guild.\n");
	return 1;
    }

/*
    if (!(tp->query_prop("_i_can_join_the_dunlinde")))
    {
	write("You need to find an Dunlinde willing to vouch for you, for you "+
	  "to join the guild.\n");
	return 1;
    }
*/

    shadow = clone_object(LINDE_GUILD_SHADOW);

    if ((result = shadow->shadow_me(tp, LINDE_GUILD_TYPE,
	  LINDE_GUILD_STYLE, LINDE_GUILD_NAME)) != 1)
    {
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
	  " failed to add shadow with result " + result + ".\n");
	shadow->remove_shadow();

	write("There was an error, you are not able to join at this "+
	  "time, please leave a bug report.\n");

	return 1;
    }
    shadow->init_occ_shadow();

    write("You kneel, and join the Dunlinde.\n");
    say(QCTNAME(tp) + " kneels and closes " +HIS_HER(tp)+ " eyes. " +
      capitalize(HIS_HER(tp))+ " head suddenly tilts to the side, " +
      "as if listening to a faraway voice. Before your eyes, " +
      HE_SHE(tp)+ " is borne to " +HIS_HER(tp)+ " feet by an unseen " +
      "power. " +capitalize(HE_SHE(tp))+ " opens " +HIS_HER(tp)+ " eyes " +
      "and looks upon the world with new confidence.\n");
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
      LINDE_GUILD_NAME + ".\n");

    write("A magnificent elf arrives and gives you a flawless white robe.\n");
    say(QCTNAME(tp) + " is given a flawless white robe by a magnificent "+
      "elf.\n");

    write("The magnificent elf gives you a leather prayer book.\n");
    say(QCTNAME(tp)+ " is given a leather prayer book.\n");

    tp->clear_guild_stat(SS_OCCUP);
    tp->set_guild_pref(SS_OCCUP, LINDE_GUILD_TAX);
//  tp->set_bit(FOURTH_GROUP,LINDE_BIT);
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

    int result;
    object ob;

    if ((result = tp->remove_guild_occ()) != 1)
    {
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
	  " failed to remove shadow with result " + result + ".\n");

	write("We'd like you to reconsider.  In fact, you cannot leave "+
	  "the guild at this time due to a bug.  Please leave a report.\n");

	return 0;
    }
    tp->set_guild_pref(SS_OCCUP, 0);
    tp->clear_guild_stat(SS_OCCUP);
    tp->remove_cmdlist(LINDE_GUILD_SOUL);
//    tp->clear_bit(FOURTH_GROUP,LINDE_BIT);
    tp->update_hooks();
    tp->setup_skill_decay();

    /* If the player starts in the guild by default, set this to
     * the default starting location for all players.
     */
    if (tp->query_default_start_location() == START)
    {
	tp->set_default_start_location(tp->query_def_start());
    }

    while (objectp(ob = present("_linde_robe_", tp)))
    {
	ob->remove_object();
    }
    while (objectp(ob = present("_linde_book_", tp)))
    {
	ob->remove_object();
    }
    MEMBER_TRACKER->remove_member(tp);
    return 1;

}

/*
 * Function name: do_betray
 * Description  : This func allows a player to leave.
 * Arguments    : string str - the command line argument
 * Returns      : int    1/0 - success/failure.
 */
nomask static int
do_betray(string str)
{
    object tp = this_player();
    int    result;

    if (str != "valar")
    {
	notify_fail("Betray whom?\n");
	return 0;
    }

    if (!IS_MEMBER(tp))
    {
	write("You cannot leave a guild when you are not a member!\n");
	return 1;
    }

    if (!lower_skill(tp))
	return 1;

    write("You leave the Dunlinde.\n");
    say(QCTNAME(tp)+ " leaves the Dunlinde.\n");

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      LINDE_GUILD_NAME + ".\n");

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
	NF("List what? Your guilds?\n");
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
 * Function name: ask
 * Description  : Members who have lost their objects, may get them back here.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1 or 0    - success or failure.
 */
nomask static int
ask(string str)
{

/*
    object tp = this_player();
    object robe;


    if ((str != "new robe") && (str != "new book"))
    {
	notify_fail("Ask for what? A new robe or a new book?\n");
	return 0;
    }

    if (!IS_MEMBER(tp))
    {
	write("The Valar do not grant requests to those who do not serve!\n");
	return 1;
    }


    if(str == "new robe")
    {

	if (objectp(robe = present("_linde_robe_",tp)) && 
	  (!robe->query_prop(OBJ_I_BROKEN)))
	{
	    write("You don't need two robes.\n");
	    return 1;
	}

	setuid();
	seteuid(getuid());

	robe->remove_object();
	clone_object(LINDE_GUILD_OBJ)->move(tp, 1);

	write("A magnificent elf arrives, and hands you a new robe.\n");
	say(QCTNAME(tp)  + " is given a new robe by a magnificent elf.\n");

	return 1;

    }

    if (objectp(present("_linde_book_", tp)))
    {
	write("You don't need two songbooks.\n");
	return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(LINDE_GUILD_SPELLS)->move(tp, 1);

    write("A magificent elf arrives, and hands you a songbook.\n");
    say(QCTNAME(tp)  + " is given a new songbook by a magnificent elf.\n");

    return 1;
*/

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
    tp->catch_tell("\nYou have changed races.  Your race is not " +
      "one albe to sing in praise to the Valar.  You are being removed " +
      "from the Dunlinde.\n");
//    set_alarm(0.1,0.0,lower_skill(tp));
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

void
do_valid_race_check(object player)
{
    string race_name;

    race_name = player->query_race_name();
    if (race_name != "human"  && race_name != "elf" && 
        race_name != "hobbit" && race_name != "half-elf" &&
        race_name != "gnome")
	remove_player_changed_race(player);
}

void
valid_race_check(object player)
{
    set_alarm(5.0, 0.0, &do_valid_race_check(player));
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
    tp->catch_tell("\nYou have gone back on your pledge to serve the "+
      "Light.  The Valar do not reward disfealty.  You are removed from "+
      "The Dunlinde.\n");

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
//    lower_skill(tp);
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

    add_action(do_serve,    "serve");
    add_action(do_betray,   "betray");
    add_action(ask,         "ask");
    add_action(do_list,     "list");
}

nomask public void
angry_valar(object tp)
{
    tp->catch_tell("\n \nYou have disappointed Manwe Sulimo.\n" +
      "Feel his wrath, and know that you are forsaken!\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " was removed from "+
      "the guild by the Valar.\n");
    tp->catch_tell("\nA thunderbolt rains down from the sky.\n");
    tp->catch_tell("It smites you in the forehead, and all goes black.\n");
    tp->heal_hp(-tp->query_max_hp());
    tp->do_die(TO);
    return;
}

nomask public int
valar_wrath(object player)
{
    int ran, ran2;

    ran = random(10);
    ran2 = random(10);

    if(ran + ran2 > 15)
    {
	set_alarm(3.0,0.0, &angry_valar(player));
	return 1;
    }

    if(ran2 < 9)
    {
	player->catch_tell("You are stung by the angry gaze of Varda.\n");
	player->heal_hp(-100);
	if (player->query_hp() <= 0)
	{
	    player->do_die(this_object());
	}  
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
	  player->query_race_name() + ") was punished by Varda.\n");

	return 1;
    }

    if(ran > 7)
    {
	player->catch_tell("Ulmo looks upon you from afar and you feel his wrath.\n");
	player->add_fatigue(-600);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
	  player->query_race_name() + ") was punished by Ulmo.\n");

	return 1;
    }

    if((ran < 3) || (ran2 < 3))
    {
	player->catch_tell("You feel an intense gaze coming from the Undying Lands.\n"+
	  "You feel very very afraid.\n");
	player->command("drop all");
	player->add_panic(550);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
	  player->query_race_name() + ") was punished by Lorien.\n");

	return 1;
    }
}
