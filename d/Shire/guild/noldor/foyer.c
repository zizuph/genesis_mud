/*
 *  This is the joining room for the noldor. It is based on numerous 
 *  join rooms in the Shire such as the Rockfriends, the hobbits, 
 *  and others.
 *
 *  Since Noldor are such a rare sight in ME, the guild limits the number
 *  of players that may join. Members that are inactive for 
 *  NOLDOR_RACE_GUILD_INACTIVE days will be automatically removed each time the
 *  game reboots. When removed members log on, their circlet melts before 
 *  their eyes as a notification they have been removed. They may join again 
 *  if there is room.
 *
 *  Thanks to Rhyn for developing the code to purge inactive members.
 *  -- Finwe, June 2001
 *
 *  Blocked shadow union elves from joining
 *  -- Finwe, December 2004
 *  
 * Removed limit on number of Noldor
 * -- Finwe, Feruary 2019
 */

#pragma save_binary
#pragma strict_types

#include "noldor.h"
#include "/d/Shire/rivendell/local.h"
#include "/d/Shire/sys/defs.h"
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

inherit "/d/Gondor/common/room";
inherit BUILDING_BASE;

#define INACTIVE(x, y) \
        ( ( (MAX( ( ((y)-(x))/60/60/24 ), 0)) > NOLDOR_RACE_GUILD_INACTIVE ) )
#define DEBUG_WIZ "finwe"

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
void test_members();


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
   
   if (file_size(NOLDOR_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(NOLDOR_RACE_GUILD_LOG, (NOLDOR_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(NOLDOR_RACE_GUILD_LOG, text);
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
* Functio name: create_room
* Description : Called when the room is first loaded into memory.
*/
void create_guild_room()
{
    set_short("A beautiful foyer");
    set_long("This is the foyer of the Noldor guild. The " +
	    "walls are polished and reflect light from the lamps " +
		"and @@daylight_desc@@ flowing in through the entrance. A " +
		"pedestal holding a large book is off to one side of " +
		"the room. Three arches lead further into the guild " +
        "with the fourth arch leading outside.\n");
    add_item("entrance",
        "It is an intricately arch leading out of the guild.\n");
    add_item("pedestal", 
        "The pedestal is made of wood and leafed with mithril. " +
		"It has been polished to a bright shine and is in the " +
		"shape of a tree. A great book rests on top of it.\n");
    add_item(({"window", "windows"}),
        "There are no windows in the foyer.\n");
    set_extra_wall("Four arches are set into the walls.");
    
    room_add_object("/d/Shire/guild/noldor/obj/join_book");

//	clone_object("/d/Shire/guild/noldor/obj/join_book")->move(TO);
//	clone_object(NOLGLD_DIR + "join_book")->move(TO);
 
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_CLEANUP,      1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
//   create_guild_support();
   
   setuid();
   seteuid(getuid());
   
    restore_object(NOLDOR_RACE_GUILD_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }
   
    add_exit(NOLGLD_DIR + "board_rm", "north", "@@check_member@@");
    add_exit(VALLEY_DIR + "stone_seat", "south");
    add_exit(NOLGLD_DIR + "start_rm", "east", "@@check_member@@");
    add_exit(NOLGLD_DIR + "train", "west","@@check_member@@");
    test_members();
}

int
check_member()
{
   object tp = this_player();
   
   if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
      {
      write("Only Noldor are allowed past this point.\n");
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
   
    if (!strlen(str) || str !="race as noldor")
    {
        notify_fail("Declare your race as what? That's not possible.\n");
        return 0;
    }   

    if (tp->query_race() != "elf")
    {
        write("You are not a elf. You may not join.\n");
    return 1;
    }

    if(tp->query_guild_name_occ() == "Union of the Warriors of Shadow")
    {
        write("Your chaotic behaviour displeases the Noldor; they refuse " +
            "to acknowledge you.\n");
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(TP) + " tried joining as a SU.\n");
        return 1;
    }

// check if player is a member already
    if (IS_MEMBER(tp))
    {
        write("You are already a Noldor. If you have lost your " +
            "items, you may get a new ones using <request " +
            "circlet>.\n");
    return 1;
    }

// check limit
/*
    if (m_sizeof(members) >= GUILD_LIMIT)
    {
        write("I'm sorry, but the Noldor guild is full and is not " +
        "accepting new members. Perhaps there will be an " +
        "opening in a day or two, so be sure to check back " +
        "regularly.\n");
        return 1;
     }
*/
    if(tp->query_alignment() <= NOLDOR_RACE_GUILD_ALIGN)
    {
        write("Your past actions prevent you from becoming a " +
          "Noldor. When you have improved yourself, you may try " +
          "again.\n");
    return 1;
    }
   
    if (IS_MEMBER(tp))
    {
        write("You are already a Noldor. If you have lost your " +
            "items, you may get a new ones using <request " +
            "circlet>.\n");
    return 1;
    }
   
    if (tp->query_guild_member(NOLDOR_RACE_GUILD_TYPE))

    {
        write("You cannot be a member of two racial guilds at " +
            "a time.\n");
    return 1;
    }

    shadow = clone_object(NOLDOR_RACE_GUILD_SHADOW);
   
    if ((result = shadow->shadow_me(tp, NOLDOR_RACE_GUILD_TYPE,
               NOLDOR_RACE_GUILD_STYLE, NOLDOR_RACE_GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to add shadow with result " + result + ".\n");
        shadow->remove_shadow();
        write("The magic of the Noldor has failed. Please leave a " +
            "bug report in this room.\n");
    return 1;
    }
   
    set_alarm(3.0,0.0,"init_me",tp);

// logs the join
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " joined the " +
        NOLDOR_RACE_GUILD_NAME + ".\n");

// creates the guild item   
    clone_object(NOLDOR_RACE_GUILD_CIRCLET)->move(tp, 1);

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
    tp->set_guild_pref(SS_RACE, NOLDOR_RACE_GUILD_TAX);
    tp->add_cmdsoul(NOLDOR_RACE_GUILD_SOUL);
    tp->update_hooks();
// changes descr to a noldo elf.
//    tp->set_race_name("noldo elf");
    members[tp->query_real_name()] = ({tp->query_age(), time() });
  
    save_object(NOLDOR_RACE_GUILD_SAVE);
   
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
    // Find stable master, Ridlin, and remove players horse
    find_living("ridlin")->remove_horse_name(tp->query_real_name());
    
    tp->set_guild_pref(SS_RACE, 0);
    tp->clear_guild_stat(SS_RACE);
    tp->remove_cmdsoul(NOLDOR_RACE_GUILD_SOUL);
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
       
    /* Remove him/her from the list of members. */
    remove_from_list(tp->query_real_name());
}

void remove_from_list(string player)
{
    player = lower_case(player);
    members = m_delete(members,player);
    setuid(); seteuid(getuid());
    save_object(NOLDOR_RACE_GUILD_SAVE);
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
   
    if (str != "noldor")
    {
        notify_fail("Abandon who? The Noldor?\n");
        return 0;
    }
   
    if (!IS_MEMBER(tp))
    {
        write("You cannot abandon the Noldor since you were never " +
            "one.\n");
    return 1;
    }
   
    if ((result = tp->remove_guild_race()) != 1)
    {
        log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) +
            " failed to remove shadow with result " + 
            result + ".\n");
      
        write("You are unable leave the Noldor. Please leave a " +
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
            "voice whispers in your mind, 'You shall be missed.'\n" +
            "'Farewell.'" +
            "\n\nThen nothing.\n");

        say("A dark cloud passes overhead, blocking the light. " +
            "Suddenly, " + QTNAME(TP) + "'s face drains. The " +
            "white light that surrounded " + HIM_HER(tp)+ 
            " fades away and winks out. "+CAP(HIS_HER(TP))+
            " circlet catches fire and burns, leaving nothing " +
            "but a wisp of smoke.\n");

    }
   
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " left the " +
        NOLDOR_RACE_GUILD_NAME + ".\n");
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
   
    clone_object(NOLDOR_RACE_GUILD_CIRCLET)->move(tp, 1);
   
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
        "do not belong in the " + NOLDOR_RACE_GUILD_NAME + 
        " anymore. You are being expelled from the guild.\n");
   
    lower_skill(tp);
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " (race " +
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
        "grown within you. The Noldor shun all that is evil. " +
        "This means you can no longer be counted as a " + 
        NOLDOR_RACE_GUILD_NAME + ".\n\n" +
        "Your circlet bursts into flames, leaving behind a wisp " +
        "of smoke. \n");
   
    lower_skill(tp);
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " (alignment " +
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
        "longer counted as a " + NOLDOR_RACE_GUILD_NAME + ".\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " (inactive) " +
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
void
test_members()
{
   string *names = m_indices(members);
   int    index;

   for (index = 0; index < sizeof(names); index++)
   {
      if (!(SECURITY->exist_player(names[index])))
      {
         log_guild(ctime(time()) + FORMAT_NAME(names[index]) +
            " is no longer a player. -> removed.\n");
         
         remove_from_list(names[index]);
      }
      else if (INACTIVE(file_time(PLAYER_FILE(names[index]) + ".o"), time()))
      {
         log_guild(ctime(time()) + " " + FORMAT_NAME(names[index]) +
             " was purged for inactivity.\n");

         remove_from_list(names[index]);
      }
   }
}

nomask public void
angry_valar(object tp)
{
    tp->catch_tell("\n\nYour actions are not inline with " +
        "acceptable Noldor behaviour.\n" +
        "You are no longer a Noldo!\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + FORMAT_PLNAME(tp) + " booted from Noldor.\n");
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
	log_guild(ctime(time()) + " " + FORMAT_PLNAME(player) + 
           " was punished-health.\n");

	return 1;
    }

    if(ran > 7)
    {
	player->catch_tell("Your foolishness has cost you dearly.\n");
	player->add_fatigue(-100);
	log_guild(ctime(time()) + " " + FORMAT_PLNAME(player) + 
           " was punished-fatigue.\n");

	return 1;
    }

    if((ran < 3) || (ran2 < 3))
    {
	player->catch_tell("Your foolishness has cost you dearly.\n");
	player->command("drop all");
	player->add_panic(150);
	log_guild(ctime(time()) + " " + FORMAT_PLNAME(player) + 
           " was punished-panic/drop all.\n");

	return 1;
    }
}
