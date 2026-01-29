inherit "/std/monster.c";
inherit "/d/Roke/common/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Roke/common/defs.h"

int has_introduced=0;
void
create_monster()
{
   set_name("alexander");
   add_name("marshal");
   add_adj("village");
   add_adj("marshal");
   set_title("Marshal of Cove's Elite Guard");
   set_race_name("human");
   set_long("This is the marshal of the small village "+
      "of cove. He is the captain of the village guard "+
      "and keeps things in general order. He also "+
      "coordinates the construction work done in "+
      "the village.\n");

   set_stats(({ 200, 250, 200, 75, 75, 120}));



   set_hp(10000);

   set_skill(SS_DEFENCE, 100);
   set_skill(SS_WEP_KNIFE, 100);
   set_skill(SS_2H_COMBAT, 85);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_PARRY, 100);
   set_skill(SS_WEP_SWORD, 90);
   set_alignment(700);
   add_act("emote flexes his muscles menacingly.");
   add_act("emote signs some important papers.");
   add_act("emote polishes his vicious midnight-back peace maker.");
   add_act("emote proudly brandishes his peace maker.");
   add_act("emote coughs noisily");
   add_act("emote caresses the blade of his sword.");
   add_act("emote snarls: Who let you in here?");
   add_act("growl");
   add_act("grumble");
   add_cchat("I shall see to it that you are hanged!");
   add_cchat("You shall regret your descision to attack me.");
   add_cchat("My peace maker shall make peace, after your death!");
   add_cchat("The peace maker will cut you to pieces!");
   add_cchat("I will cut you into so many pieces your own mother "+
             "won't recognize you!");
   add_chat("They say my fists are harder than stone.");
   add_chat("I can break five stone slabs with my bare hands!");
   add_chat("Criminals that visit here soon find that they are not wanted.");
   add_chat("Our village is small, but we, the law, keep things in order.");
   add_chat("And those criminals that do not leave find themselves "+
      "either dead or locked in jail.");
   add_chat("We have our own kind of justice here in Cove.");
   add_chat("Not only do I make laws, I enforce them.");
   add_chat("Green steel is some of the finest in the land.");
   add_chat("There is a story behind my peace maker.");
   add_chat("Legend is that there is another weapon simaler to "+
            "the peace maker.");
   add_chat("So vile was this weapon that the Gods hid it.");
   add_chat("I would reward greatly to whomever finds it.");

   set_act_time(3);
   set_chat_time(9);
   set_cact_time(1);


   ::create_monster();

    if (IS_CLONE)
      call_out("arm_me", 1);
    trig_new("%w 'introduces' %s","react_introduce");
    trig_new("%w 'smiles' %s", "react_smile");
    trig_new("%w 'bows' %s", "react_bow");
    

}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   clone_object("/d/Roke/vladimir/obj/armour/gplatemail")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/ghelm")->move(TO);
   clone_object("/d/Roke/vladimir/obj/weapons/msword")->move(TO);
   clone_object("/d/Roke/vladimir/obj/weapons/edagger")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/ggreaves")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/gbracers")->move(TO);
   command("wear all");
   command("wield all");
   seteuid(getuid(TO));

}
void
react_introduce(string person,string who)
{
   if (!has_introduced)
      {
      call_out("introduce_me",6);
      has_introduced=1;
      call_out("remove_int",30);
   }
}

void
introduce_me()
{
   command("introduce myself");
}

void
remove_int()
{
   has_introduced=0;
}
int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = this_object();
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(550 + random(680), W_BLUDGEON, me, -1);
   how = " but did no damage";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 5)
     how = " lightly";
   if (hitresult[0] > 10)
      how = " savagely";
   if (hitresult[0] > 15)
      how = " dangerously";
   if (hitresult[0] > 20)
      how = " wickedly";
   me -> catch_msg("You backhand your enemy!\n"+
      capitalize(enemy->query_pronoun())+" is backhanded"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " backhands you!\n"+
      "You are backhanded" + how + ".\n");
   tell_watcher(QCTNAME(me) + " backhands " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is backhanded"+
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}


int
react_bow(string who, string dummy) {
    if(who) {
        who = lower_case(who);
        call_out("return_bow", 3, who);
        return 1;
    }
}

void
return_bow(string who) {
   object obj;
   int ran;

   if(obj = present(who, environment())) {
        ran = random(3);
        if(ran == 0)
           command("say Hey dirtbag! Bow a little lower so I "+
                   "can lop your head off!!");
           command("laugh maniac");
        if(ran == 1)
           command("spit at " + who);
        if(ran == 2)
           command("say Bow before thine master, "+
                obj->query_nonmet_name() +".");
   }
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 3, who);
      return 1;
   }
}

void
return_smile(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You have a nice smile " + obj->query_nonmet_name()
               + ".");
      if (ran == 1)
         command("slap " + who);
      if (ran == 2)
         command("say Wipe that smile from your face, " +
         obj->query_nonmet_name() + ".");
   }
}
