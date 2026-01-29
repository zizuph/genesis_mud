inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

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

/* by Korat */

void
create_monster()
{
   set_name("broxii");
   add_name("deep dwarf");
   set_race_name("dwarf");
   set_adj("strong");
   set_short("strong deep dwarf");
   set_long("This is a blacksmith, a craftsman in forging and "+
      "mending armours. During these dark times, he works almost "+
      "all day and night to provide the deep dwarves with their "+
      "shields, mails and other armours.\n");
   set_stats(({160,70,100,60,50,100}));
   set_alignment(500);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,70);
   set_title("blacksmith of the Deep Dwarves in Underhome");
   set_act_time(1);
   add_act("emote hammers on a piece of red-hot metal.");
   add_act("emote drops the halfmade shield into the water-basin. The room "+
      "fills with hot steam as it hits the water with a sizzling sound.");
   add_act("emote gets a shield from the basin and puts it into the furnace.");
   add_act("emote fetches his tools and picks up a glowing piece of metal "+
      "from the furnace.");
   add_act("emote wipes the sweat from his brow.");
   add_act("emote hammers hard on a piece of metal. Sparks flies out.");
   add_act("emote shuffles a bit in the furnace with his tools. The heat "+
      "increases.");
   add_act("emote wipes some sweat of his brow.");
   add_act("emote stretches his back.");
   add_speak("Maybe you could help us out, stranger? I would appreciate "+
      "any weapon or armour of mithril you can offer!\n");
   set_knight_prestige(-5);
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   add_prop(OBJ_M_NO_ATTACK,"You decide against it.\n");
}