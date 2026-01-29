inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define DO_I_TELL_RUMOURS "_do_i_tell_rumours"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   add_prop(DO_I_TELL_RUMOURS,1);
   set_default_answer("The shopkeeper says: I know nothing of that.\n");
   add_ask(({"knights","thanar"}),"The shopkeeper whispers: They are a "+
      "dangerous cult of fanatics that will stop at nothing to keep out the "+
      "foreigners, especially those that are not human!\n");
   add_ask(({"trading company","company"}),"The shopkeeper whispers: They "+
      "are among the most powerful groups in the city, since they control "+
      "nearly all of Kabal's trade with the rest of Kalad.\n");
   add_ask(({"egore"}),"The shopkeeper says: Hmm, isn't that the slave overseer?\n");
   add_ask(({"help"}),"The shopkeeper says: Eh? Help you with what?\n");
   set_name("anthios");
   set_race_name("half-elf");
   set_adj("middle-aged");
   set_long("This man looks to be almost human, but not quite. The pointed "+
      "ears and slightly slanted eyes seem to mark him as an elf. You can "+
      "only assume that he is some sort of half-breed!\n");
   set_stats(({75,100,75,125,125,75}));
   set_alignment(1000);
   set_skill(SS_AWARENESS,100);
   set_title("the Retired Adventurer");
   set_act_time(3);
   add_act("say Welcome to my shop!");
   add_act("smile all");
   add_act("emote looks lovingly at his shop.");
   add_act("say Beware the Knights of Thanar...");
   add_act("say Don't go wandering into the Trading Company, they might "+
      "not like you and you'll end up in some alley somewhere...\n");
   add_speak("I know of many things...the wise should listen to my words.\n");
   set_knight_prestige(-1000);
   add_prop(OBJ_M_NO_ATTACK,"Now why would you want to do that?\n");
   trig_new("%w 'drops' %s","react_drop");
}
int
react_buy(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_buy",who);
      return 1;
   }
}
void
return_buy(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("say Thank you for purchasing from my shop!");
      command("smile " + (obj->query_real_name()));
   }
}
int
react_sell(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_sell",who);
      return 1;
   }
}
int
return_sell(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("smile " + (obj->query_real_name()));
   }
}
int
react_drop(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}
void
return_drop(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("poke " + (obj->query_real_name()));
      command("say You dropped something.");
   }
}