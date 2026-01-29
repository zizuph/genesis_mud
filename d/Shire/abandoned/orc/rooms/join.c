/*
* /d/Shire/hobbit/join.c
*
* This is the join room of the Hobbit race guild. You may join here.
* Modified from the join room of the Rockfriend guild, created by
   *
* /Mercade, 9 January 1994
*
* This room:
* /Dunstable
* /Mercade, 13 November 1994
*
* Revision history:
* Changed the descriptive aspects of the room
* /Dunstable 18 March 1994
*/

#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/orcr/orcr.h"
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include "local.h"
#include "titles.h"

inherit TUNNEL_BASE;


#define BAND_ID        "_orc_racial_guild_item_"
#define START          (ORCRGLD_DIR + "start")
#define LOG_SIZE       25000

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

/*
* Global variables.
*
* The mapping members has the names of the players as indices and the
* values are an array with two elements, the family name of the player
* and the date the player joined.
*/
private mapping members;

//   Prototypes
void dest_band(object player);


/*
* Functio name: create_room
* Description : Called when the room is first loaded into memory.
*/
void
create_tunnel_room()
{

    set_vbfc_extra(tunnel_desc3);
    extraline = "Torches spread more light here than normal. A " +
        "large boulder sits in the middle of the room.\n";
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");
    add_item(({"large boulder", "boulder", "altar"}),
        "The boulder is about half as tall as a goblin and two " +
        "arm's length wide. The boulder is jet black and looks " +
        "like part of the mountain. Its surface is covered " +
        "with black stains.\n");
    add_item(({"stains", "black stains", "blood stains", "blood"}),
        "The stains are black and cover the boulder in spots. " +
        "Some look fresh while others have dried. Where the " +
        "stains are dry, the boulder is pitted with small holes\n");

//add_cmd_item( ({ "sign" }), ({ "read" }),
   
   add_exit(ORCR_ROOM+ "gld01","north");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_CLEANUP,      1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
   create_guild_support();
   
   setuid();
   seteuid(getuid());
   
   restore_object(ORCR_RACE_GUILD_SAVE);
   if (!mappingp(members))
   {
      members = ([ ]);
   }
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
   
   add_action("do_try",   "shed");
   add_action("do_break", "curse");
   add_action("request",  "reshed");
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
   
   if (file_size(ORCR_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(ORCR_RACE_GUILD_LOG, (ORCR_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(ORCR_RACE_GUILD_LOG, text);
}

/*
* Function name: do_try
* Description  : When a goblin wants to join the guild, this function
*                makes him/her a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_try(string str)
{
   object tp = this_player();
   object shadow;
   string tribe;
   int    result;
   
   if((tp->query_alignment() < -100))
    {
	write("\nOnly those who are devoted to the Dark Lord can hope " +
        "to join.\n\nBegone!\n");
	return 1;
    }
   if (!strlen(str))
      {
      notify_fail(capitalize(query_verb()) + " what? blood? You " +
          "must <shed blood> to prove yourself to the Dark Lord!\n");
      return 0;
   }

   if (tp->query_race() != "goblin")
      {
      write("You are not a goblin. Leave now!\n");
      return 1;
   }
   if(tp->query_alignment() < ORCR_RACE_GUILD_ALIGN)
      {
      write("You have grown soft! Prove yourself " +
          "unless you want to be kicked out!\n");
      return 1;
   }
   
   if (IS_MEMBER(tp))
      {
      write("You have already shed your blood for the Dark One. " +
          "If you have lost your way, you may <reshed blood> to " +
          "dedicate yourself again.\n");
      return 1;
   }
   
   if (tp->query_guild_member(ORCR_RACE_GUILD_TYPE))
      {
      write("You cannot be a member of two racial guilds at a time.\n");
      return 1;
   }

   shadow = clone_object(ORCR_RACE_GUILD_SHADOW);
   
   if ((result = shadow->shadow_me(tp, ORCR_RACE_GUILD_TYPE,
               ORCR_RACE_GUILD_STYLE, ORCR_RACE_GUILD_NAME)) != 1)
   {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to add shadow with result " + result + ".\n");
      shadow->remove_shadow();
      
      write("How odd. For some reason you cannot shed your " +
          "blood for the Dark One. Make a bugreport in this room.\n");
      
      return 1;
   }
   
   set_alarm(3.0,0.0,"init_me",tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
      ORCR_RACE_GUILD_NAME + ".\n");
   
   clone_object(ORCR_RACE_GUILD_BAND)->move(tp, 1);
   //    write("Getting pipe...\n");
   write("Raising your right claw, you bellow loudly and slash " +
       "yourself deeply across your forearm. Black blood spills " +
       "from the gashes and falls to the altar, hissing and " +
       "pitting the stone. Within moments, everything goes " +
       "black as your body convulses. You fall to the ground " +
       "and roar with pain. After a minute, you stand up, " +
       "shakily and disoriented. You are now an orc.\n");


   say(QCTNAME(tp) + " raises " +HIS_HER(tp) + " and slashes " + 
       HIS_HER(tp) + " right forearm. Black blood spills from " +
       "the new wound and falls to the altar, hissing and " +
       "pitting the stone. Suddenly, " + HE_SHE(tp) + 
       " begins to convulses then and falls behind the altar. " +
       "A loud, blood-curdling roar echoes throughout the room; " + 
       HE_SHE(tp) + " stands up from behind the altar, shaking. " +
       "There is something different about " + HIM_HER(tp) + 
       " now.\n");
   
   tp->clear_guild_stat(SS_RACE);
   tp->set_guild_pref(SS_RACE, ORCR_RACE_GUILD_TAX);
   tp->add_cmdsoul(ORCR_RACE_GUILD_SOUL);
   tp->update_hooks();
   tp->set_race_name("orc");
   //    write("Adding cmdsoul...\n");
   
   save_object(ORCR_RACE_GUILD_SAVE);
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
   object band;
   
   tp->set_guild_pref(SS_RACE, 0);
   tp->clear_guild_stat(SS_RACE);
   tp->remove_cmdsoul(ORCR_RACE_GUILD_SOUL);
   tp->update_hooks();
   tp->setup_skill_decay();
   tp->reset_race_name();
   
   /* If the player starts in the guild by default, set this to
   * the default starting location for all players.
   */
   if (tp->query_default_start_location() == START)
      {
      tp->set_default_start_location(tp->query_def_start());
   }
   
   set_alarm(2.0,0.0,&dest_band(tp));
// remove quild object
   {
      band->remove_object();
   }
   
// Remove him/her from the list of members.

   members = m_delete(members, tp->query_real_name());
   
   setuid();
   seteuid(getuid());
   
   save_object(ORCR_RACE_GUILD_SAVE);
}

void
remove_from_list(string player)
{
   player = lower_case(player);
   members = m_delete(members,player);
   setuid(); seteuid(getuid());
   save_object(ORCR_RACE_GUILD_SAVE);
}


void
dest_band(object player)
{
   object band;
   
   band = present(BAND_ID, player);
   if (objectp(band))
      {
      band->remove_object();
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
   object band;
   int    result;
   
   if (str != "orcs")
      {
      notify_fail("Curse what? Your race? Then you shall have " +
          "to <curse orcs>.\n");
      return 0;
   }
   
   if (!IS_MEMBER(tp))
      {
      write("You cannot curse the orcs since you were never a " +
          "member.\n");
      return 1;
   }
   
   if ((result = tp->remove_guild_race()) != 1)
      {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to remove shadow with result " + result + ".\n");
      
      write("You cannot seem to leave the orcs. Please leave a " +
          "bugreport in this room.\n");
      
      return 1;
   }
   
   write("\nYou are no longer an orc and return to the pitiful race " +
       "of goblins.\n");
   
   lower_skill(tp);

// kill the guild object
  
   band = present(BAND_ID, tp);
   if (objectp(band))
      {
      band->remove_object();
      write("Your armband is ripped from your arm and destroyed " +
          "before your eyes.\n");
      say(QCTNAME(tp) + " has " + tp->query_possessive() +
         " armband is destroyed..\n");
   }
   
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      ORCR_RACE_GUILD_NAME + ".\n");

   
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
* Description  : Members who have lost their pipe, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int
request(string str)
{
   object tp = this_player();
   
   if (str != "band")
      {
      notify_fail("Request what? A new armband?\n");
      return 0;
   }
   
   if (!IS_MEMBER(tp))
      {
      write("You are not a member of this guild. You have no " +
          "right to an armband.\n");
      return 1;
   }
  
   if (objectp(present(BAND_ID, tp)))
      {
      write("You already have an armband. You don't need two.\n");
      return 1;

   }
   
   setuid();
   seteuid(getuid());
   
   clone_object(ORCR_RACE_GUILD_BAND)->move(tp, 1);
   
   write("A brand armband appears on the boulder in a pool of " +
       "fresh blood. You pick it up proudly.\n");
   say(QCTNAME(tp)  + " prudly picks up an armband that " +
       "magically appears on the boulder before you.\n");
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
   tp->catch_msg("\nYou are no longer an orc. Therefore you do not " +
      "belong in the " + ORCR_RACE_GUILD_NAME + " any more. You " +
      "are being expelled from the guild. You can no longer " +
      "call yourself a member of the " + ORCR_RACE_GUILD_NAME + ".\n");
   
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
   tp->catch_msg("\nThe Dark Lord does not tolerate those who " +
       "go soft and follow the light. You are expelled from the" + 
       ORCR_RACE_GUILD_NAME + " No go before He sends his " +
       "minions to destroy you!.\n");
   
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
* This section takes care of the member administration.
*/

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
