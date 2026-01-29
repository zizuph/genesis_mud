/*
 * /d/Shire/herald/join.c
 *
 * This is the join room of the Herald lay guild. You may join here.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/herbsearch";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "../herald.h"
#include "/d/Shire/bits.h"

#define START          ("/d/Shire/herald/start")
#define LOG_SIZE       25000
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

#define OLD_CMDSOUL    "/d/Shire/herald/herald_soul"
#define OLD_SHADOW     "/d/Shire/herald/herald_shadow"
#define MANA_SHADOW    "/d/Genesis/specials/guilds/shadows/mana_shadow"

/*
 * Function name: create_room
 * Description : Called when the room is first loaded into memory.
 */
nomask public void
create_shire_room()
{

    set_short("The top of a grassy hill in Emyn Beraid");
    set_long("The top of this hill in the Tower Hills is very "+
        "peaceful and tranquil. A large stone has been placed "+
        "at its apex. Near the large stone, a small black pit "+
        "appears to be cut into the hillside. At the north end of the "+
        "hill, a tall maple tree rises over the horizon, while to the "+
        "south, a small sapling struggles to survive. A path "+
        "leads southeast down the hillside.\n");

    add_item(({"sapling","small sapling"}),
        "This small sapling appears to be of a mallorn tree.\n");
    add_item(({"pit","black pit","small black pit","hillside"}),
        "The only part on the hillside that is not green and pastoral is "+
        "this black pit, which seems to be a place where things are "+
        "burned regularly, for the grass around it does not even attempt "+
        "to grow back.\n");
    add_item(({"hill","apex"}),
        "The hill is a tall one even for hills, it is an effort to climb "+
        "it. The apex is also high, relative to the hill.\n");
    add_item(({"maple","tall maple tree","tree"}),
        "The tall maple tree to the north end of this hill looks as if it "+
        "has always grown here.  So wide it is at the top, that you "+
        "imagine its roots go to the very bowels of the earth.\n"+
        "The bark looks a little funny in one place.\n");
    add_item("bark","The bark seems to form the outline of a door.  Maybe "+
        "you could push or slide it open?\n");
    add_item(({"large stone","stone"}),
        "The large stone, placed at the apex of the hill is roughly obelisk "+
        "shaped and has an inscription carved in fine Sindar characters around "+
        "the sides.\n");
    add_item(({"inscription","runes","characters","sindarin"}),
        "The fine inscription has been etched carefully into the obelisk. "+
        " You may read it.\n");

    add_cmd_item("inscription","read","The inscription reads:\n\n"+
      "\tHere you may join the Heralds of the Valar if you are deemed\n"+
      "\tworthy. The entrance requirements are these:\n\n"+
      "\t\t * You must belong to a race created by Eru Illuvatar.\n"+
      "\t\t   That is, you must be a human, hobbit (or as referred\n" +
      "\t\t   to by Men, halfling), elf, Noldoli (gnome), or half-elf.\n"+
      "\t\t * Your must be of a heart that desires to follow the will \n"+
      "\t\t   of the Lords of the West and the Valar.\n\n"+
      "\tIf you wish to become a Herald of the Valar, the following will\n" +
      "\tbe necessary:\n\n"+
      "\t\t<serve the lords of the west> -> Joining.\n\n"+
      "\t\tOther options:\n\n"+
      "\t\t<ask new robe> -> To receive a new robe.\n"+
      "\t\t<betray valar> -> To leave the guild.\n\n"+
      "\tCurrently, the tax for this guild is moderate. Leaving will cost\n"+
      "\tyou the skills and spells you learned in this guild.\n");

    add_exit("/d/Shire/herald/path3","southeast");
    set_noshow_obvious(1);

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    create_guild_support();
    add_std_herbs("hill", 7228);
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

    if (file_size(HERALD_GUILD_LOG) > LOG_SIZE)
    {
	rename(HERALD_GUILD_LOG, (HERALD_GUILD_LOG + ".old"));
    }

    write_file(HERALD_GUILD_LOG, text);
}

/*
 * Function name: do_serve
 * Description  : When a Herald wants to join the guild, this function
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
        buffoon != "half-elf" && buffoon != "halfling" && 
        buffoon != "gnome")
    {
	write("Only the creations of Eru Illuvatar may serve the Valar.\n");
	return 1;
    }

    if (tp->query_guild_name_race() == "Drow race guild")
    {
	write("Only the creations of Eru Illuvatar may serve the Valar.\n");
	return 1;
    }

    if (tp->query_guild_name_occ() == "Angmar Army")
    {
	write("No members of the Army of Angmar may serve the Valar.\n");
	return 1;
    }

    if (tp->query_guild_name_lay() == "Angmar Army")
    {
	write("No members of the Army of Angmar may serve the Valar.\n");
	return 1;
    }

    if((tp->query_alignment() < 500))
    {
	write("Only those who are clearly devoted to the Song of " +
            "Illuvatar are welcome here. Repent and return when you are " +
            "pure of heart.\n");
	return 1;
    }

    if (IS_MEMBER(tp))
    {
        write("You are already a member.\n");
        return 1;
    }

    if (tp->query_guild_member(HERALD_GUILD_TYPE))
    {
	write("You still belong to another layman guild.\n");
	return 1;
    }

    shadow = clone_object(HERALD_GUILD_SHADOW);

    if ((result = shadow->shadow_me(tp, HERALD_GUILD_TYPE,
	  HERALD_GUILD_STYLE, HERALD_GUILD_NAME)) != 1)
    {
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
	  " failed to add shadow with result " + result + ".\n");
	shadow->remove_shadow();

	write("There was an error, you are not able to join at this "+
	  "time, please leave a bug report.\n");

	return 1;
    }

    write("You kneel in reverence to the Lords of the West. For a " +
        "moment there is silence, then you hear a rushing, as of water " +
        "cascading over a great cliff. Within your body you feel a heat " +
        "begin to rise, and a beautiful feminine voice caresses your " +
        "mind, saying 'You are now a Servant of the Secret Flame.' " +
        "Indeed, you can feel the flame burning inside you, and with " +
        "this perception you sense also that there is a great darkness " +
        "growing in the East that would extinguish that Flame forever. " +
        "Conviction pours through you and, through no power of your " +
        "own, you rise to your feet again.\n");
    say(QCTNAME(tp) + " kneels and closes " +HIS_HER(tp)+ " eyes. " +
        capitalize(HIS_HER(tp))+ " head suddenly tilts to the side, " +
        "as if listening to a faraway voice. Before your eyes, " +
        HE_SHE(tp)+ " is borne to " +HIS_HER(tp)+ " feet by an unseen " +
        "power. " +capitalize(HE_SHE(tp))+ " opens " +HIS_HER(tp)+ " eyes " +
        "and looks upon the world with new confidence.\n");
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
        HERALD_GUILD_NAME + ".\n");

    write("A magnificent elf arrives and gives you a flawless white robe.\n");
        say(QCTNAME(tp) + " is given a flawless white robe by a magnificent "+
        "elf.\n");

    tp->clear_guild_stat(SS_LAYMAN);
    tp->set_guild_pref(SS_LAYMAN, HERALD_GUILD_TAX);
    tp->set_bit(FOURTH_GROUP, HERALD_BIT);
    HERALD_MANAGER->add_member(tp);
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

    if (!objectp(tp))
        return 0;

    if ((result = tp->remove_guild_lay()) != 1)
    {
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
	  " failed to remove shadow with result " + result + ".\n");

	write("We'd like you to reconsider.  In fact, you cannot leave "+
	  "the guild at this time due to a bug.  Please leave a report.\n");

	return 0;
    }

    // Clear guild stat, remove guild learn, and begin skill decay
    tp->set_guild_pref(SS_LAYMAN, 0);
    tp->clear_guild_stat(SS_LAYMAN);
    tp->setup_skill_decay();

    // Remove the command soul
    tp->remove_cmdlist(HERALD_GUILD_SOUL);
    tp->clear_bit(FOURTH_GROUP, HERALD_BIT);
    tp->update_hooks();

    /* If the player starts in the guild by default, set this to
     * the default starting location for all players.
     */
    if (tp->query_default_start_location() == START)
    {
	tp->set_default_start_location(tp->query_def_start());
    }

    while (objectp(ob = present("_herald_robe_", tp)))
    {
	ob->remove_object();
    }

    while (objectp(ob = present("_shire_herald_prayerbook_", tp)))
    {
	ob->remove_object();
    }

    MEMBER_TRACKER->remove_member(tp);
    HERALD_MANAGER->remove_herald_corruption(tp);
    HERALD_MANAGER->remove_dark_lord_detection(tp);
    HERALD_MANAGER->remove_member(tp);
    return 1;
}

/*
 * Function name: do_betray
 * Description  : This is a waste of memory since no-one would ever
 *                consider leaving a guild like this, or would they?
 *                Just for the completeness, this function takes care
 *                of a voluntary leave.
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

    write("There is a pause, as if of disbelief or sudden pain, " +
        "then a lordly voice resounds in your head 'Go not forth! " +
        "For the hour is evil, and your road leads to sorrow that ye " +
        "do not forsee. No aid will the Valar lend you in this quest; " +
        "but neither will they hinder you; for this ye shall know: " +
        "as ye came hither freely, freely shall ye depart. The lies of " +
        "Morgoth thou shalt unlearn in bitterness.' With that, the voice " +
        "recedes, and with it dies the Secret Flame that burned once " +
        "within your breast. You are cast to the ground, weeping.\n");
    say(QCTNAME(tp)+ " pauses, as if listening to a far off voice. " +
        "Suddenly " +HE_SHE(tp)+ " is cast to the ground, weeping. " +
        "The pure white robe surrounding " +HIS_HER(tp)+ " body is " +
        "consumed in white flame.\n");

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
        HERALD_GUILD_NAME + ".\n");

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
 * Returns      : int 1/0    - success/failure.
 */
nomask static int
ask(string str)
{
    object tp = this_player();
    object robe;

    if ((str != "new robe"))
    {
	notify_fail("Ask for what? A new robe?\n");
	return 0;
    }

    if (!IS_MEMBER(tp))
    {
	write("The Valar do not grant requests to those who do not serve!\n");
	return 1;
    }


    if(str == "new robe")
    {
	if (objectp(robe = present("_herald_robe_",tp)) && 
	  (!robe->query_prop(OBJ_I_BROKEN)))
	{
	    write("You don't need two robes.\n");
	    return 1;
	}

	setuid();
	seteuid(getuid());

	robe->remove_object();
	clone_object(HERALD_GUILD_ITEM)->move(tp, 1);

	write("A magnificent elf arrives, and hands you a new robe.\n");
	say(QCTNAME(tp)  + " is given a new robe by a magnificent elf.\n");

	return 1;
    }

    return 1;

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
    if (!objectp(tp))
        return;
    tp->catch_tell("\nYou have changed races. Your race is not " +
        "one created or permitted by Eru Illuvatar. You are being " +
        "removed from the Heralds of the Valar.\n");
    set_alarm(0.1,0.0,&lower_skill(tp));
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
        tp->query_race_name() + ") was kicked out.\n");
}


/*
* Function name: remove_player_illegal_guild
* Description  : Whenever a member changes his/her guild to an illegal 
*                one, (s)he is mercilessly kicked out the guild by this 
*                function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void
remove_player_illegal_guild(object tp)
{
	if (!objectp(tp))
	    return;
	tp->catch_tell("\nYou are a member of an illegal guild. Your " +
            "other guild is not permitted by Eru Illuvatar. You are " +
            "being removed from the Heralds of the Valar.\n");
	set_alarm(0.1, 0.0, &lower_skill(tp));
	log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
	    tp->query_race_name() + ") was kicked out(illegal guild).\n");
}

void
do_valid_race_check(object player)
{
    string race_name;

    race_name = player->query_race_name();
    if (race_name != "human"  && race_name != "elf" && 
        race_name != "hobbit" && race_name != "half-elf" &&
        race_name != "halfling" && race_name != "gnome")
	remove_player_changed_race(player);
}

void
valid_race_check(object player)
{
    set_alarm(5.0, 0.0, &do_valid_race_check(player));
}

void
do_valid_guild_check(object player)
{
    if (player->query_guild_name_occ() == "Angmar Army")
    {
	remove_player_illegal_guild(player);
    }

    if (player->query_guild_name_lay() == "Angmar Army")
    {
	remove_player_illegal_guild(player);
    }
}

void
valid_guild_check(object player)
{
    set_alarm(5.0, 0.0, &do_valid_guild_check(player));
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
    tp->catch_tell("\nYou have gone back on your pledge to serve the " +
        "Light.  The Valar do not reward disfealty.  You are removed " +
        "from the Heralds of the Valar.\n");

    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
        tp->query_alignment() + ") was kicked out.\n");

    lower_skill(tp);
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

int
do_slide(string str)
{
    if (!str || !strlen(str)) {
       notify_fail("Slide what?\n");
	    return 0;
    }

    if ((str == "door") || (str == "bark door"))
    {
       if (!IS_MEMBER(this_player()))
       {
          notify_fail("You are not a member and are not allowed to enter.\n");
	       return 0;
       }

	write("The door slides open easily and you go in.\n");
	say(QCTNAME(TP)+ " slides the bark door open and enters the tree.\n");
	TP->move_living("M","/d/Shire/herald/herb",1);
	tell_room(("/d/Shire/herald/herb"),
	    QCTNAME(TP)+" comes crawling into the tree.\n",TP);
	return 1;
    }
    write("Slide what? A "+str+"? You must be kidding!\n");
    return 1;
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
    add_action(do_slide,    "slide");
    add_action(do_slide,    "push");
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
//    tp->do_die(TO);
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
//	    player->do_die(this_object());
	}  
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
	  player->query_race_name() + ") was punished by Varda.\n");

	return 1;
    }

    if(ran > 7)
    {
	player->catch_tell("Ulmo looks upon you from afar and you feel his wrath.\n");
	player->add_fatigue(-100);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
	  player->query_race_name() + ") was punished by Ulmo.\n");

	return 1;
    }

    if((ran < 3) || (ran2 < 3))
    {
	player->catch_tell("You feel an intense gaze coming from the Undying Lands.\n"+
	  "You feel very very afraid.\n");
	player->command("drop all");
	player->add_panic(150);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + " (race " +
	  player->query_race_name() + ") was punished by Lorien.\n");

	return 1;
    }
}

void
convert_new_code(object ob)
{
    object *emblem, *book, guild, mana;
    int    g_error, m_error, s_soul, g_soul;

    if(IS_MEMBER(ob) && !(HERALD_MANAGER->query_is_member(ob)))
    {
        HERALD_DEBUG("Old Herald code - convert " +QTNAME(ob)+ 
            " over to new code.\n");

        setuid();
        seteuid(getuid());

        emblem = filter(all_inventory(ob), &operator(>)(,-1) @
                    &member_array("_herald_robe_", ) @ 
                    &->query_names());

        book = filter(all_inventory(ob), &operator(>)(,-1) @
                    &member_array("_shire_herald_prayerbook_", ) @ 
                    &->query_names());


        if (sizeof(emblem))
        {
            foreach(object item: emblem)
            {
                item->remove_object();
            }
        }

        if (sizeof(book))
        {
            foreach(object item: book)
            {
                ob->catch_msg("You discard your leather prayer " +
                    "book. You are not sure why you ever needed it.\n");
                item->remove_object();
            }
        }

        OLD_CMDSOUL->remove_spells(ob);
        ob->remove_cmdsoul(OLD_CMDSOUL);
        ob->update_hooks();

        ob->remove_guild_lay();

        guild = clone_object(HERALD_GUILD_SHADOW);
        mana = clone_object(MANA_SHADOW);

        if ((g_error = guild->shadow_me(ob, HERALD_GUILD_TYPE, 
            HERALD_GUILD_STYLE, HERALD_GUILD_NAME)) > 0 && 
            (m_error = mana->shadow_me(ob)) > 0 &&
            (g_soul = ob->add_cmdsoul(HERALD_GUILD_SOUL)) &&
            (s_soul = ob->add_cmdsoul(SPELL_MANAGER_SOUL)))
        {
            HERALD_MANAGER->add_member(ob);
            ob->update_hooks();
            write_file(HERALD_LOGS + "herald_transfer", ctime(time()) + 
                " " + ob->query_real_name() + " has successfully " +
                "transferred to the new guild.\n");
            return;
        }
        else
        {
            write_file(HERALD_LOGS + "herald_transfer", ctime(time()) + 
                " " + ob->query_real_name() + " has failed to transfer, " +
                "guild shadow returned: " + g_error + " and mana shadow " +
                "returned: " + m_error + " guild soul returned: " + 
                g_soul + " and spell manager soul " + "returned: " + 
                s_soul + "\n");
            ob->catch_msg("Something went wrong, contact " +
                implode(HERALD_GUILD_MASTER, ", ") + " to report the " +
                "issue.\n");
        }  
  
        HERALD_DEBUG("Old Herald code - convert " +QTNAME(ob)+ 
            " over to new code - skipped checks.\n");
        return;
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && !(ob->query_wiz_level()))
    {
       set_alarm(0.3,0.0, &convert_new_code(ob));

    }
}
