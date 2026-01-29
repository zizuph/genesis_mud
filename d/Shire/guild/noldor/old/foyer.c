/*
 * Foyer and entrance in Noldor Guild
 * By Finwe, August 2000
 */
 
#pragma strict_types

#include "noldor.h" 
#include "/d/Shire/rivendell/local.h"
#include <macros.h>

inherit "/lib/guild_support";
inherit BUILDING_BASE;

//#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))

private mapping members;
void dest_circlet(object player);

void
create_guild_room()
{
    set_short("A beautiful foyer");
    set_long("This is the entrance to the Noldor guild. The " +
	    "walls are polished and reflect light from the lamps " +
		"and @@daylight_desc@@ flowing in through the entrance. A " +
		"pedestal holding a large book is off to one side of " +
		"the room.\n");
  
    add_item("pedestal", 
        "The pedestal is made of wood and leafed with mithril. " +
		"It has been polished to a bright shine and is in the " +
		"shape of a tree. A great book sits on top of it.\n");

    set_extra_wall(" Large windows are set into the east and " +
        "west walls, filling the room with @@daylight_desc@@. A " +
        "large silver pedestal with a book stands against one wall.\n");
 
	clone_object("/d/Shire/guild/noldor/obj/join_book")->move(TO);
//	clone_object(NOLGLD_DIR + "join_book")->move(TO);
 
    add_exit(NOLGLD_DIR + "board_rm", "north", "@@check_member@@");
    add_exit(VALLEY_DIR + "stone_seat", "south");
    add_exit(NOLGLD_DIR + "start_rm", "east", "@@check_member@@");
    add_exit(NOLGLD_DIR + "train", "west","@@check_member@@");
}
 

void
init()
{
::init();
   
   init_guild_support();
   
   add_action("join_guild",   "join");
   add_action("leave_guild",  "leave");
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


/*
* Function name: join_guild
* Description  : When a hobbit wants to join the guild, this function
*                makes him/her a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
join_guild(string str)
{
   object tp = this_player();
   object shadow;
   int    result;
   
   if (!strlen(str) && str !="noldor")
      {
      notify_fail("Become what? That's not possible.\n");
      return 0;
   }

   if (tp->query_race() != "elf")
      {
      write("You are not a elf. You many not become a Noldor.\n");
      return 1;
   }
   if(tp->query_alignment() <= NOLDOR_RACE_GUILD_ALIGN  )
      {
      write("Your past actions prevent you from becoming a " +
          "Noldor. When you have improved yourself, you may try " +
          "again.\n");
      return 1;
   }
   
   if (IS_MEMBER(tp))
      {
      write("You are already a Noldor. If you have lost your " +
         "circlet, you may get a new one using <request circlet>.\n");
      return 1;
   }
   
   if (tp->query_guild_member(NOLDOR_RACE_GUILD_TYPE))
      {
      write("You may not be a member of two racial guilds\n");
      return 1;
   }
   
   
   shadow = clone_object(NOLDOR_RACE_GUILD_SHADOW);
   
   if ((result = shadow->shadow_me(tp, NOLDOR_RACE_GUILD_TYPE,
               NOLDOR_RACE_GUILD_STYLE, NOLDOR_RACE_GUILD_NAME)) != 1)
   {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to add shadow with result " + result + ".\n");
      shadow->remove_shadow();
      
      write("The magic of the Noldor has failed. Please leave a " +
          "bug report in this room.\n");
      
      return 1;
   }
   
   //  write("You seem to have a shadow...");
    write("You are already counted as a Noldor.\n");
    set_alarm(3.0,0.0,"init_me",tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
        NOLDOR_RACE_GUILD_NAME + ".\n");
   
    clone_object(NOLDOR_RACE_GUILD_CIRCLET)->move(tp, 1);
     //    write("let's get the stuff for them...\n");
    write("The room begins to fill with bright " +
        "light. It surrounds you, enveloping you in " +
        "pure white light. A circlet appears in your hand. A " +
        "warm voice in your mind says to you 'Welcome home, " +
        QTNAME(tp) + "'. The light slowly diminishes, leaving " +
        "you surround by an aura of pure light.\n");
    say("The room begins to fill with bright light. " +
        "It surrounds " + QTNAME(tp) + ", enveloping " + 
        HIM_HER(tp) + " in pure white light. The light slowly " + 
        "diminishes, surrounding " + HIM_HER(tp) + " with a soft glow.\n");
   
    tp->clear_guild_stat(SS_RACE);
    tp->set_guild_pref(SS_RACE, NOLDOR_RACE_GUILD_TAX);
    tp->add_cmdsoul(NOLDOR_RACE_GUILD_SOUL);
    tp->update_hooks();
   //    write("Adding cmdsoul...\n");
  
   save_object(NOLDOR_RACE_GUILD_SAVE);
   //    write("Saving master object...\n");
   
   return 1;
}

int
init_me(object ob)
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
   tp->remove_cmdsoul(NOLDOR_RACE_GUILD_SOUL);
   tp->update_hooks();
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
   //members = m_delete(members, tp->query_real_name());
   
   setuid();
   seteuid(getuid());
   
   save_object(NOLDOR_RACE_GUILD_SAVE);
}


void
dest_circlet(object player)
{
   object circlet;
   
   circlet = present(CIRCLET_ID, player);
   if (objectp(circlet))
      {
      circlet->remove_object();
   }
}


void
remove_from_list(string player)
{
   player = lower_case(player);
   members = m_delete(members,player);
   setuid(); seteuid(getuid());
   save_object(NOLDOR_RACE_GUILD_SAVE);
}


/*
* Function name: leave_guild
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
leave_guild(string str)
{
   object tp = this_player();
   object circlet;
   int    result;
   
   if (str != "noldor")
      {
      notify_fail("Leave what? The Noldor?\n");
      return 0;
   }
   
   if (!IS_MEMBER(tp))
      {
      write("You cannot leave the Noldor since you were never one.\n");
      return 1;
   }
   
   if ((result = tp->remove_guild_race()) != 1)
      {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to remove shadow with result " + result + ".\n");
      
      write("You cannot seem to leave the Noldor. Yet everyone who " +
         "wishes so, should be able to do so. Please leave a bugreport " +
         "in this room.\n");
      
      return 1;
   }
   
   write("\n");
   
    lower_skill(tp);
    circlet = present(CIRCLET_ID, tp);
    if (objectp(circlet))
      {
      circlet->remove_object();
      write("A dark cloud passes overhead, blocking the light. " +
          "Suddenly, a strange feeling begins to leave you, and " +
          "before long, the whight glow about disipates and " +
          "flickers out for good. Your bright circlet catches " +
          "fire and and burns, leaving nothing but a wisp of " +
          "smoke. A saddened voice whispers in your mind, " +
          "\"You shall be missed. Farewell.\"\n\nThen nothing.\n");

      say("A dark cloud passes overhead, blocking the light. " + 
          "Suddenly, " + HIS_HER(tp) + " face drains. The white light " +
          "that surrounded " + HIM_HER(tp)+ " fades away and " +
          "winks out. A circlet catches fire " +
          "and and burns, leaving nothing but a wisp of smoke.\n");
   }
   
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      NOLDOR_RACE_GUILD_NAME + ".\n");
   
   return 1;
}

/*
* Function name: request
* Description  : Members who have lost their circlet, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int
request(string str)
{
   object tp = this_player();
   
   if (str != "circlet")
      {
      notify_fail("Request what? A new circlet?\n");
      return 0;
   }
   
   if (!IS_MEMBER(tp))
      {
      write("You are not a Noldo. You can't have one.\n");
      return 1;
   }
   
   if (objectp(present(CIRCLET_ID, tp)))
      {
      write("You already have a circlet and don't need two.\n");
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
   tp->catch_msg("\nSince you chose to change races, you are no longer able to belong to  " +
        NOLDOR_RACE_GUILD_NAME + ". You are removed from the guild.\n");
   
   lower_skill(tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") changed races, booted out.\n");
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
   tp->catch_msg("\nIt seems the shadow of the Dark Lord has grown within you. The Noldor shun all that is evil. This means you can no longer be counted as a " + NOLDOR_RACE_GUILD_NAME + ".\n\n" +
   "Your circlet bursts into flames, leaving behind a wisp of smoke. \n");
   
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
