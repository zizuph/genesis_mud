/*
 * This file is /d/Gondor/olorin/npc/haradcap.c
 *
 * Last mod: Olorin,. August 1994
 */
inherit "/d/Gondor/ithilien/npc/haradstd";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int     cc_aid;
void
create_monster()
{
   set_adj("giant");
   ::create_monster();
   
   set_name("haradrim captain");
   add_name("captain");
   set_pname("captains");
   set_short("haradrim captain");
   set_pshort("haradrim captains");
   set_long(BSN("This is a dark-skinned giant of a haradrim warrior. He is clad in a " +
         "scarlet robe. His golden helmet marks him as a captain in the army of " +
         "Harad."));
   default_config_npc(73+random(5));
   set_base_stat(SS_DEX, 85+random(10));
   set_base_stat(SS_CON, 85+random(10));
   set_base_stat(SS_DIS, 95+random(5));
   set_aggressive(1);
   set_alignment(-350-random(250));
   set_skill(SS_WEP_SWORD, 80+random(10));
   set_skill(SS_PARRY,     90+random(5));
   set_skill(SS_DEFENCE,   90+random(5));
   set_skill(SS_AWARENESS, 70+random(5));
   
   add_prop(CONT_I_HEIGHT,   185+random(20));
   add_prop(CONT_I_WEIGHT, 90000+random(10000));
   add_prop(CONT_I_VOLUME, 85000+random(20000));
   
   add_cchat("Kill that spy!");
   add_cchat("Kill it and take his equipment!");
   add_act("shout To me! Everyone to me!");
   add_act("shout Hurry, you bastards! Keep running!");
   add_act("snarl");   
   add_cact("spit");   
}

void
arm_me()
{
   FIX_EUID
   
   clone_object(WEP_DIR + "capsword")->move(TO);
   command("wield sword");
   
   clone_object(ARM_DIR + "haradcloak")->move(TO);
   command("wear cloak");
   
   clone_object(ARM_DIR + "caphelm")->move(TO);
   command("wear helmet");
   
   clone_object(ARM_DIR + "haradshield")->move(TO);
   command("wear shield");
   
   clone_object(ARM_DIR + "corslet")->move(TO);
   command("wear corslet");

    get_money();
}

void
check_combat(object ob)
{
   object  enemy_mine;
   int     value_find_co;
   
   enemy_mine = ob->query_enemy();
   if (enemy_mine)
   {
      ob->command("shout I'm going to kill this " + enemy_mine->query_nonmet_name() + "!");
      if(!present(enemy_mine, ENV(ob)))
      {
         command("shout Let's go on to Morannon!");
         command("get all from corpse");
         environment()->continue_patrol(TO);
         return;
      }
      if(present(enemy_mine) && !living(enemy_mine))
      {
         command("shout The loot belongs to me alone!");
         command("get all from corpse");
         environment()->continue_patrol(TO);
         return;
      }
      command("shout Kill that wimp!");
      environment()->stand_to_fight();
      if (!cc_aid)
      {
         set_alarm(10.0, 0.0, &check_combat(ob));
      }
   }
   else
   {
      command("get all from corpse");
      command("get all");
      environment()->continue_patrol(TO);
   }
   return;
}

public void
init_attack()
{
   object *arr;
   int     i;

   if (!IS_EVIL(TP) && !TP->query_npc() && CAN_SEE(TO, TP))
   {
      command("shout Kill this " + TP->query_race_name() + " at once!");
      command("kill "+TP->query_real_name());
      check_combat(TO);
      
      arr = (object *)query_team_others();
      for (i = 0; i < sizeof(arr); i++)
          arr[i]->order_attack_enemy(TO, TP);
   }
}

void
order_attack_enemy(object friend, object enemy)
{
   if (query_enemy(-1))
      return;
   
   if (random(10))
      set_alarm(rnd()*5.0, 0.0, &help_friend(enemy));
}

int query_knight_prestige() { return 260; }

