/* 
 * /d/Kalad/common/wild/pass/npc/mo_chief.c
 * Purpose    : The mountain ogre chief, holds the mara run
 * Located    : /d/Kalad/common/wild/pass/desert/mount/o5
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   int i;
   ::create_monster();
   set_name("scrunge");
   set_race_name("ogre");
   set_adj("magnificent");
   add_adj("terrible");
   set_long("The most disgustingly filthy creature you've ever had the "+
      "misfortune of laying eye upon. By the hideous trophies it adorns "+
      "itself with, it can only be the chieftain of this foul group of "+
      "ogres.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 100 + random(50));
   set_base_stat(3, 65);
   set_base_stat(4, 65);
   set_base_stat(5, 100);
   set_alignment(-750);
   set_knight_prestige(800);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,60);
   set_skill(SS_2H_COMBAT,50);
   add_act(({"say Lets kill some more humans!","kill human"}));
   add_act("growl");
   add_act("tackle all");
   add_act("grin");
   add_act("fart");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("snarl all");
   add_cact("say I'll feed ya to my stomach!");
   add_cact("laugh evil");
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   trig_new("%w 'drops' %s","react_drop");
}
void
my_stuff()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(arm/moc_armour));
   item -> move(TO);
   item = clone_object(CPASS(obj/throw_rock));
   item -> move(TO);
   command("wear all");
   item = clone_object(CPASS(wep/moc_club));
   item -> move(TO);
   command("wield all");
   item = clone_object(CPASS(obj/mara_rune));
   item -> move(TO);
   MONEY_MAKE_PC(random(3))->move(TO,1);
   MONEY_MAKE_GC(random(10))->move(TO,1);
   MONEY_MAKE_SC(random(50))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("say Ye stupid " + TP->query_nonmet_name() + "!");
      command("say Now you die!!!");
      command("kill " + (ob->query_real_name()));
   }
}

public void
introduce_me(string who)
{
    object obj;
    if(!(obj = present(who, environment()))) return;
    command("spit "+(obj->query_real_name()));
    command("say I will punish your pretentious ways, fool "+(obj->query_race_name())+".");
    command("kill "+(obj->query_real_name()));
}

int
react_drop(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}
void
return_drop(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("get all coins");
      command("grin greed");
   }
}
