/* 
 * /d/Kalad/common/wild/pass/kaldoro/npc/sprokter.c
 * Purpose    : Sprokter, Kleater's body guard and pal.
 * Located    : ../rooms/bank.c
 * Created By : Rico 3.Jan.95
 * Modified By: 
 * NOTE       : Still needs plenty of work.
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "/d/Kalad/defs.h"

create_monster()
{
   ::create_monster();
 
   set_name("sprokter");
   set_race_name("goblin");

   set_adj("scarred");
   set_adj("mean");
   set_adj("killer");

   set_long("This is Sprokter Kilmoor, a very unlikely "+
      "buddy of Kleater.  You wonder how it is that a "+
      "goblin and a gnome became best of friends in "+
      "the first place.  It is pretty plain to you "+
      "that if you mess with one, you mess with both "+
      "of them.  Judging by the look of Sprokter, you "+
      "are pretty sure that you wouldn't want to "+
      "anyway.\n");

   set_stats(({ 180, 170, 180, 60, 60, 130 }));

   set_appearance(-90);

   set_alignment(-100);
   set_knight_prestige(100);
 
   set_skill(SS_AWARENESS, 20);
   set_skill(SS_UNARM_COMBAT, 60);
   set_skill(SS_BLIND_COMBAT, 40);
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_PARRY, 80);
   set_skill(SS_WEP_CLUB, 100);
   set_skill(SS_SPELLCRAFT, 30);

   set_title("Kilmoor the Shadowbend Ripper");
   set_gender(G_MALE);

   set_act_time(5);
   add_act("say Me hobbit friend.");
   add_act("say Don't even t'ink of mess'n wit us!");
   add_act("think cooking you fer dinner...");
   add_act("grin");
   add_act("fart");
   add_act("glare all");
   add_act("cpound");
   add_act("impress");
   add_act("emote picks some flesh from his teeth.");
   add_act("emote belches mightilly. You can almost feel the "+
      "ground vibrate beneath your feet.\n");
   add_act("emote shoves a finger deep into his nostril, "+
      "pulls out a huge, bloody greener and pops it into "+
      "his mouth.\n");

   set_cact_time(3);
   add_cact("say You little shit! I'll squash ya wit me bare "+
      "hands!\n");
   add_cact("emote pisses on you as you rush past in a vain "+
      "attept to grab him in a choke hold!\n");
   add_cact("Ah toldja not ta mess wit us!");
   add_cact("Ah gonna eat you fer supper...");
   add_cact("fortify");
   add_cact("scream all");
   add_cact("spit at all");
   add_cact("cackle sadistically at all");

   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'destructs' %s", "react_wizard");
   trig_new("%w 'fetches' %s", "react_wizard");

   call_out("arm_me", 1);
}

void
arm_me()
{
   object arm;
   object wep;

   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/caravan/arm/mbgslarm");
   arm -> move(this_object());
   arm = clone_object("/d/Kalad/common/caravan/arm/mbgloves");
   arm ->  move(this_object());
   arm = clone_object("/d/Kalad/common/caravan/arm/mbgboots");
   arm -> move(this_object());

   command("wear all");

   wep = clone_object(KALDORO(wep/pet_club));
   wep -> move(this_object());

   command("wield all");

   MONEY_MAKE_PC(random(3))->move(TO,1);
   MONEY_MAKE_GC(random(25))->move(TO,1);
   MONEY_MAKE_SC(random(200))->move(TO, 1);
   MONEY_MAKE_CC(random(500))->move(TO, 1);
}

void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
   {
      command("say Scum!! No hurt me friend!!");
      command("knee " + lower_case(ob->query_real_name()));
      command("kill " + lower_case(ob->query_real_name()));
   }
}

init_living()
{
   int ran;
   object who;
   
   who = this_player();

   if(living(who) && (!(who->query_npc())))
      call_out("return_enter", 3, who->query_real_name());
}

void 
enter_inv(object what, object from)
{
   ::enter_inv(what, from);

   if(!from)
      return;

   call_out("thank_chat", 1, ({ from, what }));
}

void 
thank_chat(object *arr)
{
   object from, what;
   int ran;
   string orig;
   
   ran = random(4);

   from = arr[0];
   what = arr[1];

   if(!from||!what)
      return;

   switch(ran)
   {
      case 0:
         command("say Ah, thank you.");
         command("thank " + from->query_real_name());
         break;
      case 1:
         command("say a "+
            capitalize(LANG_ADDART(check_call(what->short())))+
            ", I've always wanted one.");
         command("grin " + from->query_real_name());
         break;
      case 2:
         command("say a "+
            capitalize(LANG_ADDART(check_call(what->short())))+
            ", my favourite!");
            break;
      case 3:
         command("say I will examine this, "+
            from->query_race() + ".");
         command("smile demonically");
   }
   orig = function_exists("create_object", what);
   if(orig == "/std/weapon")
   {
      command("say Aaahh!! A weapon!!");
      say(QCTNAME(this_object()) + " doesn't think he needs "+
         "to use the " + what->short() + ".\n");
      what->remove_object();
      return;
   }
   if(orig == "/std/armour")
   {
      command("say An armour? I have no need of this!");
      say(QCTNAME(this_object()) + " breaks the "+
         what->short() + ".\n");
      what->remove_object();
      return;
   }
   if(orig == "/std/drink")
   {
      command("say Yummy! Booze!");
      command("drink " + what->query_name());
      command("drop bottle");
      command("burp");
      return;
   }
   if(orig == "/std/food")
   {
      command("say Aahh! Food...");
      command("grin");
      command("eat " + what->query_name());
      return;
   }
}

int
react_smile(string who, string dummy)
{
   if(who)
   {
      who = lower_case(who);
      call_out("return_smile", 3, who);
      return 1;
   }
}

void
return_smile(string who)
{
   object obj;
   int ran;

   if((obj = present(who, environment()))
      && (!(obj->query_npc())))
   {
      ran = random(3);
      if(ran == 0)
         command("say Ahh... even ah likes to smile "+
            "sometimes, "+
               obj->query_nonmet_name() + ".\n");
      if(ran == 1)
         command("smile at " + who);
      if(ran == 2)
         command("say Eees great ta see ya smiling, "+
         obj->query_nonmet_name() + ".\n");
   }
}

int
react_wizard(string who, string dummy1)
{
   if(who)
   {
      who = lower_case(who);
      call_out("return_wizard", 3, who);
      return 1;
   }
}

return_wizard(string who)
{
   object obj;
   int ran;

   if((obj = present(who, environment()))
      && (!(obj->query_npc())))
   {
      ran = random(3);
      if(ran == 0)
         command("say Oooooh! What great magic, "+
            obj->query_race() + " wizard!");
      if(ran == 1)
      {
         command("grovel " + who);
         command("say Please leave me in one piece, "+
            "mighty wizard!\n");
         command("emote whimpers pitifully.\n");
      }
      if(ran==2)
         command("shiver");
         command("say Wizardry is beyond me.  I "+
            "watch in awe!\n");
   }
}

public void
introduce_me(string who)
{
   object obj;
   int ran;

   if((obj = present(who, environment()))
      && (!(obj-> query_npc())))
   {
      ran = random(3);
      if(ran == 0)
      {
         command("say Ya tink ah care who you eees, "+
            obj->query_name() + "?\n");
         command("finger " + who);
         command("introduce myself");
      }
      if(ran == 1)
      { 
         command("grin at " + who);
         command("introduce myself");
         command("say Wanna scrap, " + 
            obj->query_name() + "?\n");
      }
      if(ran == 2)
      { 
         command("say Piss off, "+
            obj->query_name() + "!\n");
         command("introduce myself");
         command("spit at " + who);
      }
   }
}
