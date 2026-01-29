inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
object gobking;
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("nomog");
   add_name("king");
   set_race_name("goblin");
   set_adj("giant");
   add_adj("demonic");
   set_long("An incredibly gigantic goblin, so large is he that you "+
      "can't help but wonder if ogre blood runs in his veins. Just from "+
      "the unnerving scrutiny he studies you with, it becomes clear that "+
      "this is the iron-fisted ruler of this tribe of goblins.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 125 + random(25));
   set_base_stat(3, 75);
   set_base_stat(4, 65);
   set_base_stat(5, 100);
   set_alignment(-750);
   set_knight_prestige(750);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_AWARENESS,60);
   set_act_time(6);
   add_act("say Me Nomog, king of goblins!");
   add_act("say Me smash caravans, me capture puny humans!");
   add_act("cackle dem");
   add_act("emote sneers derisively at you.");
   add_act("say I best killer here!");
   add_act("say Me kill humans with bare hands!");
   add_act("laugh dem");
   set_cact_time(6);
   add_cact("snarl all");
   add_cact("growl dem all");
   add_cact("spit all");
   add_cact("kick all");
   add_cact("emote grabs you and hurls you against the wall!");
   add_speak("Me capture dumb humans easy. Me put them in dark! Humans no like dark.\n");
   set_default_answer("The goblin king just laughs amusedly.\n");
   add_ask(({"humans","human"}),"The goblin king says: Me capture stoopid "+
      "humans and throw them in hole!\n");
   set_title("the King of the Red Hand Goblin Tribe");
   add_prop(LIVE_I_SEE_DARK,10);
   trig_new("%w 'arrives.' %s", "react_arrive");
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'falls' 'down' %s", "react_laugh");
   trig_new("%w 'attacks' 'Goblin.\n' %s","react_attack");
   set_alarm(1.0,0.0,"my_stuff");
}
void
my_stuff()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object("/d/Kalad/common/wild/pass/wep/gk_club");
   item -> move(TO);
   command("wield all");
   item = clone_object("/d/Kalad/common/wild/pass/arm/gk_armour");
   item -> move(TO);
   command("wear all");
   item = clone_object(CPASS(obj/q_treaty));
   item -> move(TO);
   item = clone_object(CPASS(obj/gob_bag));
   item -> move(TO);
   MONEY_MAKE_GC(random(10))->move(TO,1);
}
int
special_attack(object enemy)
{
   object me;
   mixed *hitresult;
   string how;
   me = this_object();
   if (random(6))
      return 0;
   hitresult = enemy->hit_me(300 + random(200), W_BLUDGEON, me, -1);
   how = " with no damage";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 10)
      how = " with slight injuries";
   if(hitresult[0] > 20)
      how = " with major injuries";
   if(hitresult[0] > 30)
      how = " with a great many wounds";
   if(hitresult[0] > 40)
      how = " with a thunderous strike";
   me->catch_msg("You attack your opponent in a berserker rage!\n"+
      capitalize(enemy->query_pronoun()) + " is berserked" + how + ".\n");
   enemy->catch_msg(QCTNAME(me) + " attacks you in a berserker rage!\n"+
      "You are berserked" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attacks " + QTNAME(enemy) + " in a berserker rage!\n"+
      capitalize(enemy->query_pronoun()) + " is berserked" + how + ".\n",enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
int
react_arrive(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who) {
   object obj;
   int ran;
   if (obj = present(who, environment())) {
      command("snarl " + (obj->query_real_name()));
      command("say Me crush you and feed you to stomach!");
      command("emote looks like he is thinking hard about how stupid the " + (obj->query_race_name()) + " is.");
   }
}
int
react_smile(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_smile",who);
      return 1;
   }
}
void
return_smile(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("tackle " + (obj->query_real_name()));
      command("say Quit yer damn smiling!");
   }
}
int
react_laugh(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_laugh",who);
      return 1;
   }
}
void
return_laugh(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("growl " + (obj->query_real_name()));
      command("kick " + (obj->query_real_name()));
      command("say You no laugh!");
   }
}

void
return_ask(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("hmm");
      command("ponder");
      command("say Ugh, ok, me think it time to not crush humanz.");
      command("emote starts scrawling something on a parchment.");
      command("give parchment to " + (obj->query_real_name()));
      command("say Dare ya go, me sine treety.");
      command("emote departs from the cave.");
      if(gobking = present("nomog",environment(TP)));
      {
         gobking -> remove_object();
      }
   }
}

/* Routine catch_question() introduced by Mercade to get rid of the obsolete
 * trig_new on questions. */
void
catch_question(string str)
{
    if (parse_command(lower_case(str), ({ }), "[about] [the] 'peace' / 'treaty' [treaty]"))
    {
        set_alarm(3.0, 0.0, &return_ask(this_player()->query_real_name()));
    }
}

int
react_attack(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("grin " + (obj->query_real_name()));
      command("put parchment in bag");
   }
}
void
attacked_by(object ob)
{
   ::attacked_by(ob);
   command("put parchment in bag");
   command("grin");
}