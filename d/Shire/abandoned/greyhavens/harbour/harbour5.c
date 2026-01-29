/*

 Join room for Sinda racial guild, based on Hobbit join room
 Palmer Dec 18, 2003

 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/guild/sindar_rac/sindar_rac.h"
#include "/d/Shire/greyhavens/local.h"
#include "/d/Shire/sys/defs.h"
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

inherit "/d/Gondor/common/room";
//inherit "/lib/guild_support";
inherit BUILDING_BASE;

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define DEBUG_WIZ "palmer"

/*
* Global variables.
*
* The mapping members has the names of the players as indices and the
* values are an array with two elements, the family name of the player
* and the date the player joined.
*/
private mapping members;
//static private string *titles = TITLES;

//   Prototypes
void dest_circlet(object player);
void remove_from_list(string player);


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
   
   if (file_size(SINDAR_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(SINDAR_RACE_GUILD_LOG, (SINDAR_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(SINDAR_RACE_GUILD_LOG, text);
}


public int
query_is_member(string name)
{
   if(members[name])
   {
         return 1;
   }

   return 0;
}

/*
* Function name: create_guild_room
*/
void create_guild_room()
{
    set_short("A sparse clearing in the forest.");
    set_long("This is the ceremonial joining area of the Sindar guild. " +
        "A pedestal stands in the center.\n");
    add_item("pedestal",
        "The pedestal is made of wood. The top has words engraved on it.\n");

   add_prop(ROOM_I_INSIDE,          0);
   add_prop(ROOM_I_NO_CLEANUP,      1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

   setuid();
   seteuid(getuid());

    restore_object(SINDAR_RACE_GUILD_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }

    add_exit(GH_HARBOUR_DIR +  "harbour2.c", "west", 0, 1, 1);
    add_exit(GH_HARBOUR_DIR +  "harbour6.c", "north", 0, 1, 1);

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
   
   add_action("do_try",   "declare");
   add_action("do_break", "abandon");
   add_action("request",  "request");
}


/*
* Function name: do_try
* Description  : When a elf wants to join the guild, this function
*                makes him/her a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_try(string str)
{
    object tp = this_player();
    object shadow;
    int    result;
   
    if (!strlen(str) || str !="race as sindar")
    {
        notify_fail("Declare your race as what? That's not possible.\n");
        return 0;
    }   

    if (tp->query_race() != "elf")
    {
        write("You are not a elf. You may not join.\n");
    return 1;
    }

// check if player is a member already
    if (IS_MEMBER(tp))
    {
        write("You are already a Sindar. If you have lost your " +
            "items, you may get a new ones using <request " +
            "bracelet>.\n");
    return 1;
    }

    if(tp->query_alignment() <= SINDAR_RACE_GUILD_ALIGN)
    {
        write("Your past actions prevent you from becoming a " +
          "Sindar. When you have improved yourself, you may try " +
          "again.\n");
    return 1;
    }

    if (IS_MEMBER(tp))
    {
        write("You are already a Sindar. If you have lost your " +
            "items, you may get a new ones using <request " +
            "circlet>.\n");
    return 1;
    }
   
    if (tp->query_guild_member(SINDAR_RACE_GUILD_TYPE))

    {
        write("You cannot be a member of two racial guilds at " +
            "a time.\n");
    return 1;
    }

    shadow = clone_object(SINDAR_RACE_GUILD_SHADOW);
   
    if ((result = shadow->shadow_me(tp, SINDAR_RACE_GUILD_TYPE,
               SINDAR_RACE_GUILD_STYLE, SINDAR_RACE_GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
            " failed to add shadow with result " + result + ".\n");
        shadow->remove_shadow();
        write("The magic of the Sindar has failed. Please leave a " +
            "bug report in this room.\n");
    return 1;
    }
   
    set_alarm(3.0,0.0,"init_me",tp);

// logs the join
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
        SINDAR_RACE_GUILD_NAME + ".\n");

// creates the guild item   
    clone_object(SINDAR_RACE_GUILD_CIRCLET)->move(tp, 1);

// joining message
    write("The room begins to fill with bright " +
       "light. It surrounds you, enveloping you in " +
       "pure white light. A circlet appears in your hand. A " +
       "warm voice in your mind says to you \"Welcome home. \" " +
       "The light slowly diminishes, leaving you with a warm glow.\n");
    say("The room begins to fill with bright light. " +
       "It surrounds " + QTNAME(tp) + ", enveloping " + 
       HIM_HER(tp) + " in pure white light. The light slowly " + 
       "diminishes, surrounding " + HIM_HER(tp) + " with a soft glow.\n");
   
    tp->clear_guild_stat(SS_RACE);
    tp->set_guild_pref(SS_RACE, SINDAR_RACE_GUILD_TAX);
    tp->add_cmdsoul(SINDAR_RACE_GUILD_SOUL);
    tp->update_hooks();
    tp->set_race_name("grey-elf");
    members[tp->query_real_name()] = ({tp->query_age(), time() });

    save_object(SINDAR_RACE_GUILD_SAVE);

    return 1;
}


int init_me(object ob)
{
    ob->init_race_shadow();
    return 1;
}

/*
* Function name: lower_skill
* Description  : When a member leaves the guild or is kicked out due
*                to a change of race, this function punishes him/her,
*                removes the soul, shadow, etcetera.
* Arguments    : object tp - the object leaving.
*/
nomask private void
lower_skill(object tp)
{
    object circlet;
   
    tp->set_guild_pref(SS_RACE, 0);
    tp->clear_guild_stat(SS_RACE);
    tp->remove_cmdsoul(SINDAR_RACE_GUILD_SOUL);
    tp->update_hooks();
// resets player back to a boring elf
//    tp->reset_race_name();
    tp->setup_skill_decay();
   
   /* If the player starts in the guild by default, set this to
   * the default starting location for all players.
   */
    if (tp->query_default_start_location() == START)
    {
        tp->set_default_start_location(tp->query_def_start());
    }
   
    set_alarm(2.0,0.0,&dest_circlet(tp));
    {
        circlet->remove_object();
    }
       
   /* Remove him/her from the list of members.
   */
    members = m_delete(members, tp->query_real_name());
   
    setuid();
    seteuid(getuid());
   
    save_object(SINDAR_RACE_GUILD_SAVE);
}

void remove_from_list(string player)
{
    player = lower_case(player);
    members = m_delete(members,player);
    setuid(); seteuid(getuid());
    save_object(SINDAR_RACE_GUILD_SAVE);
}

void dest_circlet(object player)
{
    object circlet;
   
    circlet = present(CIRCLET_ID, player);
    if (objectp(circlet))
    {
        circlet->remove_object();
    }
}

/*
* Function name: do_break
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_break(string str)
{
    object tp = this_player();
    object circlet;
    int    result;
   
    if (str != "sindar")
    {
        notify_fail("Abandon who? The Sindar?\n");
        return 0;
    }
   
    if (!IS_MEMBER(tp))
    {
        write("You cannot abandon the Sindar since you were never " +
            "one.\n");
    return 1;
    }
   
    if ((result = tp->remove_guild_race()) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
            " failed to remove shadow with result " + 
            result + ".\n");
      
        write("You are unable leave the Sindar. Please leave a " +
            "bugreport in this room about this. Thanks.\n");
    return 1;
    }
   
// starts skill decay   
    lower_skill(tp);

// remove the circlet  
    circlet = present(CIRCLET_ID, tp);

    if (objectp(circlet))
    {
        circlet->remove_object();
        write("A dark cloud passes overhead, blocking the " +
            "light. Suddenly, a strange feeling begins to leave " +
            "you, and before long, the white aura surrounding " +
            "you dissipates and flickers out for good. Your " +
            "bright circlet catches fire and burns, leaving " +
            "nothing behind but a wisp of smoke. A saddened " +
            "voice whispers in your mind, 'You shall be missed.\n" +
            "Farewell.'" +
            "\n\nThen nothing.\n");

        say("A dark cloud passes overhead, blocking the light. " +
            "Suddenly, " + QTNAME(TP) + "'s face drains. The " +
            "white light that surrounded " + HIM_HER(tp)+ 
            " fades away and winks out. "+CAP(HIS_HER(TP))+
            " circlet catches fire and burns, leaving nothing " +
            "but a wisp of smoke.\n");

    }
   
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
        SINDAR_RACE_GUILD_NAME + ".\n");
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
        notify_fail("List what? Your guilds?\n");
    return 0;
    }
   
    str = this_player()->list_major_guilds();
   
    if (strlen(str))
    {
        write("You are a member of the following major " +
            "guilds:\n" + str);
    }
    else
    {
        write("You are not a member of any major guild.\n");
    }
    return 1;
}

/*
* Function name: request
* Description  : Members who have lost their circlet, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int request(string str)
{
    object tp = this_player();
   
    if (str != "circlet")
    {
        notify_fail("Request what? A new circlet?\n");
    return 0;
    }
   
    if (!IS_MEMBER(tp))
    {
        write("You are not a member of this guild. You have no " +
            "right to a circlet.\n");
    return 1;
    }
   
    if (objectp(present(CIRCLET_ID, tp)))
    {
        write("You already have a circlet. You don't need two.\n");
    return 1;
    }
   
    setuid();
    seteuid(getuid());
   
    clone_object(SINDAR_RACE_GUILD_CIRCLET)->move(tp, 1);
   
    write("A new circlet appears before you. You reach out and " +
       "take it.\n");
    say(QCTNAME(tp)  + " stretches out " + HIS_HER(tp) + " hand " +
       "and takes a circlet floating in the air.\n");
   
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
    tp->catch_msg("\nYou are no longer an elf, therefore you " +
        "do not belong in the " + SINDAR_RACE_GUILD_NAME + 
        " anymore. You are being expelled from the guild.\n");
   
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
    tp->catch_msg("\nIt seems the shadow of the Dark Lord has " +
        "grown within you. The Sindar shun all that is evil. " +
        "This means you can no longer be counted as a " + 
        SINDAR_RACE_GUILD_NAME + ".\n\n" +
        "Your circlet bursts into flames, leaving behind a wisp " +
        "of smoke. \n");
   
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
        tp->query_alignment() + ") was kicked out.\n");
}

/*
 * Function name: remove_player_inactive
 * Description: This is called when a player has been removed from the
 *              guild for inactivity.
 * Arguments:   object tp - the object to kick out.
*/
nomask public void
remove_player_inactive(object tp)
{
    tp->catch_tell("You have been inactive for too long. You are no " +
        "longer counted as a " + SINDAR_RACE_GUILD_NAME + ".\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (inactive) " +
        "was kicked out.\n");
}


/*
* Function name: leave_inv
* Description  : Called to remove the guild support if it is stuck.
* Arguments    : object obj - the leaving object.
*                object to  - the new destination of the object.
*/
/*
nomask public void leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
   
    gs_leave_inv(obj, to);
}
*/


/*
* Function name: test_members
* Description  : At the first of the month, we test whether all members
*                listed are still valid. Ie. players who have quit will
*                be kicked out of the list.
*/
nomask static void
test_members()
{
   string *names = m_indices(members);
   int    index = -1;
   int    size = sizeof(names);
   
   setuid();
   seteuid(getuid());
   
   while(++index < size)
   {
      if (!(SECURITY->exist_player(names[index])))
         {
         log_guild(ctime(time()) +
            sprintf(" %-11s is no longer a player. -> removed.\n",
               capitalize(names[index])));
         
         members = m_delete(members, names[index]);
         }
   }
   
   save_object(SINDAR_RACE_GUILD_SAVE);
}


nomask public void
angry_valar(object tp)
{
    tp->catch_tell("\n\nYour actions are not inline with " +
        "acceptable Sindar behaviour.\n" +
        "You are no longer a Sindar!\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " booted from Sindar.\n");
//    tp->catch_tell("\nYour circlet catches fire and melts before your eyes..\n");
//    tp->catch_tell("It smites you in the forehead, and all goes black.\n");
//    tp->heal_hp(-tp->query_max_hp());
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
	player->catch_tell("Your foolishness has cost you dearly.\n");
	player->heal_hp(-1000);
	if (player->query_hp() <= 0)
	{
//	    player->do_die(this_object());
        player->heal_hp(random(10));
	}
	log_guild(ctime(time()) + " " + WRITE_NAME(player) +
        " was punished-health.\n");

	return 1;
    }

    if(ran > 7)
    {
	player->catch_tell("Your foolishness has cost you dearly.\n");
	player->add_fatigue(-100);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + 
        " was punished-fatigue.\n");

	return 1;
    }

    if((ran < 3) || (ran2 < 3))
    {
	player->catch_tell("Your foolishness has cost you dearly.\n");
	player->command("drop all");
	player->add_panic(150);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + 
        " was punished-panic/drop all.\n");

	return 1;
    }
}
