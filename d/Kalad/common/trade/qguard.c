inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

/* by Antharanos */
void
create_monster()
{
   ::create_monster();
   set_name("bobby");
   add_name("guard");
   set_race_name("human");
   set_adj("tower");
   set_short("tower guard");
   set_long("A tall, dark-haired man who is responsible for "+
      "maintaining vigilant guard within this tower in the Trade "+
      "district of Kabal.\n");
   set_stats(({80,70,70,55,55,60}));
   set_alignment(250);
   set_skill(SS_WEP_SWORD, 80);
   set_skill(SS_WEP_KNIFE, 60);
   set_skill(SS_2H_COMBAT, 70);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_PARRY, 75);
   set_skill(SS_AWARENESS,30);
   set_act_time(6);
   add_act("peer all");
   add_act("say Beware.");
   set_cact_time(3);
   add_cact("shout Fellow guardsmen, come to my aid!");
   add_cact("say You will die for this cowardly attack, you miserable cur.");
   add_speak("I took a locket from a thief once.\n");
   set_knight_prestige(-3);
   set_default_answer("The tower guard says: What?\n");
   add_ask(({"captain"}),"The tower guard says: Why, that'd be Mordur.\n");
   set_title("the Tower Guard");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_alarm(1.0,0.0,"arm_me");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv();
    if(from)
    {
        if(ob->short() == "a platinum coin")
        {
            set_alarm(3.0,0.0,"return_give",from);
        }
    }
}

void
arm_me()
{
   object wep, arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/caravan/arm/gchain");
   arm -> move(this_object());
   arm = clone_object("/d/Kalad/common/caravan/arm/ghelm");
   arm -> move(this_object());
   arm = clone_object("/d/Kalad/common/trade/cliffside/obj/locket");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/caravan/wep/gsword");
   wep -> move(this_object());
   wep = clone_object("/d/Kalad/common/caravan/wep/gdagger");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_GC(random(5))->move(TO,1);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
   {
      command("say Villanous retch! Die!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}

void
check_locket()
{
    object arm;
    seteuid(getuid(this_object()));

    if (!present("_guard_quest_locket"))
    {
        arm = clone_object("/d/Kalad/common/trade/cliffside/obj/locket");
        arm -> move(TO);
        command("wear all");
    }
}

void
return_give(object obj)
{
   if(present(obj, environment()))
   {
      command("say Here you go!");
      command("give locket to " + (obj->query_real_name()));
   }
}