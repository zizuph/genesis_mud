/* 
 * /d/Kalad/common/wild/pass/npc/water_sprite.c
 * Purpose    : A water sprite, guards the urn for a quest
 * Located    : /d/Kalad/common/wild/pass/desert/oasis/u1
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
object watersprite;
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("mylena");
   set_race_name("sprite");
   set_adj("delicate");
   add_adj("water");
   set_long("A tiny figure no higher than a man's knee. The delicate "+
      "blue-skinned creature has the form of a thin wisp of a girl, with "+
      "hair an outlandish green in color. Her sky blue eyes gaze out at "+
      "you with joy and lovingness.\n");
   set_stats(({25,50,15,50,50,15}));
   set_alignment(500);
   set_knight_prestige(-5);
   set_gender(G_FEMALE);
   set_skill(SS_UNARM_COMBAT,25);
   set_skill(SS_DEFENCE,25);
   set_skill(SS_AWARENESS,50);
   set_act_time(6);
   add_act("bounce");
   add_act("smile");
   add_act("cheer");
   add_act("say I'm so happy you came to visit me!");
   set_cact_time(3);
   add_cact("ack");
   add_cact("stomp");
   add_cact("explode");
   set_default_answer("Umm...what was the question again?\n");
   add_ask(({"urn","urn of rata","rata's urn"}),
      "I know where it is...do you?\n");
   add_speak("What follows you wherever you may go, no matter how hard "+
      "you try, yet is not to be found when the moon doth shine? "+
      "If you know the answer, whisper it to me...if you are right, I "+
      "shall let you know...if not I shan't respond.\n");
   add_prop(CONT_I_WEIGHT,10000);
   add_prop(CONT_I_VOLUME,10000);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(LIVE_I_SEE_DARK,1);
   add_prop(LIVE_I_SEE_INVIS,1);
}

void
return_riddle(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("shake");
      command("say That's not right!");
      set_alarm(6.0,0.0,"urn",who);
   }
}

/* Routine catch_whisper introduced by Mercade to get rid of obsolete trig_new
 * on whispering.
 */
void
catch_whisper(string str)
{
    if (str == "sun" || str == "the sun")
    {
        set_alarm(2.0, 0.0, &return_riddle(this_player()->query_real_name()));
    }
}

void
urn(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("say Just kidding!");
      command("emote loudly whispers: You'll find the urn down below!");
      command("smile cheer");
      command("wave " + (obj->query_real_name()));
      command("emote slips into the pool of water and is gone.");
      if(watersprite = present("mylena", environment(TP)))
         {
         watersprite -> remove_object();
      }
   }
}