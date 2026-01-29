/*
 * This file is /d/Gondor/olorin/npc/haradcap.c
 *
 * Last mod: Olorin,. August 1994
 *
 * Gnadnar, October 1998: call notify_ob_attacked_me(), not 
 *	order_attack_enemy(), in team. vary shouts.
 *	
 */
inherit "/d/Gondor/ithilien/npc/haradstd";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static int	Alarmid;

void
create_monster()
{
   set_adj("giant");
   ::create_monster();
   
   set_name("haradrim captain");
   add_name(({"captain", "southron", "haradrim", "man"}));
   set_pname("captains");
   add_pname("southrons");
   add_pname("men");
   add_pname("haradrim");
   set_short("brutal dark-skinned haradrim captain");
   set_pshort("brutal dark-skinned haradrim captains");
   set_long(BSN("This is a brutal dark-skinned giant of a haradrim warrior. "+
       "He is clad in a scarlet robe. His golden helmet marks him as "+
       "a captain in the army of Harad."));
   set_adj("brutal");
   add_adj("dark-skinned");
   add_adj("haradrim");
   default_config_npc(103+random(5));
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
   int     i, s;
   object *arr;
   
   enemy_mine = ob->query_enemy();
   if (enemy_mine)
   {
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

      command( ({
	  "shout I'm going to kill this " +
	      enemy_mine->query_nonmet_name() + "!",
	  "shout Die, you sniveling coward!",
          "shout Kill that " + enemy_mine->query_nonmet_name() + "!",
	  "shout You won't escape this time, spy!",
	  "shout You're in the wrong place, " +
	      enemy_mine->query_race_name() + "!",
	  })[random(5)]
      );

      arr = (object *)query_team_others();
      for (i = 0, s = sizeof(arr); i < s; i++)
      {
          arr[i]->notify_ob_attacked_me(enemy_mine);
      }
      environment()->stand_to_fight();
      if (!Alarmid ||
	  !sizeof(get_alarm(Alarmid)))
      {
          Alarmid = set_alarm(10.0, 0.0, &check_combat(ob));
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
check_player_met(object pl)
{
   object *arr;
   int     i, s;

   if (!objectp(pl))
      return;

   if (!IS_EVIL(pl) && !pl->query_npc() && CAN_SEE(TO, pl))
   {
      command("shout Kill this " + pl->query_race_name() + " at once!");
      command("kill "+pl->query_real_name());
      check_combat(TO);
      
      arr = (object *)query_team_others();
      for (i = 0, s = sizeof(arr); i < s; i++)
      {
          arr[i]->notify_ob_attacked_me(TO, pl);
      }
   }
}

public void
init_attack()
{
    set_alarm(1.0, 0.0, &check_player_met(TP));
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

