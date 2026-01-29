/*                                      */
/*    The fortune teller's assistant.   */
/*                                      */
/*                 -Rico 24.01.95       */
/*                                      */

inherit "/d/Kalad/std/monster";

#include "/d/Kalad/defs.h"
#include <money.h>
#include <macros.h>

create_monster()
{
   ::create_monster();
   
   set_name("assistant");
   set_race_name("human");
   set_adj("bored");
   add_adj("assistant");
   
   set_short("assistant sitting at the desk");
   set_long("This is the fortune teller's assistant. "+
      "She looks extremely bored. She is sitting at "+
      "the desk waiting to give out tickets to "+
      "anyone wishing to give her ten silver coins "+
      "for one.\n");
   
   set_stats(({ 45, 45, 50, 50, 30, 40 }));
   
   set_alignment(0);
   
   set_appearance(10);
   
   set_gender(G_FEMALE);
   
   set_act_time(3);
   add_act("yawn");
   add_act("stretch");
   add_act("say What a boring job.");
   add_act("say I should get another job, I'm going to pot in "+
      "this one.\n");
   
   add_speak("Only ten silver coins for a ticket to see the "+
      "great and world renown fortune teller, Isla!\n");
   
   trig_new("%w 'gives' 'you' '10' 'silver coins' %s", "react_ticket");
   
}

int
react_ticket(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(3.0, 0.0, "return_ticket", who);
      return 1;
   }
}

void
return_ticket(string who)
{
   object obj;
   int ran;
   
   if(obj = present(who, environment()))
   {
         object obj;
         
         setuid();
         seteuid(getuid());
         
         obj = clone_object(MRKT_PATH(obj/ticket01));
         obj -> move(this_object());
         
         command("give ticket to " +  obj->query_nonmet_name());
         command("There you go, " + obj->query_nonmet_name() + 
            ", I hope your fortune is told to your liking.\n");
         command("emote puts the money in a safe under her desk.\n");
    }
} 
