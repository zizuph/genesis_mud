/* 
 * /d/Kalad/common/wild/pass/npc/mo_leader.c
 * Purpose    : A mountain ogre leader
 * Located    : /d/Kalad/common/wild/pass/desert/mount/o*
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
   set_name("leader");
   add_name("ogre leader");
   set_race_name("ogre");
   set_adj("horrific");
   set_short("ogre leader");
   set_long("A particularly large and disgustingly smelly brute of an ogre. "+
      "By the disgusting trophies it has arrayed itself with, it would appear to "+
      "hold an important position in its so-called society.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 75 + random(60));
   set_base_stat(3, 55);
   set_base_stat(4, 50);
   set_base_stat(5, 90);
   set_alignment(-500);
   set_knight_prestige(500);
   set_skill(SS_WEP_CLUB,80);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,40);
   set_act_time(6);
   add_act(({"say Ugly bugs!","kill human"}));
   add_act("growl");
   add_act("tackle all");
   add_act("grin");
   add_act("fart");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("snarl all");
   add_cact("say I crush you with rock!");
   add_cact("laugh evil");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
}
void
my_stuff()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(obj/throw_rock));
   item -> move(TO);
   command("wear all");
   item = clone_object(CPASS(wep/mol_club));
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(5))->move(TO,1);
   MONEY_MAKE_CC(random(75))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("say Ye stupid " + TP->query_nonmet_name() + "!");
      command("say Me eat you now!");
      command("kill " + (ob->query_real_name()));
   }
}

public void
introduce_me(string who)
{
    object obj;

    if(!(obj = present(who, environment()))) return;
    command("slap "+obj->query_real_name());
    command("smirk malev");
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
