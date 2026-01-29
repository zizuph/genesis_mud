inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"
/* by Korat */
create_monster()
{
   ::create_monster();
   set_name("grunch");
   add_name("beggar");
   set_race_name("human");
   set_adj("dirty");
   set_long("This wretched human peers at you with a hunger-stricken expression, "+
      "trying to create a feeling of pity in you. "+
      "Except from the long, thin outstretched hands that clings to a "+
      "small wooden bowl, the only other part you see of his body is his "+
      "bony face that frames those huge begging eyes. You cannot but feel sorry for this "+
      "poor sod.\n");
   set_stats(({30,20,25,20,20,25}));
   set_alignment(800);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_act_time(2);
   add_act("robepolish");
   add_act("robeshiver");
   add_act("robewipe");
   add_act("bbeg");
   add_act("bnap");
   add_act("bsearch");
   add_act("say Gimme some money ... pleeeaaasse ...");
   add_act("say Im soooo hungry!");
   add_act("say Do you have some money spare? I could have use for them "+
      "... a copper or two? A platinum ??");
   set_knight_prestige(-8);
   set_title(", an unfortunate poor soul");
   add_speak("Gimme some money? Please??\n");
   trig_new("%w 'drops' %s","react_grab");
   trig_new("%w 'gives' %s","react_give");
}

arm_me()
{
   object wep,arm;
   arm = clone_object("/d/Kalad/common/central/arm/bgrobe");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/obj/club_bowl");
   wep -> move(TO);
   MONEY_MAKE_CC(random(5)+1)->move(TO,1);
   command("wimpy feeling very well");
}

int
react_grab(string who, string dummy)
{
   if (who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_grab",who);
      return 1;
   }
}

int
react_sulk(string who, string dummy)
{
   if (who)
      {
      who = lower_case(who);
      set_alarm(1.0,0.0,"return_sulk",who);
      return 1;
   }
}

void
return_grab(string who)
{
   object obj;
   int ran;
   if (obj = present(who, environment()))
      {
      command("bgrab");
      command("say Ohhh...thanx!");
      command("bempty");
   }
}

void
return_sulk(string who)
{
   object obj;
   int ran;
   if (obj = present(who, environment()))
      {
      command("poke "+QCTNAME(obj));
      command("say hey! What about me??");
      command("bbeg");
   }
}

react_give(string who,string what)
{
  object obj;
   if (who) who=lower_case(who);
   if (obj=present(who,environment()))
   {
      command("say Ohh, thank you Master. May your money pouch be "+
        "blessed and your generousity doubled.");
      command("thank "+lower_case(obj->query_real_name()));
   }
}

int
react_attack(string who, string dummy)
{
   object obj;
   if(who)
      who = lower_case(who);
   if(obj = present(who, environment())){
      command("ack");
      command("say Im sorry! I will never beg you for money...ever!!");
      command("panic");
   }
   return 1;
}
