/* 
 * /d/Kalad/common/wild/pass/npc/bed_child.c
 * Purpose    : A bedellin child
 * Located    : /d/Kalad/common/wild/pass/camp/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
/* by antharanos */
create_monster()
{
   ::create_monster();
   set_name("child");
   set_race_name("human");
   set_adj("young");
   add_adj("bedellin");
   set_short("young bedellin child");
   set_long("A young Bedellin child, despite the intense heat he looks like "+
      "he's having fun playing.\n");
   set_stats(({10,15,12,5,5,10}));
   set_alignment(600);
   set_random_move(10);
   set_act_time(9);
   add_act("smile merr");
   add_act("emote jumps around the room happily.");
   add_act("tickle all");
   add_act("say I'll be a brave warrior when I grow up!");
   add_act("emote pretends to fight a fierce desert monster.");
   add_act("giggle");
   add_act("emote sucks his thumb.");
   set_knight_prestige(-6);
   set_default_answer("The child looks like he's too young to understand "+
      "anything you might ask.\n");
   add_ask(({"sheik","musalim","tribe","iriphawa","bedellin"}),
      "The child says: Um, why don't you ask someone older?\n");
   add_speak("My daddy is missing, and so is my brother.\n");
   add_prop(LIVE_I_NEVERKNOWN,1);
   trig_new("%w 'arrives.' %s", "react_arrive");
   trig_new("%w 'pats' 'you' %s", "react_pat");
}
int
react_arrive(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("say Why look! Its a nice " + obj->query_nonmet_name() + ".");
      command("ask " + (obj->query_real_name()) + " Wanna play with me?");
   }
}
int
react_pat(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_pat",who);
      return 1;
   }
}
void
return_pat(string who){
   {
      command("smile shyly");
   }
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob,environment()))
      {
      command("scream");
      command("kill " + (ob->query_real_name()));
   }
}
