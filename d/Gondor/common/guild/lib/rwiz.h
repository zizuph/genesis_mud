/* 
* Code for the Wizards/Mortals administrating the Rangers Guild
* Originally coded by Lord Elessar Telcontar
*
* Revision history:
* Mercade (23 Sept 1993) added 'rangertell' to 'tell' all rangers
* Olorin  (26 Oct 1993) added 'deputy' to allow Captains to
*          assign a Lieutenant
* Elessar (24 Jul 1994) added support for punishing Rangers
* Elessar ( 8 Feb 1995) changed 'deputy' for Ltn. and Sgt. ranks.
*                       Changed title system to direct Council control.
*                       Allowed for special Master assignments.
* Elessar (   Aug 1998) Allowed for assigning mentors
* Gnadnar (25 Aug 1998) Allowed unban. Evict outlaws from guild premises.
* Gwyneth (4 Nov 2000) Removed hard-coded wizard name (Elessar) from code.
*/

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <options.h>
#include "/d/Gondor/common/guild/lib/punish_defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/titles.h"

#define TOKEN  ({ RANGER_DIR + "rring",   \
      RANGER_DIR + "rring",   \
      RANGER_DIR + "ramulet" })

int
make_ranger(string who)
{
   int     result;
   object  pl;
   
   NF("That is not for you yet.\n");
   if (!TP->query_wiz_level()) 
      return 0;
   NF("Only Gondor wizards can do that.\n");
   if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
	write_file(STATUS_LOG, TP->query_name() + " attempted 'ranger " +
	    who + "' without permission. "+ ctime(time()) + ".\n");
	return 0;
   }
   NF("Make who a ranger?\n");
   if (!who)
      return 0;
   who = lower_case(who);
   NF("No such player.\n");
   pl = find_player(who);
   if (!objectp(pl))
      return 0;
   NF("But that player is already a Ranger!\n");
   if (RANGER_GUILD->query_ranger(who))
      return 0;
   NF("But that player is already a member of the "+
      pl->query_guild_name_occ()+"!\n");
   if (pl->query_guild_member_occ())
      return 0;
   if ((result = RANGER_GUILD->add_ranger(who,1)) == 1)
      {
      write("You made "+capitalize(who)+" a Ranger!\n");
      setuid();
      seteuid(getuid());
      write_file(RANGER_LOG, TP->query_name() + " made "
         + capitalize(who) + " a Ranger! "+ctime(time())+".\n");
      return 1;
   }
   if (result == 0) 
      NF("GUILD: Unable to add shadow to "+who+".\n");
   if (result == -1) 
      NF("GUILD: "+capitalize(who)+" is not in the game.\n");
   if (result == -2) 
      NF("GUILD: "+capitalize(who)+" is already a Ranger.\n");
   return result;
}

int
unmake_ranger(string who)
{
   int     punish, 
           result;
   object  pl;
   NF("That is not for you yet.\n");
   if (!TP->query_wiz_level()) 
      return 0;
   NF("Only Gondor wizards can do that.\n");
   if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
	write_file(STATUS_LOG, TP->query_name() + " attempted 'unranger " +
	    who + "' without permission. "+ ctime(time()) + ".\n");
	return 0;
   }
   if (query_verb() == "unrangerp") 
      punish = 1;
   NF("Remove who from the Rangers?\n");
   if (!stringp(who)) 
      return 0;
   who = lower_case(who);
   NF("That person is not playing right now.\n");
   pl = find_player(who);
   if (!objectp(pl)) 
      return 0;
   NF("That person is not a ranger!\n");
   if (!RANGER_GUILD->query_ranger(who)) 
      return 0;
   if ((result = RANGER_GUILD->remove_ranger(who,1)) == 1)
      {
      write("You remove " + CAP(who) + " from the Rangers!\n");
      setuid();
      seteuid(getuid());
      write_file(RANGER_LOG, TP->query_name() + " removed " 
         + CAP(who) + " from the Rangers. Punished: " + punish 
         + ". "+ctime(time())+".\n");
      if (punish) 
         RANGER_GUILD->decrease_skills_as_punishment(pl);
      else 
         write("No punishment given.\n");
      return 1;
   }
   NF("Failed to remove " + CAP(who) + " from the guild!\n");
   return result;
}

int
give_token(object pl)
{
   object  token;
   int     division;
   
   if (!objectp(pl)) 
      return 0;
   division = query_bin_bits(1,16,2,pl);
   token = present("ranger_guild_object", pl);
   if (objectp(token))
      token->remove_object();
   setuid();
   seteuid(getuid());
   token = clone_object(TOKEN[division]);
   token->move(pl, 1);
   pl->catch_msg("A white pigeon comes flying with a new " +
      token->query_name() + " to you!\n");
   write(pl->query_name() + " given a new "+token->query_name()+"!\n");
   return 1;
}

int
newtoken(string who)
{
   object  pl, 
   *pl_list;
   int     i;
   
   NF("That is not for you yet.\n");
   if (!TP->query_wiz_level()) 
      return 0;
   NF("Only Gondor wizards can do that.\n");
   if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
	write_file(STATUS_LOG, TP->query_name() + " attempted 'newtoken " +
	    who + "' without permission. "+ ctime(time()) + ".\n");
	return 0;
   }
   NF("Give new token to whom?\n");
   if (!who) 
      return 0;
   who = lower_case(who);
   if (who != "all")
      {
      NF("No such player!\n");
      pl = find_player(who);
      if (!objectp(pl)) 
         return 0;
      NF("That person is not a Ranger!\n");
      if (!RANGER_GUILD->query_ranger(who)) 
         return 0;
      give_token(pl);
      return 1;
   }
   pl_list = users();
   while (i < sizeof(pl_list))
   {
      if (RANGER_GUILD->query_ranger(pl_list[i]->query_name()))
         give_token(pl_list[i]);
      i++;
   }
   write("All Rangers given a new token!\n");
   return 1;
}

int
company(string str)
{
   string *str_arr, 
   name, 
   company;
   int     cbit,
   rbit,
   dbit;
   object  pl;
   
   rbit = query_bin_bits(1,18,2,TP);
   dbit = query_bin_bits(1,16,2,TP);
   
   NF("Only a Ranger Officer can do that.\n");
   if ((rbit != 2) && (!COUNCIL->is_officer(TP->query_name())))
   {
       if (!TP->query_wiz_level()) 
       {
           return 0;
       }
       NF("Only Gondor wizards can do that.\n");
       if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Gondor")
       {
	  write_file(STATUS_LOG, TP->query_name() + " attempted 'company " +
	    str + "' without permission. "+ ctime(time()) + ".\n");
	  return 0;
       }
   }
   
   NF("Wrong number of arguments: 'company <player> <company>'\n");
   if (!stringp(str) || (sscanf(str,"%s %s",name,company) != 2)) 
      return 0;
   name = lower_case(name);
   NF("No such player!\n");
   pl = find_player(name);
   if (!objectp(pl)) 
      return 0;
   
   NF("No such company! (Gondor, Ithilien)\n");
   if ((company != "gondor") && (company != "ithilien") 
       && (company != "pupils"))
   return 0;
   
   NF("That person is not a Ranger!\n");
   if (query_bin_bits(1,18,2, pl) != 1 &&
         query_bin_bits(1,18,2, pl) != 2) 
   return 0;
   
   if (company == "pupils") cbit = 0;
   if (company == "gondor") cbit = 1;
   if (company == "ithilien") cbit = 2;
   
   NF("You are not an Officer of the " + CAP(company) + " Company!\n");
   if ((cbit != dbit) && (!TP->query_wiz_level()))
      return 0;
   
   NF("That person is a Ranger of another Company!\n");
   dbit = query_bin_bits(1,16,2, pl);
   if (dbit != 0) 
      return 0;
   NF("You realize that " + CAP(LOW(name)) + " has not been in "
     + "training long enough to be admitted to the " + CAP(company)
     + " Company yet.\n");
   if (pl->query_base_stat(SS_OCCUP) < COMP_REQUIREMENT ||
        pl->query_ranger_rank(2) < PUP_RANK_REQUIREMENT)
      return 0;
   NF(CAP(LOW(name)) + " has not been declared graduated yet.\n");
   if (!R_SPONSORS->query_graduated(name))
      return 0;
   setuid();
   seteuid(getuid());
   set_bin_bits(1,16,2, pl, cbit);
   pl->set_skill(SS_REWARDED, 0);
   (R_SPONSORS)->remove_pupil(CAP(lower_case(name)));
   give_token(pl);
   write(CAP(name) + " is now assigned to the " + CAP(company)
      + " Company.\n");
   write_file(STATUS_LOG, TP->query_name() + " assigned " + CAP(name)
      + " to the " + CAP(company) + " Company. " + ctime(time())+".\n");
   RANGER_GUILD->company_log(name,cbit);
   return 1;
}

int
captain(string who)
{
   object  key,
   pl;
   string  captain;
   int     cbit;
   
   NF("That is not for you yet.\n");
   if (!TP->query_wiz_level()) 
      return 0;
   NF("Only Gondor wizards can do that.\n");
   if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
	write_file(STATUS_LOG, TP->query_name() + " attempted 'captain " +
	    who + "' without permission. "+ ctime(time()) + ".\n");
	return 0;
   }
   NF("Make who a Captain?\n");
   if (!who) 
      return 0;
   who = lower_case(who);
   NF("No such player!\n");
   pl = find_player(who);
   if (!objectp(pl))
      return 0;
   NF("That person is not a Ranger!\n");
   if (!RANGER_GUILD->query_ranger(who))
      return 0;
   setuid();
   seteuid(getuid());
   cbit = query_bin_bits(1,16,2, pl);
   if (cbit == 1) captain = COUNCIL->query_gondor();
   if (cbit == 2)  captain = COUNCIL->query_ithilien();
   NF("There already is a Captain of " + pl->query_company()+"!\n");
   if (captain != 0)
      return 0;
   if (cbit == 1) COUNCIL->add_gondor_captain(who);
   if (cbit == 2) COUNCIL->add_ithilien_captain(who);
   set_bin_bits(1, 18, 2, pl, 2);
   write("You assign " + pl->query_name() + " as Captain of "
      + pl->query_company()+".\n");
   pl->catch_msg("You have been assigned as Captain of "
      + pl->query_company() + "!\n");
   write_file(RANGER_LOG, CAP(who) + " is promoted to Captain of "
      + "the Rangers of " + pl->query_company() + ", by "
      + TP->query_name() + ". " + ctime(time())+".\n");
   key = clone_object(RANGER_DIR+"obj/councilkey");
   key->move(pl, 1);
   pl->catch_msg("You receive a gold key as proof.\n");
   return 1;
}

int deputy(string str)
{
   object  deputy,
   key;
   int     ic,
   cbit,
   rbit;
   string  rank, 
   who;
   
   cbit = query_bin_bits(1,16,2,TP);
   rbit = query_bin_bits(1,18,2,TP);
   ic = COUNCIL->is_council_member(TP->query_name());
   
   NF("Only a Captain may assign a deputy!\n");
   if (ic < G_CPT || ic > I_CPT)
      {
      /* redundant check if player is captain */
         if(rbit == 2)
         {
         write("BUG: Please inform the guild master! (SOUL D1 = "
            + ic + ")\n"
            + "     The council file seems to be out of date!\n");
       }
      return 0;
   }
   
   /* redundant check if player is captain */
      NF("BUG: Please inform the guild master! (SOUL D2)\n"
      + "     The council file seems to be out of date!\n");
   if(rbit != 2)
      return 0;
   NF("Syntax is 'deputy <who> <lieutenant/sergeant>'\n");
   if (!stringp(str) || sscanf(str,"%s %s",who,rank) != 2) 
      return 0;
   who = lower_case(who);
   if(!(deputy = find_player(who)))
      write("That person is not on duty right now, but your order "
      + "will still be executed.\n");
   NF("Deputize " + CAP(lower_case(who)) + " as sergeant or "
      + "lieutenant?\n");
   if ((rank != "lieutenant") && (rank != "sergeant"))
      return 0;
   NF("Your " + rank + " must be a member of your company!\n");
   if(!(deputy = find_player(who)))
      {
      if(member_array(who,
               RANGER_GUILD->query_company_members(cbit)) == -1)
      return 0; 
   }
   else if(cbit != query_bin_bits(1,16,2,deputy))
      return 0;
   if (rank == "lieutenant")  
      switch(cbit)
   {
      case 1: 
      COUNCIL->add_gondor_deputy(who);
      break;
      case 2: 
      COUNCIL->add_ithilien_deputy(who);
      break;
   }
   else
      switch(cbit)
   {
      case 1: 
      COUNCIL->add_gondor_sergeant(who);
      break;
      case 2: 
      COUNCIL->add_ithilien_sergeant(who);
      break;
   }
   setuid();
   seteuid(getuid());
   (R_SPONSORS)->remove_master(capitalize(who));
   write_file(STATUS_LOG, CAP(who) + " is promoted to " + CAP(rank)
      + " of the Rangers of " + TP->query_company() + ", by "
      + TP->query_name()+". " + ctime(time()) + ".\n");
   write("You promote " + CAP(who) + " to " + CAP(rank) 
      + " of the Rangers of " + TP->query_company() + "!\n");
   if(objectp(deputy))
      {
      tell_object(deputy, "You have been promoted to " + CAP(rank)
         + " by " + TP->query_name() + "!\n");
      if (!present("_council_key", deputy))
         {
         key = clone_object(RANGER_DIR+"obj/councilkey");
         key->move(deputy, 1);
         deputy->catch_msg("You receive a gold key as proof.\n");
      }
   }
   else
      {
      write(BSN("Mail your " + CAP(rank) + " to get a key to the "
            + "council room using the command 'get council key' just "
            + "outside the council room in the guild house of the "
            + "Gondor company!"));
      write(BSN("Also remember to unassign the Master title from "
            + "your new deputy, if he or she was a Master Ranger "
            + "previous to being deputized now."));
   }
   return 1;
}

int
unassign_master(string str)
{
   object  deputy;
   string  who, 
   rank;
   int     i;
   
   FIX_EUID
   (R_SPONSORS)->telekinesisanka();
   NF("This is only for the Officers to do!\n");
   if (!COUNCIL->is_officer(TP->query_real_name()))
      return 0;
   NF("Unassign whom from a Master title or specialty?\n");
   if (!stringp(str)) 
      return 0;
   who = lower_case(str);
   deputy = find_player(who);
   if (!objectp(deputy))
      {
      write("That person does not seem to be logged in.\n");
      if ((R_SPONSORS)->remove_master(CAP(who)))
         write("The order will be given to Master Amaron however.\n");
      else
         write(CAP(who) + " does not seem to be a Master.\n");
      return 1;
   }
   if (!IS_RANGER(deputy))
      return 0;
   NF("That Ranger is not a member of your Company.\n");
   if (query_bin_bits(1,16,2, deputy) != query_bin_bits(1,16,2,TP)) 
      return 0;
   NF("That Ranger does not have a specialty nor a Master title!\n");
   if (deputy->query_master_ranger() == 0)
      {
      if (deputy->query_skill(SS_MASTER_TASK) <= 0) 
         return 0;
      i = deputy->query_skill(SS_MASTER_TASK);
      rank = MASTER_TITLES[i];
      deputy->remove_skill(SS_MASTER_TASK);
      write("You remove the " + rank + " of " + CAP(who) + ".\n");
      deputy->catch_msg(QCTNAME(TP) + " relieves you of the "
         + rank + " task.\n");
      write_file(STATUS_LOG, CAP(who) + " was relieved of the specialty "
         + CAP(rank) + " by " + TP->query_name() + ", "
         + ctime(time()) + ".\n");
      return 1;
   }
   deputy->set_master_ranger(0);
   (R_SPONSORS)->remove_master(CAP(who));
   i = deputy->query_skill(SS_MASTER_TASK);
    rank = MASTER_TITLES[i];
   write("You remove " + CAP(who) + "'s Master "
      + CAP(rank) + " title.\n");
   deputy->catch_msg(QCTNAME(TP) + " relieves you of the task of "
      + "being Master " + CAP(rank) + " of " + deputy->query_company()
      + ".\n");
   write_file(STATUS_LOG, CAP(who) + " was relieved of the Master "
      + CAP(rank) + " position by " + TP->query_name() + ", "
      + ctime(time()) + ".\n");
   return 1;
}

int
assign_master(string str)
{
   object  deputy;
   string  who, 
   spec;
   int     i;
   
   NF("This is only for the Officers to do!\n");
   if (!COUNCIL->is_officer(TP->query_real_name()) &&
         (!this_player()->query_wiz_level()))
   return 0;
   NF("Assign who to have what specialty or Master position?\n");
   if (!stringp(str)) 
      return 0;
   str = lower_case(str);
   NF("Syntax: assign <who> specialty <field>\n"
      + "Or: 'assign <who> specialty master' to promote that "
      + "ranger to Master of his/her specialty.\n");
   if (sscanf(str,"%s specialty %s",who, spec) != 2)
      return 0;
   spec = lower_case(spec);
   deputy = find_player(who);
   NF("That person is not on duty now!\n");
   if (!objectp(deputy) && (spec != "master"))
      return 0;
   if (spec == "master")
      {
      if (objectp(deputy))
         {
         COUNCIL->add_master(CAP(LOW(who)));
         deputy->set_skill(SS_REWARDED, 0);
         deputy->set_skill(SS_PUNISHED, 0);
         deputy->set_master_ranger(1);
         deputy->catch_msg(QCTNAME(TP) + " assigns you the position "
           + "of Master " + MASTER_TITLES[deputy->query_skill(SS_MASTER_TASK)]
            + ".\n");
         write("You assign " + CAP(who) + " to be the Master "
           + MASTER_TITLES[deputy->query_skill(SS_MASTER_TASK)]
           + " of your Company.\n");
         write_file(STATUS_LOG, deputy->query_name() + " was made "
          + "Master " + MASTER_TITLES[deputy->query_skill(SS_MASTER_TASK)] + " by "
           + TP->query_name() + ", " + ctime(time()) + ".\n");
          return 1;
       }
      else return 0;
   }
   NF("That person is not a Ranger!\n");
   if (!IS_RANGER(deputy))
      return 0;
   NF("That Ranger is not a member of your Company.\n");
   if (query_bin_bits(1,16,2,deputy) != query_bin_bits(1,16,2,TP))
      return 0;
   NF("That Ranger is not yet experienced enough to choose a "
      + "specialty.\n");
   if (deputy->query_stat(SS_OCCUP) < SPECIALTY_RANK) return 0;
   i = member_array(CAP(spec), MASTER_TITLES);
   NF("That specialty does not exist, or you spelled it wrongly.\n");
   if (i == -1)
      return 0;
   deputy->set_skill(SS_MASTER_TASK, i);
   deputy->set_skill(SS_REWARDED, 0);
    deputy->set_skill(SS_PUNISHED, 0);
   write("You assign " + CAP(who) + " to become "
      + LANG_ADDART(CAP(spec)) + ".\n");
   deputy->catch_msg(QCTNAME(TP)+" assigns you the new task of being "+
      CAP(spec) + ".\n");
   write_file(STATUS_LOG, deputy->query_name() + " was made "
      + CAP(spec) +
      " by "+TP->query_name()+", "+ctime(time())+".\n");
   return 1;
}

int
mentor(string str)
{
    object  mentor;
    int     ic;

    if (!COUNCIL->query_captain(TP->query_name()) &&
       !COUNCIL->query_lieutenant(TP->query_name()) &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        write_file("/d/Gondor/log/guild", TP->query_name()
          + " tried to make " + str + " a Mentor. "
          + ctime(time()) + ".\n");
        write("Only the Captain or Lieutenant may appoint " +
            "a Mentor of the Rangers.\n");
        return 1;
    }
    if (!strlen(str))
    {
        NF("Whom do you want to assign to be a Mentor?\n");
        return 0;
    }
    str = CAP(LOW(str));
    if (!(mentor = present(LOW(str), ENV(TP))))
    {
            write("You arrange for " + str + " to be appointed a Mentor "
              + "among the Rangers.\n");
            FIX_EUID
            R_SPONSORS->add_can_sponsor(str);
        if (!(mentor = find_player(LOW(str))))
        {
            return 1;
        }
        else
        {
            mentor->set_ranger_mentor(1);
            return 1;
        }
    }
    else
    {
        if (mentor == TP)
        {
            write("You grant yourself the status of Mentor.\n");
        }
        else
        {
            write("You grab " + str + "'s left shoulder in a gesture of honour, "
              + "proclaiming " + mentor->query_objective() + " a Mentor among "
              + "the Rangers.\n");
            mentor->catch_msg(QCTNAME(TP) + " puts a hand on your left shoulder in "
              + "a gesture of honour, and proclaims that you have been granted the "
              + "power to be a Mentor among the Rangers.\n");
            say(QCTNAME(TP) + " puts a hand on " + QTNAME(mentor) + "'s left shoulder "
              + "in a gesture of honour, proclaiming " + mentor->query_objective()
              + " a Mentor among the Rangers.\n", ({ TP, mentor }) );
        }
    }
    FIX_EUID
    mentor->set_ranger_mentor(1);
    R_SPONSORS->add_can_sponsor(str);
    write_file(STATUS_LOG, str + " was made Mentor by " + TP->query_name()
      + ", " + ctime(time()) + ".\n");
    return 1;
}

int
un_mentor(string str)
{
    object  mentor;
    int     ic;

    if (!COUNCIL->query_captain(TP->query_name()) &&
       !COUNCIL->query_lieutenant(TP->query_name()) &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        write_file("/d/Gondor/log/guild", TP->query_name()
          + " tried to remove " + str + " from the Mentor position. "
          + ctime(time()) + ".\n");
        write("Only the Captain or Lieutenant may remove " +
            "someone from Mentor status.\n");
        return 1;
    }
    if (!strlen(str))
    {
        NF("Whom do you want to remove from Mentor status?\n");
        return 0;
    }
    str = CAP(LOW(str));
    if (!(mentor = present(LOW(str), ENV(TP))))
    {
        write("You remove " + str + " from the Mentor "
          + "position among the Rangers.\n");
        FIX_EUID
        R_SPONSORS->remove_mentor(str);
        write_file(STATUS_LOG, str + " was removed from Mentor "
          + "status by " + TP->query_name() + ", " + ctime(time()) + ".\n");

        if (!(mentor = find_player(LOW(str))))
        {
            return 1;
        }
        else
        {
            mentor->set_ranger_mentor(0);
            return 1;
        }
    }
    else
    {
        if (mentor == TP)
        {
            write("You remove your own status of Mentor.\n");
        }
        else
        {
            write("You inform " + str + " that " + mentor->query_pronoun() 
              + " is no longer a Mentor among "
              + "the Rangers.\n");
            mentor->catch_msg(QCTNAME(TP) + " informs you that you no longer "
              + "are to be a Mentor among the Rangers.\n");
            say(QCTNAME(TP) + " informs " + QTNAME(mentor) + " that " 
              + mentor->query_pronoun() + " is no longer "
              + " a Mentor among the Rangers.\n", ({ TP, mentor }) );
        }
    }
    FIX_EUID
    mentor->set_ranger_mentor(0);
    R_SPONSORS->remove_mentor(str);
    write_file(STATUS_LOG, str + " was removed from Mentor status by " + TP->query_name()
      + ", " + ctime(time()) + ".\n");
    return 1;
}

/*
* is_subordinate(who)
* Tests if <who> is of lower rank and subordinate to ThisPlayer.
   * For use in the punishment-commands.
*/
int
is_subordinate(string who)
{
   object  criminal;
   string  how,
   reason;
   int     i, 
   cc, 
   rc, 
   ic, 
   wc;
   
   ic = (COUNCIL)->is_council_member(TP->query_name());
   NF("Only the Ranger Officers may do that.\n");
   if ((ic < G_CPT || ic > I_LT)
         && !COUNCIL->query_sergeant(TP->query_name()))
   {
      if (!TP->query_wiz_level())
      {
	 return 0;
      }
      NF("Only Gondor wizards may do that!\n");
      if (SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
      {
	  write_file(STATUS_LOG, TP->query_name() + " attempted '" + QVB +
	     who + "' without permission. "+ ctime(time()) + ".\n");
	  return 0;
      }
   }
   rc = query_bin_bits(1,16,2,TP);
   who = lower_case(who);
   if (!(criminal = find_player(who)))
      {
      /* If this is an Officer trying to punish someone in another Company */
      NF("The Ranger to be punished or rewarded must either be "
         + "in your Company, or a Ranger pupil.\n");
      if ((member_array(who, RANGER_GUILD->query_company_members(rc)) 
               == -1) && (member_array(who,
               RANGER_GUILD->query_company_members(0)) == -1))
      return 0;
      wc = COUNCIL->is_council_member(CAP(who));
      /* If this is a Ltn. or Sgt. trying to punish a Captain */
      NF("You can neither punish nor reward your Captain.\n"
         + "The only way is to attempt an impeachment in the "
         + "Council.\n");
      if (wc > 0 && wc < G_LT) 
         return 0;
      /* If this is a Sergeant trying to punish a Lieutenant */
      NF("You can neither punish nor reward the Lieutenant.\n"
         + "That is only for the Captain to do.\n");
      if (COUNCIL->query_sergeant(TP->query_name()) 
            && wc > I_CPT && wc <= I_LT)
      return 0;
   }
   else 
      {
      NF("You cannot do that to yourself!\n");
      if (criminal == TP)
         return 0;
      cc = query_bin_bits(1,16,2,criminal);
      /* If this is an Officer trying to punish a non-ranger */
      NF("That person is not a Ranger.\n");
      if (query_bin_bits(1,18,2,criminal) != 1 &&
            query_bin_bits(1,18,2,criminal) != 2)
      return 0;
      
      /* If the Officer tries to punish a Ranger of a different Company */
         NF("The Ranger to be punished or rewarded must either be in "
         + "your Company, or a Ranger pupil.\n");
      if (cc != rc && cc != 0)
         return 0;
      
      /* If this is a Ltn. or Sgt. trying to punish a Captain */
      NF("You can neither punish nor reward your Captain.\n"
         + "The only way is to attempt an impeachmeant in the "
         + "Council.\n");
      if (query_bin_bits(1,18,2,criminal) == 2)
         return 0;
      
      /* If the Sergeant tries to punish the Lieutenant */
      NF("You can neither punish nor reward the Lieutenant.\n"
         + "That is only for the Captain to do.\n");
      if (COUNCIL->query_sergeant(TP->query_name()) &&
            COUNCIL->is_council_member(CAP(who)))
      return 0;
   }
   return 1;
}

int
unpunish_ranger(string str)
{
   object  crim;
   string  who,
   reason;
   NF("Only the Captain or Lieutenant can remove punishments.\n");
   if (query_bin_bits(1,18,2,TP)!=2 &&
    (!COUNCIL->query_lieutenant(TP->query_name())))
   {
      return 0;
   }
   
   NF("Syntax is 'unpunish <ranger> for <reason>'\n");
   if (!strlen(str))
        return 0;
   if (sscanf(str,"%s for %s",who,reason)!=2)
      return 0;
   who = lower_case(who);

   NF("Nothing done.\n");
   if (!is_subordinate(who) &&
     (query_bin_bits(1,18,2,TP)!=2))
   {
      return 0;
   }

   if (!(crim = find_player(who)))
      COUNCIL->add_punishment(who,REM_PUNISH,TP,reason);
   else if (crim->query_skill(SS_PUNISHMENT))
      COUNCIL->remove_punishment(who,TP);
   else 
      {
      write(crim->query_name()+" was not currently punished.\n");
      return 1;
   }
   if (crim)
      write(crim->query_name()+"'s punishment is now removed.\n");
   else
      write(capitalize(who)+" will be cleared of punishment.\n");
   return 1;
}

int
block_ranger(string str)
{
   object  crim;
   string  who,
   reason;
   int     how;
   switch(query_verb())
   {
      case "notrain":
      how = NOTRAIN; break;
      case "notrade":
      how = NOTRADE; break;
      case "noaccess":
      how = NOACCESS; break;
      case "noskills":
      how = NOSKILLS; break;
      case "nospells":
      how = NOSPELLS; break;
      case "noabilities":
      how = NOABILITIES; break;
   } 
   NF("Syntax is '"+query_verb()+" <who> for <reason>'.\n");
   if (sscanf(str,"%s for %s",who,reason)!=2)
      return 0;
   who = lower_case(who);
   NF("Nothing done.\n");
   if (!is_subordinate(who))
      return 0;
   if (!(crim = find_player(who)))
      COUNCIL->add_punishment(who,how,TP,reason);
   else if (crim->query_skill(SS_PUNISHMENT))
      {
      write(crim->query_name()+" was already punished with "
         + PTYPE[crim->query_skill(SS_PUNISHMENT)]+".\n");
   }
   if (crim)
      COUNCIL->execute_block(who,how,TP,reason);
   if (crim)
      write(crim->query_name() + " is now punished with "
      + PTYPE[how]+".\n");
   else
      write(CAP(who) + " will be punished with "+PTYPE[how]+".\n");
   return 1;
}

int
degrade_ranger(string str)
{
   object  crim;
   string  who,
   reason;
   NF("Syntax is 'degrade <who> for <reason>'.\n");
   if (!strlen(str) || sscanf(str,"%s for %s",who,reason)!=2)
      return 0;
   who = lower_case(who);
   NF("Degrade " + CAP(who) + " for what reason?\n");
   if (!strlen(reason))
      return 0;
   NF("Nothing done.\n");
   if (!is_subordinate(who))
      return 0;
   if (!(crim = find_player(who)))
      COUNCIL->add_punishment(who,DEGRADE,TP,reason);
   else
      COUNCIL->do_degrade(who,TP,reason);
   if (crim)
      write(CAP(who) + "'s rank in the Ranger guild "
      + "was degraded.\n");
   else
      write(CAP(who) + "'s rank in the Ranger guild "
      + "will be degraded.\n");
   return 1;
}

int
reward_ranger(string str)
{
   object  pl;
   string  who,
   reason;
   NF("Syntax is 'reward <who> for <reason>'.\n");
   if (!strlen(str))
      return 0;
   if (sscanf(str,"%s for %s",who,reason)!=2)
      return 0;
   who = lower_case(who);
   NF("Reward " + CAP(who) + " for what reason?\n");
   if (!strlen(reason))
      return 0;
   NF("Nothing done.\n");
   if (!is_subordinate(who))
      return 0;
   if (!(pl = find_player(who)))
    {
        if (COUNCIL->add_punishment(who, REWARD, TP, reason) == 2)
        {
            write("Previous punishment/reward cancelled.\n");
            write("Only one can be stored at a time.\n");
        }
    }
   else
      COUNCIL->do_reward(who,TP,reason);
   if (pl)
      write(CAP(who) + "'s rank in the Ranger guild was "
      + "increased.\n");
   else
      write(CAP(who) + " will be rewarded with higher rank "
      + "in the Ranger guild.\n");
   return 1;
}

int
commend_ranger(string str)
{
   object  pl;
   string  who,
   reason;
   NF("Syntax is 'commend <who> for <reason>'.\n");
   if (!strlen(str))
      return 0;
   if (sscanf(str,"%s for %s",who,reason)!=2)
      return 0;
   who = lower_case(who);
   NF("Commend " + CAP(who) + " for what reason?\n");
   if (!strlen(reason))
      return 0;
   NF("Nothing done.\n");
   if (!is_subordinate(who))
      return 0;
   if (!(pl = find_player(who)))
      COUNCIL->add_punishment(who,COMMEND,TP,reason);
   else
      COUNCIL->do_commend(who,TP,reason);
   if (pl)
      write(CAP(who) + "'s rank in the Ranger guild was "
      + "increased slightly.\n");
   else
      write(CAP(who) + " will be rewarded with slightly higher rank "
      + "in the Ranger guild.\n");
   return 1;
}

int
pupilize_ranger(string str)
{
   object  crim;
   string  who,
   reason;
   int     rbit,
   cbit;
   
    if (!strlen(str))
        NFN0("Syntax is 'pupilize <who> for <reason>'.");

   NF("Syntax is 'pupilize <who> for <reason>'.\n");
   if (sscanf(str,"%s for %s",who,reason)!=2)
      return 0;
   rbit = query_bin_bits(1,18,2,TP);
   cbit = query_bin_bits(1,16,2,TP);
   who = lower_case(who);
   NF("Nothing done.\n");
   if (!is_subordinate(who))
      return 0;
   NF("Council-members cannot be made into Ranger pupils "
      + "directly!\n");
   if (COUNCIL->is_council_member(who))
      return 0;
   NF("Only the Captain may make a Ranger a pupil again.\n");
   if (rbit !=2)
      return 0;
   NF("You can only demote Rangers of your own Company back "
      + "to pupil status.\n");
   if (member_array(who,RANGER_GUILD->query_company_members(cbit))==-1)
      return 0;
   if (!(crim = find_player(who)))
      COUNCIL->add_punishment(who,PUPILIZE,TP,reason);
   else COUNCIL->pupilize_ranger(who,TP,reason);
   if (crim)
      write(CAP(who) + " was demoted from your Company to pupil "
      + "status.\n");
   else 
      write(CAP(who) + " will be demoted from your Company to pupil "
      + "status.\n");
   return 1;
}

int
expel_ranger(string str)
{
   object  crim;
   string  who, reason;
   int	ok;
   NF("Syntax is 'expel <who> for <reason>'.\n");
   if (!strlen(str))
      return 0;
   if (sscanf(str,"%s for %s",who,reason) != 2)
      return 0;
   who = lower_case(who);
   NF("Nothing done.\n");
   if (!is_subordinate(who))
      return 0;
   NF("Council-members cannot be directly expelled from the "
      + "guild! Captains must be impeached, while Lieutenants "
      + "and Sergeants must be made ordinary Rangers first.\n");
   if (COUNCIL->is_council_member(who))
      return 0;
   if (!(crim = find_player(who)))
      COUNCIL->add_punishment(who,EXPULSION,TP,reason);
   else
      ok = COUNCIL->expel_ranger(who,TP,reason);
   if (crim )
   {
     if ( ok )
        write(CAP(who) + " was expelled from the Rangers!\n");
     else
	write("For some reason, the expulsion of "+CAP(who)+
	   " failed. Please consult a Gondor wizard.\n");
   }
   else
      write(CAP(who) + " will be expelled from the Rangers!\n");
   R_SPONSORS->remove_pupil(CAP(who));
   return 1;
}

int
ban_ranger(string str)
{
   object  crim;
   string  who,
   reason;
   NF("Only the Captains and Lieutenants can ban people from the guild!\n");

   if (!strlen(str))
   {
       notify_fail("Syntax is 'ban <who> for <reason>'.\n");
       return 0;
   }
   
   if (!COUNCIL->query_captain(TP->query_name()) &&
       !COUNCIL->query_lieutenant(TP->query_name()) &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
        return 0;
   }
   NF("Syntax is 'ban <who> for <reason>'.\n");
   if (sscanf(str,"%s for %s",who,reason) != 2)
      return 0;
   who = lower_case(who);
   NF("Council-members cannot be directly banned from the Rangers!\n");
   if (COUNCIL->is_council_member(who))
      return 0;
   if (!(crim = find_player(who)))
      COUNCIL->add_punishment(who,BAN,TP,reason);
   else
      COUNCIL->ban_ranger(who,TP,reason);
   if (crim)
      write(crim->query_name()+" was banned from the Rangers!\n");
   else
      write(capitalize(who)+" will be banned from the Rangers!\n");
   R_SPONSORS->remove_pupil(CAP(who));
   return 1;
}

int
unban_player(string str)
{
   string  who,
   reason;
   object  crim;
   int     result;

   NF("Only the Captains and Lieutenants can unban people!\n");
    if (!COUNCIL->query_captain(TP->query_name()) &&
       !COUNCIL->query_lieutenant(TP->query_name()) &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
      if (!TP->query_wiz_level()) 
      {
         return 0;
      }
      NF("Only Gondor wizards can do that.\n");
      if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Gondor")
      {
    	write_file(STATUS_LOG, TP->query_name() + " attempted 'unban " +
	   str + "' without permission. " + ctime(time()) + ".\n");
         return 0;
      }
   }
   NF("Syntax: unban <who> for <reason>\n");
   if (!strlen(str))
      return 0;
   if (sscanf(str, "%s for %s", who, reason) != 2)
      return 0;
   who = lower_case(who);
   FIX_EUID
   result = COUNCIL->unban_player(who, TP, reason);
   if (result == 1)
   {
      write("You make it known that " + CAP(who) + " is freed of the ban "
         + "from the Rangers!\n");
      write_file(RANGER_LOG, CAP(who) + " was unbanned by " +
	CAP(TP->query_real_name())
         + ", " + ctime(time()) + ".\n"
         + "  Reason: " + reason + ".\n");
      write_file(STATUS_LOG, CAP(who) + " was unbanned by " +
         CAP(TP->query_real_name()) + ", " + ctime(time()) + ".\n"
         + "  Reason: " + reason + ".\n");
   }
   else
   {
          write("Could not find " + CAP(who) + "!\n");
   }
   return 1;
}

/*
 * Function name:	evict_from_premises
 * Description	:	evict a just-added outlaw from the guildhall
 * Arguments	:	string who -- outlaw's name 
 */
public void
evict_from_premises(string who)
{
    object	pl,
		env;
    string	guild,
		tmp1,
		tmp2;

    if (!objectp(pl = find_living(LOW(who))) ||
	!objectp(env = ENV(pl)) ||
	!sscanf(file_name(env), RANGER_DIR+"%s", guild))
    {
	return;
    }
    if (sscanf(guild, "%s/%s", tmp1, tmp2) == 2)
    {
	guild = tmp1;
    }

    switch (guild)
    {
    case "gondor":
    case "recruithall":
	tmp1 = DRUEDAIN_DIR + "rangerpath3";
	break;
    case "ithilien":
	tmp1 = ITH_DIR + "nforest/fpath/bushes5";
	break;
    default:
	/* "cannot happen" */
	return;
    }

    tell_room(env,
	"A tall muscular ranger arrives.\n"+
	"A young square-faced ranger arrives.\n"+
	"The tall muscular ranger says: You are not welcome here, "+
	    CAP(who)+"!\n");
    tell_object(pl, "The rangers escort you from the room.\n");
    tell_room(env, "The rangers escort "+QTNAME(pl)+" from the room.\n", pl);
    FIX_EUID;
    pl->move_living("M", tmp1);
    tell_room(ENV(pl),
	"Two sturdy rangers escort "+QNAME(pl)+" in, "+
	"then silently depart.\n", pl);
} /* evict_from_premises */

int
outlaw_enemy(string str)
{
   string who,reason;
   object crim;
   int result;
   NF("Only the Captains and Lieutenants can outlaw people!\n");
    if (!COUNCIL->query_captain(TP->query_name()) &&
       !COUNCIL->query_lieutenant(TP->query_name()) &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
       return 0;
   }
   NF("Syntax is 'outlaw <who> for <reason>'\n");
   if (!strlen(str))
      return 0;
   if (sscanf(str,"%s for %s",who,reason) != 2)
      return 0;
   who = lower_case(who);
   FIX_EUID
   result = R_OUTLAW->add_outlaw(who);
   if (result == 1)
      {
      write("You make it known that "+CAP(who)+" is now outlawed "
         + "by the Rangers!\n");
      write_file(RANGER_LOG,CAP(who) + " was outlawed by " 
         + CAP(TP->query_real_name()) + ", " + ctime(time()) + ".\n");
      write_file(STATUS_LOG,CAP(who) + " was outlawed by " 
         + CAP(TP->query_real_name()) + ", " + ctime(time()) + ".\n");
      evict_from_premises(who);
   }
   else if (result == -1)
      {
      write("It is impossible to outlaw " + CAP(who) + ".\n");
   }
   else
      write(CAP(who) + " is already outlawed by the Rangers.\n");
   return 1;
}

int
pardon_outlaw(string str)
{
   string  who,
   reason;
   object  crim;
   int     result;
   NF("Only the Captains and Lieutenants can pardon outlaws!\n");
    if (!COUNCIL->query_captain(TP->query_name()) &&
       !COUNCIL->query_lieutenant(TP->query_name()) &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
   {
       return 0;
   }
   NF("Syntax: rpardon <who> for <reason>\n");
   if (!strlen(str))
      return 0;
   if (sscanf(str, "%s for %s", who, reason) != 2)
      return 0;
   who = lower_case(who);
   result = R_OUTLAW->remove_outlaw(who);
   if (result == 1)
      {
      write("You make it known that " + CAP(who) + " no longer is outlawed "
         + "by the Rangers!\n");
      write_file(RANGER_LOG, CAP(who) + " was pardoned by " + CAP(TP->query_real_name())
         + ", " + ctime(time()) + ".\n"
         + "  Reason: " + reason + ".\n");
      write_file(STATUS_LOG, CAP(who) + " was pardoned by " +
         CAP(TP->query_real_name()) + ", " + ctime(time()) + ".\n"
         + "  Reason: " + reason + ".\n");
   }
   else if (result == -1)
      {
      write("It was impossible to pardon " + CAP(who) + "!\n");
   }
   else
      {
      write(CAP(who) + " was not an outlaw!\n");
   }
   return 1;
}

/*
* rangertell <message>
*
* This will tell a message to all rangers present.
* Only available for wizards
*/
int
rangertell(string str)
{
   object *players;
   int     i,
   busy;
   string *told_rangers = ({ }),
   *busy_rangers = ({ }),
   *names = ({ }),
   who;
   
   if (!(TP->query_wiz_level()))
      {
      NF("You aren't a wizard, so you cannot do that.\n");
      return 0;
   }
   if (!strlen(str))
      {
      NF("What do you want to tell all rangers?\n");
      return 0;
   }
   
   players = users();
   for (i = 0; i < sizeof(players); i++)
   {
      if ((TP == players[i]) || (!(IS_RANGER(players[i]))))
         continue;
      busy = (int)players[i]->query_prop(WIZARD_I_BUSY_LEVEL);
      if (busy & 2 || busy & 8 || busy & 16 || busy & 128)
         {
         busy_rangers += ({ CAP(players[i]->query_real_name()) });
        }
      else
         {
         players[i]->catch_msg("Suddenly " + TP->query_name() 
            + " appears to you and tells you:\n" + BSN(str));
         if (!(players[i]->query_wiz_level()))
            players[i]->catch_msg("You may 'reply' if you wish "
            + "to.\n");
         names = players[i]->query_prop(PLAYER_AS_REPLY_WIZARD);
         who = TP->query_real_name();
         if (pointerp(names))
            names = ({ who }) + (names - ({ who }));
         else
            names = ({ who });
         players[i]->add_prop(PLAYER_AS_REPLY_WIZARD, names);
         told_rangers += ({ CAP(players[i]->query_real_name()) });
        }
   }
   
   if (sizeof(busy_rangers))
      {
      write(BSN("The following ranger(s) is/are busy: "
            + COMPOSITE_WORDS(busy_rangers) + "."));
   }
   if (sizeof(told_rangers))
      {
      write(BSN("You told the following ranger(s): "
            + COMPOSITE_WORDS(told_rangers) + "."));
      if (TP->query_option(OPT_ECHO))
         write("You told all rangers:\n" + BSN(str));
   }
   else
      write("Except yourself, there are no rangers playing.\n");
   return 1;
}

/*
* rangerupdate
*
* Call update_hooks() in all rangers.. Especially handy if you patch the
* soul and somepeople have buggy souls.
* Only wizards can do this.
*/
int
rangerupdate(string str)
{
   object *players;
   int     i;
   string *told_rangers = ({ });
   
   if (!(TP->query_wiz_level()))
      {
      NF("You aren't a wizard, so you cannot do that.\n");
      return 0;
   }
   
   players = users();
   for (i = 0; i < sizeof(players); i++)
   {
      if (!(IS_RANGER(players[i])))
         continue;
      players[i]->update_hooks();
      told_rangers += ({ CAP(players[i]->query_real_name()) });
   }
   
   write(BSN("You update the cmdsoul-hooks from the following "
         + "Rangers: " + COMPOSITE_WORDS(told_rangers) + "."));
   
   return 1;
}
