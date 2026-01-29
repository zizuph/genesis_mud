inherit "/std/monster";
#include <language.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
void
create_monster() {
   set_name("linda");
   set_race_name("gnome");
   set_adj("naked");
   set_adj("obese");
   set_title("the bitch, Barmaid of the Master");
   set_long("This is a short, squat, highly obese little " +
      "gnome.  She serves these wyrmmen for some reason or " +
      "another;  might be a slave.  Probably is their hore.\n");
   set_gender(1);
   set_aggressive(0);
   set_whimpy(50);
   set_alignment(50);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   set_skill(SS_AWARENESS, 100);
   default_config_mobile(20);
   add_act("emote serves a wyrmman a Chang-er grog.");
   add_act("emote serves a wyrmman a Meat wine.");
   add_act("emote is mounted by a wyrmman for a quickie.");
   add_act("emote is mounted by two wyrmmem for a quickie.");
   add_act("emote bends over exposing her anus.");
   add_act("emote asks you:  Would you like a Quickie?");
   add_act("say I charge five coppers per Quickie.");
   add_act("emote goes about her business.");
   trig_new("%s 'gives' 'you' 'five' 'copper' %s","part_nude");
   trig_new("%s 'introduces' %s","intro_me");
   set_alarm(0.0,0.0,"get_disease");
}
get_disease() {
   seteuid(geteuid());
   clone_object("/d/Rhovanion/mute/dungeon1/disease.c")->move(TO);
   return 1;
}
part_nude() {
   if (TP->query_gender() > 0)
      {
      write("Linda unbuckles your pants to take a look, but " +
         "doesn't find the right parts!");
      say(QCTNAME(TP) + " has her pants unbuckled by Linda who, " +
         "in shock, doesn't find the right parts!");
      set_alarm(1.0,0.0,"part_female");
      return 1;
   }
   command("say Thank you.  I think you're sexy!");
   command("emote hides the coins on her nude body.");
   set_alarm(2.0,0.0,"part_nude2");
   return 1;
}
part_nude2() {
   command("emote hops up onto a table and assumes the " +
      "position.");
   set_alarm(1.0,0.0,"part_nude3");
   return 1;
}
part_nude3() {
   write("Linda unbuckles your pants.\n");
   say(QCTNAME(TP) + " has his pants unbuckled by Linda!\n");
   set_alarm(2.0,0.0,"part_nude4");
   return 1;
}
part_nude4() {
   write("You mount Linda!\n");
   say(QCTNAME(TP) + " mounts Linda in a ferocious " +
      "display of manhood.\n");
   command("moan");
   set_alarm(5.0,0.0,"part_nude5");
   return 1;
}
part_nude5() {
   command("emote makes sexy grunting noises.");
   write("You and Linda are still going at it.\n");
   say(QCTNAME(TP) + " is getting it on with Linda " +
      "at a tremendous speed.\n");
   set_alarm(10.0,0.0,"part_nude6");
   return 1;
}
part_nude6() {
   command("moan");
   write("You slump to the ground and sigh as you finish " +
      "your quickie with Linda.\n");
   say(QCTNAME(TP) + " groans and lets out a humiliating " +
      "cry as he slumps to the ground gyrating in a " +
      "quivering heap of flesh.\n");
   set_alarm(2.0,0.0,"part_nude7");
   return 1;
}
part_nude7() {
   command("say Next!");
   command("give disease to " + TP->query_real_name());
   clone_object("/d/Rhovanion/mute/dungeon1/disease.c")->move(TO);
   return 1;
}
intro_me() {
   set_alarm(1.0,0.0,"intro_me2");
   return 1;
}
intro_me2() {
   command("introduce myself");
   return 1;
}
part_female() {
   command("say No problem...");
   write("Linda pulls out a long, wooden spoon and proceeds " +
      "to give you pleasure!\n");
   say(QCTNAME(TP) + " giggles with glee as Linda pulls out " +
      "her long, wooden spoon and proceeds to please " + QCTNAME(TP)
      + ".\n");
   set_alarm(5.0,0.0,"part_female2");
   return 1;
}
part_female2() {
   command("emote giggles merrily as she skillfully operates " +
      "her long, wooden spoon.");
   write("You are receiving pleasure.\n");
   say(QCTNAME(TP) + " moans with pleasure!\n");
   set_alarm(5.0,0.0,"part_female3");
   return 1;
}
part_female3() {
   command("emote withdraws her spoon and hides it on her " +
      "nude body.");
   write("You fall to the floor well-pleased.\n");
   say(QCTNAME(TP) + " falls to the floor moaning and " +
      "heaving, trying to re-clothe herself.\n");
   set_alarm(2.0,0.0,"part_nude7");
   return 1;
}
