/* by Korat */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "coalquest"

int coal;
string long;
object dwarf;

/* function do_say: filters sentances according to 
 *                  listeners language skill.
 * Arguments:
 *                  Arg: the sentance to be filtered.
 */
public int
do_say(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the local jargon?\n");
      return 0;
   }
   
   filter(all_inventory(environment(this_object())) - ({ this_object() }),
      "do_it", this_object(), arg);
   return 1;
}

/* Function do_it: Does the actual filtering of the text.
 * arguments: who - all who can hear the npc
 *            arg - the sentence to be filtered.
*/
public int
do_it(object who, string arg)
{
   int i;
   string text;
   string dummy;
   if (!living(who))
      return 0;
   
   /* listeners with above 50 in language or dwarven with above 40
   understands it perfectly */
   if ((who->query_race_name() == "dwarf" && who->query_skill(SS_LANGUAGE) > 40) ||
        who->query_skill(SS_LANGUAGE) > 50)
   {
      tell_object(who, TO->query_The_name() + " growls "+
         "in the local dwarven jargon: " + arg + "\n");
      return 1;
   }
   
   /* listeners with less than 20 in language doesn't
   understand anything */
   if(who->query_skill(SS_LANGUAGE) < 20)
      {   
      tell_object(who, TO->query_The_name() + " growls "+
         "some harsh sounds. You find it utterly unconprehensable.\n");
      return 1;
   }
   
   /* remove vocals from arg according to ss_language skill */
   
   text="";
   for (i=0;i<strlen(arg);i++)
   {
      dummy=extract(arg,i,i);
      if(dummy != "a" && dummy !="e" && dummy != "i" &&
         dummy != "o" && dummy != "u" && dummy !="s" && dummy != "y")
      text=text+dummy;
      else
         {
         if (random(who->query_skill(SS_LANGUAGE)-20)>10)
            text=text+dummy;
         else
         {
            switch(random(4))
            {
               case 0: text=text+"x"; break;
               case 1: text=text+"r"; break;
               case 2: text=text+"gh"; break;
               case 3: text=text+"z"; break;
               default: text=text+"r"; break;
            }
         }
      }
   }
   tell_object(who, TO->query_The_name() + " growls "+
      "something in the local dwarven jargon. You manage to catch this: "+
      text+".\n");
   return 1;
}

void
create_monster()
{
   set_name("rhoy");
   add_name("deep dwarf");
   set_race_name("dwarf");
   set_adj("dirty");
   set_short("dirty deep dwarf");
   set_long("This deep dwarf is covered in layers of coal dust "+
      "that has coagulated with the help of his sweat in this "+
      "hot room.\n");
   set_stats(({100,40,50,30,40,50}));
   set_alignment(500);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,30);
   set_title("coal-shuffler in Underhome's Smith");
   set_act_time(3);
   add_act("emote shovels some coal into the fire.");
   add_act("emote wipes some sweat of his brow.");
   add_act("emote pushes his shovel into the pile of coal.");
   add_act("emote stretches his back.");
   add_act("emote shovels more coal into the fire.");
   set_cact_time(3);
   add_cact("shout HEEEELPP!!");
   add_cact("emote tries to hit you with his shovel but misses.");
   add_speak("Can you help me? We need more coal, and fast! "+
      "The war we are in demands piles of new weapons, and that means "+
      "more coal to fuel the furnace.\n");
   
   set_knight_prestige(-5);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}

/* This npc gives out a quest. He wants some coal brought to him */
public void
enter_inv(object ob, object from)
{
   if(MASTER_OB(ob) == "/d/Kalad/common/wild/pass/dwarf/obj/coal_dust")
      {
      ::enter_inv(ob, from);
      do_say("We cannot use this ... this is dust!");
      set_alarm(3.0,0.0,"drop_the_object",ob);
      return;
   }
   if(MASTER_OB(ob) != "/d/Kalad/common/wild/pass/dwarf/obj/coal")
      {
      ::enter_inv(ob, from);
      set_alarm(3.0,0.0,"drop_the_object",ob);
      return;
   }

   if(!interactive(from))
      return;
   else
      set_this_player(from);
   if(from->test_bit("Kalad",2,4))
      {
      do_say(query_The_name(from) + " says: You got more to me! Thanks!!");
   }
   else
      {
      do_say("Thank you! Now our supply of coal is a "+
         "bit better. Each handful helps.");
      TO->command("thank "+from->query_real_name());
      TP->catch_msg("You feel a little more experienced!\n");
      TP->add_exp(500);
      TP->set_bit(2,4);
      seteuid(getuid(TO));
      log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " " +
         capitalize(TP->query_real_name()) + " rewarded with 500 xp, "+
         "<"+TP->query_average_stat()+"> average stats.\n");
   }
   ::enter_inv(ob, from);
   set_alarm(3.0,0.0,"remove_the_object",ob);
}

void
drop_the_object(object ob)
{
   command("drop all");
}

void
remove_the_object(object ob)
{
   ob->remove_object();
   tell_room(E(TO),"The deep dwarf throws the coal into the fire.\n");
}