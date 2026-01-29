inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(3);
   if(i < 1)
      return "/d/Kalad/common/caravan/wep/gmace";
   else if (i < 2)
      return "/d/Kalad/common/caravan/wep/gsword";
   else
      return "/d/Kalad/common/caravan/wep/gaxe";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("brigand");
   set_race_name("human");
   set_adj("filthy");
   add_adj("unkempt");
   set_short("brigand");
   set_pshort("brigands");
   set_long("He is a tall, dark-haired man whose job is to "+
      "rob and steal from anyone who dares come near him. "+
      "You notice that his weapons are of the brand the "+
      "city-guards of Kabal wields. Undoubtedly they were not given to him.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 70 + random(25));
   set_base_stat(3, 55);
   set_base_stat(4, 55);
   set_base_stat(5, 100);
   set_alignment(-333);
   set_skill(SS_WEP_CLUB, 70);
   set_skill(SS_WEP_SWORD, 80);
   set_skill(SS_WEP_AXE, 75);
   set_skill(SS_WEP_KNIFE, 60);
   set_skill(SS_2H_COMBAT, 75);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_PARRY, 75);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_HIDE,75);
   set_skill(SS_SNEAK,50);
   set_knight_prestige(200);
   add_prop(OBJ_I_HIDE, 75);
   set_default_answer("The brigand says: Shut up!\n");
}
void
arm_me()
{
   object wep, arm;
   int i;
   string extra;
   extra = random_extra();
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/caravan/arm/gchain");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/caravan/arm/ghelm");
   arm -> move(TO);
   command("wear all");
   wep = clone_object(extra);
   wep -> move(TO);
   wep = clone_object("/d/Kalad/common/caravan/wep/gdagger");
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(4))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("spit " + (ob->query_real_name()));
      command("kill " + lower_case(ob->query_real_name()));
   }
}

do_die(object enemy)
{
   if (TO->query_hp()>0) return;
   
   command("say This one is lethal!!!");
   command("scream");
   ::do_die(enemy);
}
