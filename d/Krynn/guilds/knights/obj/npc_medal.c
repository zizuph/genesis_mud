/* The Paladine medal for the Solamnian Knight guild. */

#pragma save_binary

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <composite.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <state_desc.h>


int knight_level; /* The level of the knight */
int knight_sublevel; /* The sublevel of the knight */
int pres_decay; /* The alarm that decays prestige */
int generous; /* Will the knight be generous and not kill his enemies? */
int primary; /* Which is the primary hand of the knight: 0-right, 1-left */


void
create_object()
{
   if (!IS_CLONE)
      return;
   
   knight_level = 0;
   knight_sublevel = 0;
   set_name("tunic");
   add_name("pal_med");
   set_short("tunic of the Knighthood");
   set_long("This elegant tunic is embroidered with the symbols of "+
      "the Knighthood. Having been given it when you became a member "+
      "of the Knights, you have worn it since. To get help on the guild "+
      "use 'help guild help'.\n");
   
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   set_no_show_composite(1);
}

string
query_auto_load() 
{ 
   return MASTER_OB(this_object()) + ":" + knight_level + " " +
   knight_sublevel + " " + generous + " " + primary; 
}

/******************************************************************************
*           KNIGHTS have a special invite command!
* Black Knights may not lead a team (invite) at all! Knights who have recently
* Pkilled have a skill set with the age. They may not lead a team for 2 days
* (AGE!) or until a conclave or assistant has pardoned them.
* This function was moved to the medal from it's original location
* in the soul because it was not called before the other invite
* command from the soul. Additionally, it was modified to allow
   * Knights of the Rose to lead anyone, regardless of dis comparisons. 
* Nov 95 by Morrigan
*****************************************************************************/
int
invite(string name)
{
   object         *member_list, member;
   
   /* this is the knight specific part */
      
   /* if (TP->query_knight_level() == L_BROSE)  */
      //Line above doesn 't seem to cut it, using int instead of macro
   if (TP->query_knight_level() == 1)
      {
      write("Knights of the Black Rose have disgraced the Knights of Solamnia " +
         "and may not lead any teams.\n");
      return 1;
   }
   if (REALAGE(TP) < TP->query_skill(SS_DISGRACED))
      {/* 2 days playing time! */
      write("You have disgraced the Knights of Solamnia and may not lead a team currently.\n");
      return 1;
   }
   else
      TP->remove_skill(SS_DISGRACED);
   
   /* end knight specific part */
      
   if (!name)
      {
      member_list = (object *) this_player()->query_invited();
      if (!member_list || !sizeof(member_list))
         write("You have not invited anyone to join you.\n");
      else
         {
         if (sizeof(member_list) == 1)
            write("You have invited " + member_list[0]->short() +
            ".\n");
         else
            {
            name = (string) COMPOSITE_FILE->desc_live(member_list);
            write("You have invited " +
               (string) LANG_FILE->word_num(sizeof(member_list)) +
               " people:\n");
            write(break_string(name, 76, 3));
         }
       }
      return 1;
   }
   member = find_player(name);
   
   if (!member || (member && !present(member, environment(this_player()))))
      {
      notify_fail(capitalize(name) +
            " is not a good potential team member!\n");
      return 0;
   }
   if (!CAN_SEE(this_player(), member))
      {
      notify_fail("Invite whom?");
      return 0;
   }
   if (this_player()->query_leader())
      {
      notify_fail("You can't be a leader when you have a leader!\n");
      return 0;
   }
   if ((!member->query_met(this_player())) ||
         (!this_player()->query_met(member)))
   return (notify_fail("You have not been introduced!\n"), 0);
   
   if (member == this_player())
      {
      notify_fail("You do not need an invitation to your own team!\n");
      return 0;
   }
   this_player()->team_invite(member);
   member->catch_msg(this_player()->query_The_name(member) +
      " invites you to join " + this_player()->query_possessive() +
      " team.\n");
   this_player()->reveal_me(1);
   member->reveal_me(1);
   
   write("Ok.\n");
   return 1;
}

/* Modified Nov 95 by Morrigan and Aridor to enable the primary command */
   void
init_arg(string str)
{
   int i = sscanf(str, "%d %d %d %d", knight_level, knight_sublevel,
      generous, primary);
   if (i < 2)
      {
      knight_level = 0;
      knight_sublevel = 0;
      generous = 0;
      primary = 0;
   }
   else if (i == 2)
      {
      generous = 0;
      primary = 0;
   }
   else if (i == 3)
      primary = 0;
   
   if (TP->test_bit("Krynn", 1, 3) == 1)
      {
      knight_level = 1;
   }
}

void
init()
{
   if (!MEMBER(TP) && !LAYMAN(TP))
      return;
   seteuid(getuid(TO));
   
   add_action("invite", "invite");
   set_alarm(1.0,0.0,"set_tax", 0);
   set_alarm(3.0,0.0,"soul", TP);
   set_alarm(5.0,0.0,"adjust_wimpy", TP);
   set_alarm(7.0,0.0,"check_actions", TP);
   
/* if (!TP->query_wiz_level()) */
/* pres_decay = set_alarm(600.0,600.0,"decay_prestige"); */
}

/* Function name: check_actions
* Description:   If the player is in the action list of the admin room,
*                take the appropriate actions.
*/
void
check_actions(object who)
{
   (ADMIN)->check_action_pending(who);
}

/*
* Function name: soul
* Description:   Add the toolsoul and spell object to the member
*/
void
soul(object ob)
{
   int i;
   string *souls;
   
   seteuid(getuid(TO));
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
   ob->remove_cmdsoul(souls[i]);
   ob->add_cmdsoul(KNIGHT_SOUL);
   for (i = 0; i < sizeof(souls); i++)
   if (souls[i] != KNIGHT_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
   
}

/* adjust the wimpy level for those knights that have it too high
*/
void
adjust_wimpy(object ob)
{
   string how;
   int i = ob->query_whimpy();
   int j = WIMPY_LIMIT[knight_level] + WIMPY_LIMIT2[knight_sublevel];
   if (i > j)
      {
      i = j;
      if (i > 99)
         i = 99;
      ob->catch_msg("Your current wimpy level is not allowed for a " +
         "Knight of Solamnia!\n");
      how = SD_HEALTH[sizeof(SD_HEALTH) * i / 100];
      ob->catch_msg("You are now wimpy at: '" + how + "'.\n");
      ob->set_whimpy(i);
   }
}

/*
* Function name: set_knight_level
* Description:   Set which level the knight has
*/
void 
set_knight_level(int level) 
{ 
   object ob = E(TO);
   
   seteuid(getuid(TO));
   
   /* Nothing to do if level hasn't changed or is illegal. */
      if (level == knight_level || level < 1 || level > 5)
      return;
   
   if (knight_level == 1 && level > 3)
      level = 3;
   
   /*
   if (ob->test_bit("Krynn",1,2) && level > 2)
      level = 2;
   
   if (level == 5 && !ob->test_bit("Krynn",1,10))
      level = 4;
   
   if (level == 4 && !ob->test_bit("Krynn",1,9))
      level = 3;
   */
   
   knight_level = level;
   
   if (knight_level == 1)
      ob->set_bit(1,3);
   else
      {
      ob->clear_bit(1,3);
      
      if (knight_level == 2 || knight_level == 3)
         ob->clear_bit(1,4);
      else
         ob->set_bit(1,4);
      
      if (knight_level == 2 || knight_level == 4)
         ob->clear_bit(1,5);
      else
         ob->set_bit(1,5);
   }
   
   (ADMIN)->add_knight(ob->query_real_name(), knight_level, LAYMAN(ob));
   TO->set_tax(0);
}

/*
* Function name: set_knight_sublevel
* Description:   Set which sublevel the knight has
*/
void 
set_knight_sublevel(int sublevel) 
{ 
   knight_sublevel = sublevel; 
}

/*
* Function name: query_knight_level
* Description:   Ask about the knights level
*/
int 
query_knight_level() 
{ 
   return knight_level; 
}

/*
* Function name: query_knight_sublevel
* Description:   Ask about the knights sublevel
*/
int 
query_knight_sublevel() 
{ 
   return knight_sublevel; 
}

/*
* Function name: set_tax
* Description:   Update the tax of the member
*/
void
set_tax(int i)
{
   int stat, old_tax, new_tax;
   object ob;
   
   ob = E(TO);
   if (!knight_sublevel)
      {
      ob->set_skill(SS_PRESTIGE_ST,
         ob->exp_to_stat(ob->query_skill(SS_PRESTIGE_ACC)));
      stat = ob->query_skill(SS_PRESTIGE_ST);
      if (stat < 20 && !ob->query_skill(SS_PRESTIGE_ACC))
         {
         ob->set_skill(SS_PRESTIGE_ST, 20);
         ob->set_skill(SS_PRESTIGE_ACC, 20 * 20 * 20 + 100);
         stat = 20;
       }
      
      if (ob->test_bit("Krynn", 1, 4) == 0)
         {
         if (ob->test_bit("Krynn", 1, 5) == 0)
            knight_level = 2;
         if (ob->test_bit("Krynn", 1, 5) == 1)
            knight_level = 3;
       }
      
      if (ob->test_bit("Krynn", 1, 4) == 1)
         {
         if (ob->test_bit("Krynn", 1, 5) == 0)
            knight_level = 4;
         if (ob->test_bit("Krynn", 1, 5) == 1)
            knight_level = 5;
       }
      
      
      if (ob->test_bit("Krynn",1 ,3) == 1)
         knight_level = 1;
      
      if (knight_sublevel && !ob->query_skill(SS_PRESTIGE_ACC))
         {
         ob->set_skill(SS_PRESTIGE_ACC, ob->query_acc_exp(SS_OCCUP));
         ob->set_skill(SS_PRESTIGE_ST,
            ob->exp_to_stats(ob->query_skill(SS_PRESTIGE_ACC)));
       }
      
      knight_sublevel = L_1;
      if (stat >= SS_LEVEL1)
         knight_sublevel = L_2;
      if (stat >= SS_LEVEL2)
         knight_sublevel = L_3;
      if (stat >= SS_LEVEL3)
         knight_sublevel = L_4;
      if (stat >= SS_LEVEL4)
         knight_sublevel = L_5;
      if (stat >= SS_LEVEL5)
         knight_sublevel = L_6;
      if (stat >= SS_LEVEL6)
         knight_sublevel = L_7;
      if (stat >= SS_LEVEL7)
         knight_sublevel = L_8;
      if (stat >= SS_LEVEL8)
         knight_sublevel = L_9;
      if (stat >= SS_LEVEL9)
         knight_sublevel = L_10;
      
      if ((ADMIN)->query_conclave("crown") == ob->query_name()
            || (ADMIN)->query_conclave("sword") == ob->query_name()
         || (ADMIN)->query_conclave("rose") == ob->query_name())
      knight_sublevel = 11;
   }
   
   new_tax = TAX[knight_level];
   
   if (knight_level > 3)
      new_tax += 2;
   if (knight_level == 3 && knight_sublevel > 8)
      new_tax += 2;
   old_tax = ob->query_learn_pref(SS_OCCUP);
   if (new_tax != old_tax)
      ob->set_guild_pref(SS_OCCUP, new_tax);
   
   if (!ob->query_guild_member_lay() && ob->query_learn_pref(SS_LAYMAN))
      ob->set_guild_pref(SS_LAYMAN, 0);
   
   if (!ob->query_guild_member_race() && ob->query_learn_pref(SS_RACE))
      ob->set_guild_pref(SS_RACE, 0);
}

/* if the player isn't devoted to Paladine remove some prestige
   * once in a while
*/
/*
void
decay_prestige()
{
   object who = E(TO);
   int when = who->query_prop(KNIGHT_I_DEVOTION);
   
   if (!who || !interactive(who))
      return;
   
   if (when < who->query_age())
      {
      if (who->query_skill(SS_PRESTIGE_ACC) > 2000)
         who->change_prestige((MEMBER(who) ? -200 : -40),1); 
   }
   else
      who->change_prestige(3); 
}
*/

int
query_generous()
{
   return generous;
}

void
set_generous(int what)
{
   generous = what;
}

int
query_primary()
{
   return primary;
}

void
set_primary(int what)
{
   primary = what;
}
