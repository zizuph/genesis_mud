/* Andrea the chicken chef */
/* Created By Stevenson */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit M_FILE

string pee_quest();
string dunno();
create_krynn_monster()
{
   int i;
   
   set_name("andrea");
   set_living_name("andrea");
   set_long("She is very busy frying up chicken for the Highlord.\n");
   set_race_name("human");
   
   set_default_answer(VBFC_ME("dunno"));
   CUTLEFTOVER("heart");
   LEFTOVER("lip");
   CUTLEFTOVER("hair");
   
   add_cact("emote throws hot grease on you.");
   add_cact("shout Help! Help! Help! I'm being attacked by some "
      + QRACE(TP) + "!");
   add_cact("emote kicks you in your shins.");
   
   add_ask(({"ingredient","ingredients","about ingredient",
            "about ingredients"}), VBFC_ME("pee_quest"));
   add_act("emote grabs a chicken and plucks it with lightning speed.");
   add_act(({"say My chicken recipe is a secret.","say It is made with "
            + "13 secret herbs and spices."}));
   add_act("emote drops another piece of chicken into the cooker.");
   add_act("emote looks at you happily.");
   add_act("say Hmmm... I seem to be out of some ingredients.");
   add_act("emote searches around the kitchen for something.");
   add_act("say I have so many chickens I decided to prepare some " +
           "hardboiled eggs. I definitely don't need more chicks!");
   add_act("say I have just learned how to bake and stuff a whole chicken! " +
           "please, try it out! It is simply delicious.");
   add_act("say I hope the Highlord likes my cooking... Hadn't complained so far.");
   add_act("say Last cook ended up in Thanoi pot. How horrible! What did he do?");

   set_act_time(2);
   
   set_knight_prestige(-3);
   
   set_gender(1);
   for (i = 0; i < 6; i++)
   set_base_stat(i, 15+random(5));
   set_alignment(170);
   
   set_all_attack_unarmed(10, 8);
   set_all_hitloc_unarmed(2);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   add_prop(NPC_I_NO_LOOKS,1);
   add_prop(LIVE_I_ALWAYSKNOWN, 1);
}

string 
pee_quest()
{
   if (TP->test_bit("Krynn",PEEBITS)) {
      write("You have already done this quest.\n");
      return "";
   }
   
   command("blush");
   command("whisper "+TP->query_real_name()+ " Actually, what "
      + "I need is my "
      + "SECRET ingredient: the one I need to make my chicken taste "
      + "extra special.");
   command("whisper "+TP->query_real_name()
      + " It is 'essence of polar bear' and it "
      + "may be found somewhere out on the icy plains.");
   TP->add_prop("_on_pee_quest",1);
   return "";
}

string 
dunno()
{
   command("emote looks confused.");
   command("say I'm not that kind of a girl!");
   return "";
}

void 
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (from)
      set_alarm(1.0,0.0,"do_quest",ob, from);
}

void 
do_quest(object ob, object from)
{
   object chicken;
   
   if (from->query_prop("_on_pee_quest") &&
         ob->id("pee")) 
   {
      command("hug "+from->query_real_name());
      command("whisper "+from->query_real_name()
         + " Now don't you go out and give away the secret, "
         + "ya hear?");
      command("wink "+from->query_real_name());
      K_QUEST_LOG("quest", "Pee Quest", from, PEEQUEST);
      from->remove_prop("_on_pee_quest");
      from->set_bit(PEEBITS);
      from->add_exp(PEEQUEST);
      from->catch_msg("You feel more experienced.\n");
      ob->remove_object();
      chicken=clone_object(ICE_CAST_O+"chicken");
      chicken->move(from,1);
      command("say Here's one on the house.");
      from->catch_msg("Andrea gives you a piece of chicken.\n");
      tell_room(E(TO),"Andrea gives a piece of chicken to "
         + QCNAME(from) + ".\n", from);
      return;
   }
   set_alarm(1.0,0.0,"command","give "+ob->query_name()
      + " to " + from->query_real_name());
   set_alarm(1.5,0.0,"command","say I don't want that.");
}

