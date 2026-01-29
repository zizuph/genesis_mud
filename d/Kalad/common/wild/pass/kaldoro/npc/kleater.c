/* 
 * /d/Kalad/common/wild/pass/kaldoro/npc/kleater.c
 * Purpose    : Kaldoro's banking clerk.
 * Located    : ../rooms/bank.c
 * Created By : Rico 3.Jan.95
 * Modified By: 
 * NOTE       : Still needs lots of work.
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "/d/Kalad/defs.h"

create_monster()
{
   ::create_monster();
 
   set_name("kleater");
   set_race_name("gnome");
   set_adj("ancient");
   set_adj("bald");

   set_long("This is Kleater Munnygrubber, Kaldoro's "+
      "resident banking clerk.  Actually, he owns this "+
      "bank, but don't tell anyone, he thinks it's a "+
      "secret.  He looks to be ancient beyond imagine, "+
      "but you can tell he is very crafty and has "+
      "immeasurable experience in the dealings of "+
      "cash.  He obviously commands your respect.\n");

   set_stats(({ 95, 130, 100, 120, 120, 70 }));

   set_alignment(300);
   set_knight_prestige(-600);
 
   set_skill(SS_AWARENESS,100);
   set_skill(SS_UNARM_COMBAT, 100);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_DEFENCE, 100);

   set_title("Munnygrubber, resident banking clerk");
   set_gender(G_MALE);

   set_act_time(3);
   add_act("say Ahh...this is the life...");
   add_act("say How may I be of service to you?");
   add_act("think the old days");
   add_act("yawn");
   add_act("stretch");
   add_act("emote greedily eyes your pockets.");
   add_act("emote rubs his hands together in anticipation.");

   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'giggles' %s", "react_giggle");
   trig_new("%w 'laughs' %s", "react_giggle");
   trig_new("%w 'bows' %s", "react_bow");
   trig_new("%w 'waves' %s", "react_wave");
   trig_new("%w 'takes' %s", "react_take");
   trig_new("%w 'gets' %s", "react_take");
   trig_new("%w 'destructs' %s", "react_wizard");
   trig_new("%w 'fetches' %s", "react_wizard");
   trig_new("%w 'patched' %s", "react_wizard");
   trig_new("%w 'patched' %s", "react_wizard");

   add_prop(OBJ_S_WIZINFO,("This npc really has nothing to "+
      "do with the function of 'his' bank.  PC's, though, "+
      "should find him a nice little amusing fellow.\n"));

   call_out("arm_me", 1);
}

void
arm_me()
{
   object arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/caravan/arm/mbgslarm");
   arm -> move(this_object());
   arm = clone_object("/d/Kalad/common/caravan/arm/mbgloves");
   arm ->  move(this_object());
   arm = clone_object("/d/Kalad/common/caravan/arm/mbgboots");
   arm -> move(this_object());

   command("wear all");

   MONEY_MAKE_PC(random(2))->move(TO, 1);
   MONEY_MAKE_GC(random(10))->move(TO, 1);
   MONEY_MAKE_SC(random(100))->move(TO, 1);
   MONEY_MAKE_CC(random(200))->move(TO, 1);
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
         command("smile " + from->query_real_name());
         break;
      case 2:
         command("say a "+
            capitalize(LANG_ADDART(check_call(what->short())))+
            ", my favourite!");
            break;
      case 3:
         command("say I will examine this, "+
            from->query_race() + ".");
         command("smile warmly");
   }
   orig = function_exists("create_object", what);
   if(orig == "/std/weapon")
   {
      command("say Eeeeks!! A weapon!!");
      say(QCTNAME(this_object()) + " breaks the "+
         what->short() + "!\n");
      what->remove_object();
      return;
   }
   if(orig == "/std/armour")
   {
      command("say An armour? I have no need of this!");
      say(QCTNAME(this_object()) + " breaks the "+
         what->short() + "!\n");
      what->remove_object();
    return;
   }
   if(orig == "/std/drink")
   {
      command("say Yummy!! Booze!!");
      command("drink " + what->query_name());
      command("drop bottle");
      command("burp");
      return;
   }
   if(orig == "/std/food")
   {
      command("say Food!! Thanks, I was a mite peckish!");
      command("smile warmly");
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
       command("say Life is great, isn't it, "+
            obj->query_nonmet_name()+ "?\n");
      if(ran == 1)
         command("smile at " + who);
      if(ran == 2)
         command("say It is great to see you smiling, "+
         obj->query_nonmet_name() + ".\n");
   }
}

int
react_giggle(string who, string dummy)
{
   if(who)
   {
      who = lower_case(who);
      call_out("return_giggle", 3, who);
      return 1;
   }
}

void
return_giggle(string who)
{
   object obj;
   int ran;

   if((obj = present(who, environment()))
      && (!(obj->query_npc())))
   {
      ran = random(3);
      if(ran == 0)
         command("say Funny, eh "+
            obj->query_nonmet_name() + "?\n");
     if(ran == 1)
         command("say Ahh, "+
            LANG_PWORD(obj->query_race())+
            " are such merry people.\n");
      if(ran == 2)
         command("giggle");
   }
}

int
react_bow(string who, string dummy1)
{
   if(who)
   {
      who = lower_case(who);
      call_out("return_bow", 3, who);
      return 1;
   }

}

void
return_bow(string who)
{
   command("bow " + who);
}

int
react_wave(string who, string dummy1)
{
   if(who)
   {
      who = lower_case(who);
      call_out("return_wave", 3, who);
      return 1;
   }
}

void
return_wave(string who)
{
   command("wave");
}

int
react_take(string who, string what)
{
   if(who)
   {
      who = lower_case(who);
      call_out("return_take", 3, ({ who, what }));
      return 1;
   }
}

return_take(string *two)
{
   object obj;
   int ran;
   string who, what;
  

   who  = two[0];
   what = two[1];

   if((obj = present(who, environment()))
      && (!(obj->query_npc())))
   {
      ran = random(3);
      if(ran == 0)
         command("say Why did you take " + what);
      if(ran == 1)
         command("say You took it just before I could!\n");
      if(ran == 2)
         command("say Please, can I have " + what);
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
         command("say Nice to meet you, "+
            obj->query_name() + ".\n");
         command("bow to " + who);
         command("introduce myself");
         command("introduce buffy");
      }
      if(ran == 1)
      { 
         command("bow to " + who);
         command("introduce myself");
         command("introduce buffy");
         command("say Well met, " + 
            obj->query_name() + ".\n");
      }
      if(ran == 2)
      { 
         command("say Be welcome here, "+
            obj->query_name() + ".\n");
         command("introduce myself");
         command("introduce buffy");
         command("bow to " + who);
      }
   }
}
