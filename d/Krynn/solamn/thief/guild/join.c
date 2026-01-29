/* created by Aridor 01/27/94 */
/* Removed death penalty - Arman 2017 */
/* Aug 27, 2018: Added no-scry protection in guild (Gorboth) */

#include "guild.h"

inherit ROOM_BASE
inherit "/lib/time";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>

#define TRAINROOM   GUILDR + "train"
#define SOUTH       CAVERN + "b2"
#define ONE_DAY     86400    /* seconds in a day */

int next_join = 0;
string *ready_to_expel = ({ });
string *banish_reasons = ({ });
object *tried_join = ({ });
int join_guild(string str);

void
create_thief_room()
{
    set_short("The treasury chamber");
    set_long("This is the treasury chamber. You can see " +
	     "a plaque fastened to the west wall. There is an exit leading " +
	     "further north, but you cannot make out anything there. A " +
	     "door leads south, out of the treasury chamber.\n");
    
    add_exit(SOUTH,"south","@@door");
    add_exit(GUILDR + "train","north","@@only_member");
    
    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

    LIGHT;
    INSIDE;
    
    add_item(({"treasury","treasure"}),
	     "Hmm, apparently there isn't any money here now, but " +
	     "maybe you can do something else in this room?\n");
    add_item(({"text","plaque"}), 
	     "You can read it. You notice there is some fine " +
	     "print written below the normal text.\n");
    add_cmd_item(({"text","plaque"}),"read",
		 "This is the old treasure room of the Clan of the Vingaard " +
		 "Theiwar Dwarves. As you can see, it is not used anymore, " +
		 "but the security system invented by the dwarves is still " +
		 "used to protect this room. This is a secret place and " +
		 "you are not allowed to talk to anyone about the " +
		 "ingeniously twisted minds of the dwarves who created " +
		 "this out of the hard rock in ages long forgotten. The " +
		 "secrecy is an honor and if you intend to break it, be " +
		 "prepared for the worst. You notice some fineprint at " +
                 "the bottom of the plaque that you can read.\n");
    add_item(({"fine print","print","fineprint"}),"You can read it.\n");
    add_cmd_item(({"fine print","print","fineprint"}),"read",
		 "THE GUILD\n=========\n\n" +
		 "This layman guild will offer you protection and unity " +
		 "among its members. You will be able to learn skills you " +
		 "never knew existed. Anyone who desires so may join this " +
		 "guild, there are limits as far as numbers go, though. " +
		 "Joining this guild is entirely at your _own_ peril. You " +
		 "may not receive any information about the guild until you " +
		 "have joined. To join this guild, use 'join the guild'." +
                 " (You can also 'become a thief' if 'join' causes problems.\n\n"+
		 "In case you choose to leave this guild again be certain " +
		 "that when you do, you will lose all your skills acquired " +
		 "here. You might " +
		 "also never be able to come again to this very place you " +
		 "are standing at now. To leave this guild, use 'leave!'.\n\n" +
                 "Members who have problems with their membership in the " +
                 "guild can try to 'rejoin' to get fixed again.\n");
    seteuid(getuid(TO));
    restore_object(NEXT_JOIN);
}

int
become_thief(string str)
{
  if (str && str == "a thief")
  {
    return join_guild("the guild");
  }
  NF("Become what? A thief?\n");
  return 0;
}

void
init()
{
    ::init();
    ADD("join_guild","join");
    ADD("become_thief", "become");
    ADD("leave","leave!");
    ADD("rejoin_guild","rejoin");
}



/* If the person has either the autoshadow or the bits,
 * s/he can be restored. If both is missing, no chance.
 */
int
rejoin_guild(string str)
{
    object ob;
    int result, done = 0;
    seteuid("Krynn");
    NF("You don't need this option.\n");

    if (TP->query_guild_name_lay() == GUILD_NAME)
    {
	/* Lost the bits or the keyring/souls! */
	if (!MEMBER(TP))
	{
	    TP->set_bit(GUILD_GROUP,MEMBER_BIT);
	    write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		       TP->query_real_name() + " member bit.\n");
	    done = 1;
	}
	if (!LAYMAN(TP))
	{
	    TP->set_bit(GUILD_GROUP,BANISH_BIT);
	    write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		       TP->query_real_name() + " layman bit.\n");
	    done = 1;
	}
	ob = P(THIEF_OBJ_ID, TP);
	if (!ob)
	{
	    TP->remove_cmdsoul(THIEF_SOUL);
	    TP->remove_cmdsoul(THIEF_STD_SOUL);
	    clone_object(THIEF_OBJ)->move(TP,1);
	    write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		       TP->query_real_name() + " keyring/souls.\n");
	    done = 1;
	}
	if (done)
	  write("Here you are, just as good as new.\n");
    }
    else if (MEMBER(TP) && LAYMAN(TP))
      /* Lost the autoshadow, but got the bits */
    {
	result = (clone_object(L_SHADOW)->shadow_me(TP, "layman", "thief",
						    GUILD_NAME));
	if (result != 1)
	{
	    write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		       TP->query_real_name() + " autoshadow (unable to add new shadow).\n");
	    TP->clear_bit(GUILD_GROUP,MEMBER_BIT);
	    TP->clear_bit(GUILD_GROUP,BANISH_BIT);
	    if (ob = P(THIEF_OBJ_ID, TP))
	      ob->remove_object();
	    TP->remove_cmdsoul(THIEF_SOUL);
	    TP->remove_cmdsoul(THIEF_STD_SOUL);
	    write("I'm sorry, but you have to join us again.\n");
	    return 1;
	}
	done = 1;
	write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		   TP->query_real_name() + " autoshadow.\n");
	ob = P(THIEF_OBJ_ID, TP);
	if (!ob)
	{
	    TP->remove_cmdsoul(THIEF_SOUL);
	    TP->remove_cmdsoul(THIEF_STD_SOUL);
	    clone_object(THIEF_OBJ)->move(TP,1);
	    write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		       TP->query_real_name() + " keyring/souls.\n");
	    done = 1;
	}
	done = 1;
	write("Here you are, just as good as new.\n");
    }
    else /* Lost the autoshadow and bits (someone who's NEVER been a
	  * member falls into that category :)
	  */
    {
	write_file(REJOINPATH, extract(ctime(time()), 4, 15) + " " +
		   TP->query_real_name() + " autoshadow AND bits (unable to restore).\n");
	TP->clear_bit(GUILD_GROUP,MEMBER_BIT);
	TP->clear_bit(GUILD_GROUP,BANISH_BIT);
	if (ob = P(THIEF_OBJ_ID, TP))
	  ob->remove_object();
	TP->remove_cmdsoul(THIEF_SOUL);
	TP->remove_cmdsoul(THIEF_STD_SOUL);
	write("Sorry, please use the join command instead.\n");
	done = 1;
    }
    return done;
}


int
join_guild(string str)
{
    int result;
    

    if (!str)
      {
	  write("Join what? the guild?\n");
	  return 1;
      }
    if (str != "the guild")
      {
	  write("Join what? the guild?\n");
	  return 1;
      }    

    if (MEMBER(TP))
      {
	  write("You are already a member of this guild.\n");
	  return 1;
      }

    /* Kender disallowed from joining the guild. Current kender
       may remain members. */
    if (TP->query_race_name() == "kender")
    {
        notify_fail("Kender have no respect for the profession! " +
            "Go play your pranks elsewhere!\n");
        return 0;
    }

    if (TP->query_guild_name_lay())
      {
	  write("You are already a member of another layman guild.\n");
	  return 1;
      }
    if (!TP->test_bit("Krynn", GUILD_GROUP, QUEST_BIT) && TP->query_real_name()!="navarjr")
      {
	  write("You are not worthy to join this guild.\n");
	  return 1;
      }
    if (BANISHED(TP))
      {
	/*write("You have been banished or have left the guild before, now " +
		"you cannot rejoin again. How did you get in here, anyway?\n");
	  return 1;*/

	  write("You have been banished or have left the guild before, now " +
		"you need to prove yourself worthy to the guild before you " +
		"are allowed to rejoin. Talk to one of the outposts of the " +
		"guild about this.\n");
	  return 1;
      }

    if (TP->query_alignment() > 0)
      {
#if ALIGNRESTRICT
	write("Your current alignment prevents you from joining. " +
	      "Adjust your alignment before you come back and try again!\n");
	return 1;
#else
	if (member_array(TP, tried_join) < 0)
	{
	    write("Your current alignment may not allow you to use this guild to " +
		  "its full potential. If you want to join anyway, please repeat " +
		  "the join command.\n");
	    tried_join += ({ TP });
	    tried_join -= ({ 0 });
	    return 1;
	}
	write("Your current alignment may not allow you to use this guild to " +
		  "its full potential. It is your wish to join nevertheless.\n");
	tried_join -= ({ TP, 0 });
#endif
      }

    /* -- Navarre June 25th 2008: Removing the time constraint for joining.
    if (time() < next_join &&
	(!TP->query_wiz_level() && extract(TP->query_real_name(),-2) != "jr"))
      {
	  write("You desperately want to join the guild, but you are out " +
		"of luck this time. The guild does NOT accept new members " +
		"at this time. Please try again later.\n");
	  find_living("aridor")->catch_msg("THIEF JOIN: " + QCTNAME(TP) + " failed.\n");
	  return 1;
      }
    */
    
    seteuid(getuid(TO));
    result = (clone_object(L_SHADOW)->shadow_me(TP, "layman", "thief",
						GUILD_NAME));
    if (result == 0)
      {
	  write("You are already a member of another layman guild.\n");
	  return 1;
      }
    if (result == -4)
      {
	  write("The other guilds you have joined prevent you from " +
	     "joining here!\n");
	  return 1;
      }   
    (TRAINROOM)->load_me();
    if (!(TRAINROOM)->send_trainer_to_tattoo_new_member(TP))
      {
	  write("Unfortunately, there is noone there at the moment who could " +
		"inaugurate you into the guild. You'll have to try again " +
		"later I'm afraid.\n");
	  TP->remove_shadow(L_SHADOW);
	  return 1;
      }

    TP->clear_guild_stat(SS_LAYMAN);
    TP->set_bit(GUILD_GROUP, MEMBER_BIT);
    TP->set_bit(GUILD_GROUP, BANISH_BIT);
    clone_object(THIEF_OBJ)->move(TP,1);
    set_alarm(20.0,0.0,"do_update_hooks",TP);
    if (!TP->query_wiz_level() && extract(TP->query_real_name(),-2) != "jr")
      {
/*** Changed by Louie to keep the counter correct
	  next_join += (4*ONE_DAY) + random(6*ONE_DAY);
*/
    next_join = time() + (4*ONE_DAY) + random(6*ONE_DAY);
	  save_object(NEXT_JOIN);
      }
    write_file(JOINPATH, extract(ctime(time()), 4, 15) + " " +
	       TP->query_real_name() + " " + convtime(REALAGE(TP)) + ".\n");
    MASTER_ROOM->add_thief(TP->query_real_name());

    /*TP->setup_skill_decay();*/
    /* Stop the skill decay immediately (if present) */

    return 1;
}

/* do_update_hooks
 * the call of this function is delayed to make sure the soul has
 * been added first.
 */
void
do_update_hooks(object who)
{
    who->update_hooks();
}

void
do_leave(object who, string message)
{
    MASTER_ROOM->remove_thief(TP->query_real_name());
    who->remove_guild_lay();
    who->clear_guild_stat(SS_LAYMAN);
    
#ifdef NO_SKILL_DECAY
    /* Remove skills immediately if skill decay is off */
    for (i=0;i<sizeof(SKILLS);i++)
    {
	num = who->query_skill(SKILLS[i]);
	num -= (2 * num / 3 + random(num / 4));
	if (num > 0)
	  who->set_skill(SKILLS[i], num);
	else
	  who->remove_skill(SKILLS[i]);
    }
#endif
    who->remove_skill(SS_SACRIFICE);
    who->remove_skill(SS_STOLEN);
    
    if (P(THIEF_OBJ_ID, who))
      P(THIEF_OBJ_ID,who)->remove_object();
    if (who->query_default_start_location() == START_ROOM
	&& who->query_wiz_level() == 0)
      who->set_default_start_location(who->query_def_start());
    who->remove_cmdsoul(THIEF_SOUL);
    who->remove_cmdsoul(THIEF_STD_SOUL);
    who->clear_bit(GUILD_GROUP, MEMBER_BIT);
    who->set_bit(GUILD_GROUP, BANISH_BIT);
    who->update_hooks();

    who->catch_msg(message);
    who->command("$south");

/*    Death penalty removed for leaving

      if (who->query_race_name() != "kender")
      {
      who->set_hp(0);
      who->heal_hp(-20000);
      who->do_die(TO);
      }
      else
      {
    who->command("$south");
    }
*/

}

int
leave(string str)
{
    int num,i;
    NF("You are not a member of this guild.\n");
    if (!MEMBER(TP))
      return 0;
    NF("Leave what? the Cabal of Hiddukel?\n");
    if (!str)
      return 0;
    if (str != "the Cabal of Hiddukel" && str != "the cabal of hiddukel")
      return 0;
    
    seteuid(getuid(TO));
    
    
    write_file(LEAVEPATH, extract(ctime(time()), 4, 15) + " " +
	       TP->query_real_name() + ".\n");

    if (TP->query_race_name() == "kender")
    {
        do_leave(TP, "You decide to leave the Cabal of Hiddukel " +
            "with a carefree grin. The power of Hiddukel has no " +
            "hold upon you.\n");
    }
    else
    {
        do_leave(TP,
	     "As you decide to leave the Cabal of Hiddukel, you feel " +
	     "the disapproving gaze of Hiddukel fall upon you.\n\n\n\n\n");
    }

    return 1;
}

void
door()
{
    write("You open the door, walk through and close it again.\n");
    tell_room(TO, QCTNAME(TP) + " opens the door.\n", TP);
    tell_room(SOUTH, "The door opens.\n");
    set_alarm(1.0,0.0,"close_again",TP);
}

void
close_again(object who)
{
    tell_room(TO,"The door closes again.\n");
    tell_room(SOUTH, QCTNAME(who) + " closes the door.\n",TP);
}

int
only_member()
{
    object para;
    int how_long = random(20) + 10;
    if (MEMBER(TP))
      return 0;
    if ((TP->query_skill(SS_AWARENESS) > 90) ||
	(TP->query_skill(SS_FR_TRAP) > 50))
      {
	  write("You notice the trap that has been set into the exit and " +
		"carefully avoid it.\n");
	  return 0;
      }
    say(QCTNAME(TP) + " tries to go north but suddenly falls backwards and " +
	"appears to be knocked unconscious.\n");
    write("The last that you feel is a tingling sensation inside your feet, " +
	  "then there is nothing...\n\n\n\n" +
	  "                  DARKNESS...\n\n\n\n");
    para = clone_object("/std/paralyze");
    para->set_stop_verb("");
    para->set_stop_message("");
    para->set_stop_fun("stop_paralyze");
    para->set_fail_message("You are unable to do that.\n");
    para->set_stop_object(0);
    para->set_remove_time(how_long + 1);
    para->move(TP, 1);
    TP->add_prop(LIVE_S_EXTRA_SHORT," is lying unconsciously on the floor");
    set_alarm(itof(how_long),0.0,"wake_up_again",TP);
    return 1;
}


void
wake_up_again(object who)
{
    who->catch_msg("SOMEONE SAYS: COME WITH ME, MORTAL ONE!...\n\n" +
		   "You slowly regain consciousness and think you must've " +
		   "been dreaming -\n" +
		   "A pretty bad dream -\nYou could call it a NIGHTMARE.\n\n");
    who->catch_msg("You think you might be OK again, now...\n");
    who->remove_prop(LIVE_S_EXTRA_SHORT);
    tell_room(TO,QCTNAME(who) + " slowly regains consciousness.\n",who);
}

/* expel_member_from_guild
 *  call with reason = 0 to test if someone needs to be expelled.
 *  if no reason is given, no expelling is done unless a reason is found
 *     in the banish_reasons.
 *  who, the player name, must be given always.
 */
varargs void
expel_member_from_guild(string who, mixed reason)
{
    int num,i;
    object pers = find_living(who);
    if (!who)
      return;
    num = member_array(who, ready_to_expel);
    if (num == -1)
      {
	  if (!reason)
	    return;
	  ready_to_expel += ({ who });
	  banish_reasons += ({ reason });
      }
    else if (!reason)
      reason = banish_reasons[num];
    if (!reason)
      return;
    if (pers)
      {
	  if (!MEMBER(pers))
	    return 0;
	  
	  write_file(BANISHPATH, extract(ctime(time()), 4, 15) + " " +
		     pers->query_real_name() + " for " + reason + "\n");
	  do_leave(pers,
		   "\n\nSuddenly, you can see HIDDUKEL, your protector and " +
		   "mentor washing " +
		   "over you and settling into your very SOUL.\n" +
		   "He tells you: You are now banished from the guild because " +
		   reason + "\n\n\n\n");
      }
    else
      {
	  /* mark here for expelling when player not logged in */
	  ready_to_expel += ({ who });
	  banish_reasons += ({ reason });
	  save_object(NEXT_JOIN);
      }
}

void
do_save()
{
    save_object(NEXT_JOIN);
}
