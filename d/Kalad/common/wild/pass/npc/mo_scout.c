/* 
 * /d/Kalad/common/wild/pass/npc/mo_scout.c
 * Purpose    : An ogre scout
 * Located    : /d/Kalad/common/wild/pass/desert/mount/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(7);
   if(i < 1)
      return "vicious";
   else if(i < 2)
      return "brutal";
   else if(i < 3)
      return "malicious";
   else if(i < 4)
      return "cruel";
   else if(i < 5)
      return "savage";
   else if(i < 6)
      return "malevolent";
   else
      return "horrible";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   string extra;
   extra = random_extra();
   set_name("ogre");
   set_race_name("ogre");
   set_adj(extra);
   set_long("A hulking brutish figure that vaguely reminds you of those "+
      "stories told long ago of cave men. That remembrance is rudely "+
      "disrupted when you gaze upon its inhuman face, one filled with two "+
      "gigantic and uneven tusks, two large black eyes and a puggish nose.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 100 + random(50));
   set_base_stat(3, 50);
   set_base_stat(4, 50);
   set_base_stat(5, 100);
   set_alignment(-750);
   set_knight_prestige(750);
   set_aggressive(1);
   set_skill(SS_WEP_CLUB,90);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,60);
   set_skill(SS_AWARENESS,50);
   set_act_time(6);
   add_act(({"say Me smash little people!","kill human"}));
   add_act("growl");
   add_act("tackle all");
   add_act("grin");
   add_act("fart");
   add_act("get all from corpse");
   set_cact_time(1);
   add_cact("snarl all");
   add_cact("say I'll feed ya to my stomach!");
   add_cact("laugh evil");
   add_cact("scream");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
}
void
my_stuff()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(wep/mo_club));
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_CC(random(50))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote laughs with malicious glee!");
      command("grin " + TP->query_race_name());
      command("kill " + (ob->query_real_name()));
   }
}

public void
introduce_me(string who)
{
    command ("spit");
    command ("say Get out of way, maggot.");
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
