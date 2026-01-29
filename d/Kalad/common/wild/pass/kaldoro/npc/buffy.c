/* 
 * /d/Kalad/common/wild/pass/kaldoro/npc/buffy.c
 * Purpose    : Buffy, Kleater's pet pooch.
 * Located    : ../rooms/bank.c
 * Created By : Rico 05.Jan.95
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";

#include "/d/Kalad/defs.h"

create_monster()
{
   ::create_monster();
 
   set_name("buffy");
   set_race_name("dog");
   set_adj("golden");
   set_adj("fluffy");

   set_long("This is Kleater's pet pooch.  Perhaps, "+
      "if you are nice, he will introduce her to "+
      "you\n");

   set_stats(({ 15, 60, 40, 30, 10, 30 }));

   set_alignment(800);
 
   set_appearance(100);

   set_title("faithful companion of Kleater");
   set_gender(G_FEMALE);

   set_act_time(3);
 
   add_act("stretch");
   add_act("emote pants happilly.");
   add_act("emote starts to clean herself.");
   add_act("snuggle kleater");
   add_act("lick kleater");
   add_act("lick all");
   add_act("emote tugs on your pant leg for attention.");
   add_act("emote eats the treat.");
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
   {
      command("growl all");
      command("snuggle kleater");
      command("emote barks at you viciously.");
      command("emote tries to bite your leg.");
   }
}
