
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#define ENEMY "_enemy_of_town_guards"

int armed;

void arm_me()
{
  string type,wep;

  if(armed) return;
  armed=1;

  reset_euid();
  wep=ONE_OF_LIST(({"axe","club","sword","pole"}));
  type=ONE_OF_LIST(({"_low","_med"}));
  clone_object(WEAPON_DIR+wep+type)->move(this_object());
  command("wield all");
  clone_object(RHUN_DIR+"npc/chainmail")->move(this_object());
  type=ONE_OF_LIST(({"_low","_med"}));
  clone_object(ARMOUR_DIR+"shield"+type)->move(TO);
  type=ONE_OF_LIST(({"_low","_med"}));
  clone_object(ARMOUR_DIR+"helm"+type)->move(TO);
  command("wear all");
}

string query_guard_id(){ return "_rhun_town_guard_";}

void create_monster()
{
  set_alarm(1.0, 0.0, "arm_me");

  set_name("guard");
  set_race_name("human");
  set_adj("town");
  set_short("town guard");
  set_gender(0);
  set_alignment(200);
  set_long("This small-town guard looks as though he'll fight"
	+" fiercely to protect his little community.\n");
  add_prop(CONT_I_WEIGHT, 75*1000);
  add_prop(CONT_I_VOLUME, 75*1000);
  add_prop(CONT_I_HEIGHT, 180);

  add_prop(LIVE_I_NEVERKNOWN, 1);

  set_stats(({50,40,44,50,45,45}));

  set_skill(SS_UNARM_COMBAT, 40);
  set_skill(SS_DEFENCE, 32);
  set_skill(SS_WEP_POLEARM,44);
  set_skill(SS_WEP_CLUB,44);
  set_skill(SS_WEP_AXE,44);
  set_skill(SS_WEP_SWORD,44);
  set_skill(SS_PARRY, 50);

  set_chat_time(12);
  add_chat("I've heard there are Easterling in the forest.");
  add_chat("Be sure not to cause any trouble in our little town.");

  set_aggressive(1);
}

/*************  agresive stuff  *********************************/
void init_attack()
{
  if(!TP->check_seen(TO)) return;
  if(TP->query_prop(ENEMY))
  {
    if(random(2)) command("shout Troublemaker! Kill "+HIM(TP)+"!!!");
    set_alarm(1.0, 0.0, "slow_init_attack", TP);
  }
}

void slow_init_attack(object tp)
{
  aggressive_attack(tp);
}

/*********  team stuff - they should help eachother  ****************/
void call_for_help(object ob)
{
  object *arr = FILTER_LIVE(all_inventory(environment()));
  int i;

  for (i = 0; i < sizeof(arr); i++)
    if((arr[i]->query_quard_id() == "_rhun_town_guard_") && (arr[i] != TO))
      arr[i]->notify_ob_attacked_me(ob);
}

void 
attacked_by(object ob)
{
  ::attacked_by(ob);
  ob->add_prop(ENEMY, 1);
  call_for_help(ob); /* naturally we call for help when attacked */
}

void
attack_object(object ob)
{
  ::attack_object(ob);
  ob->add_prop(ENEMY, 1);
  call_for_help(ob);  /* well, we call for help even when we attack! */
}

int
special_attack(object ob)
{
  if(!random(5)) call_for_help(ob); 
  /* sometimes we call for help even during fight */
  return 0;
}

void
notify_ob_attacked_me(object ob)
{
    if(query_attack()) return;
    set_alarm(itof(5 + random(10)), 0.0, "help_friend", ob);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        if(random(2)) command("grin at " + ob->query_real_name());
        command("kill " + ob->query_real_name());
    }
}
