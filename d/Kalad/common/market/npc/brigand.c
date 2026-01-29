/*                               */
/*       A sneaky brigand.       */
/*                               */
/*         -Antharanos           */
/*         -Modified by Rico     */
   /*             25.01.95          */
/*                               */

inherit "/d/Kalad/std/monster";

#include "/d/Kalad/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>

create_monster()
{
   ::create_monster();
   
   set_name("brigand");
   set_race_name("human");
   set_adj("sneaky");
   
   set_short("sneaky brigand");
   set_long("An unshaven human that smells strongly of "+
      "liquor and the outdoors. Clearly he must be living "+
      "in these surrounding forests, since the clothes he "+
      "wears are nothing but crudely sewn animal skins. "+
      "He'll probably leave as soon as you give him some "+
      "money. "+
      "\n");
   
   set_stats(({ 65, 85, 80, 55, 55, 80 }));
   
   set_aggressive(1);
   
   set_alignment(-250);
   set_knight_prestige(250);
   
   set_skill(SS_WEP_CLUB,75);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,60);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_HIDE,45);
   
   set_act_time(4);
   add_act("smile greedily");
   add_act("say Gimme all yer loot!");
   add_act("say If ya don't gimme yer stuff, I'll have to beat you "+
      "senseless!\n");
   add_act("get all from corpse");
   
   set_cact_time(4);
   add_cact("say If you give me some coins I'll leave...");
   add_cact("say Now you're gonna get it!");
   add_cact("say The vultures will have a feast of yer corpse!");
   add_cact("kick all");
   
   add_speak("Hello, gimme all yer loot...or I'll kill ya.\n");
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   
   trig_new("%w 'gives' 'you' %s", "react_leave");
   
   call_out("arm_me",1);
}

void
arm_me()
{
   object wep;
   
   seteuid(getuid(this_object()));
   wep = clone_object("/d/Kalad/common/wild/pass/wep/bclub");
   wep -> move(this_object());
   
   command("wield all");
   
   MONEY_MAKE_SC(random(50))->move(TO, 1);
   MONEY_MAKE_GC(random(2))->move(TO, 1);
}

intreact_leave(string who, string dummy)
{
   if (who)
      {
      who = lower_case(who);
      call_out("return_leave", 3, who);
      return 1;
   }
}

void
return_leave(string who)
{
   object obj;
   int ran;
   
   if(obj = present(who, environment()))
      {
      command("smirk");
      command("say Thanks for the stuff, " + obj->query_nonmet_name() +
         ".\n");
      command("east");
      command("east");
      command("south");
      command("crawl under wagon");
      command("southwest");
      command("hide");
   }
}
