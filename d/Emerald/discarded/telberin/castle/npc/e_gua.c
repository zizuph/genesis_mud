inherit "/std/monster";

#include "default.h"

#define LIVE_I_I_KILLED_ROYAL_PALADIN "_live_i_i_killed_royal_paladin"

void
create_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("guard");
   set_race_name("elf");
   set_short("elven guard");
   set_long(break_string("This guard is one of the many in the elven "+
         "palace guards, who are extremely well trained.\n",76));

   set_base_stat(SS_INT, 67);
   set_base_stat(SS_WIS, 56);
   set_base_stat(SS_DIS, 44);
   set_base_stat(SS_STR, 45);
   set_base_stat(SS_DEX, 61);
   set_base_stat(SS_CON, 37);
   
   set_skill(SS_WEP_SWORD, 43);
   set_skill(SS_PARRY, 39);
   set_skill(SS_DEFENCE, 38);
   
   set_all_hitloc_unarmed(3);
   
   set_hp(569);
   
   add_prop(OBJ_I_WEIGHT, 19000);
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   
   set_alignment(250);
   
   
    set_alarm(1.4,0.0, "arm_me");
}

void
arm_me()
{
   object eq;
   
    reset_euid();
   eq=clone_object(CASTLE_DIR + "wep/g_sword");
   if (eq)
      eq->move(this_object());
   eq=clone_object(CASTLE_DIR + "arm/g_brig");
   if (eq)
      eq->move(this_object());
   eq=clone_object(CASTLE_DIR + "arm/g_helmet");
   if (eq)
      eq->move(this_object());

    set_alarm(1.0,0.0,"wield_it");
}

void
attacked_by(object ob)
{
   object *arr;
   int i;
   
   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
* Function name: notify_ob_attacked_me
   * Description:   This is called when someone attacks a team member of mine
* Arguments:     friend - My team mate
*                attacker - The attacker
*/
void
notify_ob_attacked_me(object friend, object attacker)
   {
   if (query_attack())
      return;
   
   if (random(10))
      call_out("help_friend", 1, attacker);
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say You scum, stop fighting my friend!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}

void
do_die(object enemy)
{
   if(query_hp() > 0) { return; }
   /* and not if(query_hp()) for query_hp() might be negative */
      
   if(!enemy) { enemy = previous_object(); }
   
   enemy->add_prop(LIVE_I_I_KILLED_ROYAL_PALADIN, 1);
   ::do_die(enemy);
   
   return;
}

void
wield_it()
{
    tell_room(environment(this_object()),
              capitalize(short())+" checks his equipment to make sure everything "+
              "is in order.\n");
    command("wield all");
    command("wear all");
}
