//
// shepherd's wife - has the shears needed to shear the sheep
//
// Zima  - May 18, 1998
//
// Refactored, Tapakah, 08/2021
//
#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit BASE_NPC;

void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/apron",
               "/d/Khalakhor/common/arm/bonnet",
               "/d/Khalakhor/common/arm/dress" });
  ::arm_me();
}
 
void check_ob(object ob, object from)
{
  string obj=(ob->query_name());
  if (!interactive(from))
    return;
  if (ob->id("shears")) {
    command("say Ah, thank ye! I'll be needin' these soon!");
    command("emote puts the "+obj+" in her apron pocket.");
    ob->remove_object();
  }
  else {
    command("say I can naugh' take yer charity! We're a proud family!");
    command("give "+obj+" to "+(lower_case(from->query_name())));
    command("drop "+obj);
    command("say But I appreciate yer charitable thoughts.");
  }
}
 
//
// enter_inv - accept only shears
//
void enter_inv(object ob, object from)
{
  set_alarm(3.0,0.0,&check_ob(ob,from));
  ::enter_inv(ob,from);
}
 
//
// borrow - respond to request to borrow shears.
//
string
borrow ()
{
  if (!MONEY_ADD(TP,-12))
    return ("say Ye can't have 'em for free! Don't ye have 12 coppers?");
 
  TP->catch_msg("You give some money to "+QTNAME(TO)+".\n");
  tell_room(ENV(TO),QCTNAME(TP)+" gives some money to "+QTNAME(TO)+
            ".\n",TP);
  command("emote takes some shears from her apron pocket.");
  clone_object(WEP+"sheep_shears")->move(TO);
  command("give shears to "+lower_case(TP->query_name()));
  command("drop shears");
  command("say Thar ye are. Now return 'em to me or ye'll have "+
          "bad luck!");
  command("say They're cursed, they are! Me mather's a witch ye know.");
  return ("smile evilly");
}
 
void
create_khalakhor_human ()
{
  explicit_name="ceile";
  ::create_khalakhor_human();

  set_gender(1); // female
  add_name(({"wife","shepherd"}));
  set_adj("lean");
  add_adj("red-haired");
  set_long("She is the wife of the shepherd and mother of the family which "+
           "lives here. Lean and tall, her red hair reflects her fiery "+
           "personality.\n");
 
  default_config_npc(40);
  set_skill(SS_AWARENESS, 45);
  set_skill(SS_UNARM_COMBAT, 40);
  set_skill(SS_DEFENCE, 40);
  set_skill(SS_PARRY,   40);
  set_skill(SS_WEP_KNIFE, 50);
 
  set_act_time(60);
  add_act("emote cleans some dishes and puts them away.");
  add_act("say Whar is that man!? He must be sleepin' w' the sheep now!");
  add_act("emote cleans the fireplace with a wet rag.");
  add_act("shout You kids better not go over the bridge, ya hear!");
  add_act("shout Go tell yar Pa its nigh to supper time!");
  add_act("emote wipes her hands on her apron.");
  add_act("emote combs her red hair with her skinny fingers.");
  add_act("emote adjusts the bonnet on her head.");
  add_act("emote puts a pair of sheep shears away.");
 
  set_default_answer("I dunno that. Perhaps you could ask me husband?");
  add_ask("sheep",
          "say Aye, those be our sheep in yonder pasture. Wooly they are!",1);
  add_ask(({"wool","for wool","how wool","how to get wool","buy wool"}),
          "say Ye can shear the sheep if ye have a pair of shears.",1);
  add_ask(({"shear","shears","how to shear","for shears"}),
          "say Ask me to borrow me shears, and ye can, for 12 coppers mind "+
          "ye.",1);
  add_ask(({"spin","cord","for cord","spin cord","to spin cord","make cord",
            "to make cord"}),
          "say I'm no seamstress! Ye can find one in tha village.",1);
  add_ask(({"village","tabor sogh","Tabor Sogh"}),
          "say The village of Tabor Sogh is southeast of here, nigh "+
          "to the sea.",1);
  add_ask(({"borrow","to borrow shears","to borrow her shears",
            "to borrow your shears","borrow shears"}),
          borrow, 1);
  add_ask(({"husband","where husband","where is husband"}),
          "say He be in the fields with the sheep I imagine.",1);
 
  set_alignment(200);
  set_exp_factor(75);
  set_size_descs("tall", "of normal width");
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
}
 
void
hook_return_intro_new (string str)
{
  command("say Pleased to meet ye!");
  command("say Me be "+query_name()+" the Shepherd's wife!");
  command("say Hope yer travels have been well!");
}
