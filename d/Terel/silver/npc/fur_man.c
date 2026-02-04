/*
  Guy that improve armours with fur.
    by Udana, 03/06
*/

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../include/defs.h"

#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif

/* for the pay function */
inherit "/lib/trade.c";
inherit NPC + "caravan_member.c";

int reinforce_item(string a);
void first_phase(object ob, object owner);
void second_phase(object ob, object owner);
void arm_me();

void create_caravan_member()
{
  set_name("orhton");
  add_name("tanner");
  set_race_name("dwarf");
  set_adj("young");
  add_adj("black-bearded");
  set_long("This dwarf is tanner. He travels with the caravan so he can buy animal skins in the north "+
    "and sells them in Calathin or on the road. He's told to be excellent at improving clothes and armour "+
    "they give better protection against cold weather. Just use 'reinforce <armour>'. \n");
    
  set_gender(0);
  set_alignment(100 + random(100));
  
  default_config_npc(80 + random(20));


  set_skill(SS_UNARM_COMBAT, 80);
  set_skill(SS_PARRY, 60);
  set_skill(SS_DEFENCE, 75);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_BLIND_COMBAT, 70);
  
  set_hp(query_max_hp());
  type = 3;
  remove_prop(LIVE_I_NEVERKNOWN);
  set_colour("_orhton_colour_");
  arm_me();
  config_default_trade();
  add_ask(({"fur", "furs", "fur-lined armours", "improving", "frost", "cold"}), "For a small fee I can reinforce your armours "+
    "fur so they can protect you better from frost here.\n");
  enable_intro();
  set_act_time(10 + random(10));
  add_act("shout Ye don't have to freeze yer buttom here, reinforce yer armours today!");
  add_act("shout Best furs for lowest prices!");
  
}

void arm_me()
{
  FIX_EUID;
  object to_wear;
  to_wear = clone_object(ARMOUR + "cloak");
  to_wear->set_colour("black");
  to_wear->move(TO);
  
  to_wear = clone_object(ARMOUR + "helmet");
  to_wear->set_colour("black");
  to_wear->move(TO);

  clone_object(ARMOUR + "vest")->move(TO);

  clone_object(OBJ + "deerskin")->move(TO);
  clone_object(OBJ + "foxskin")->move(TO);

  command("wear all");
}

public void help_friend(object enemy, object victim)
{
  /* He only changes target for his own wagonmates, no point at attacking the same guy again. */
 if(query_attack())
    if(query_attack() == enemy || victim->query_colour() != colour ||
	    (query_attack()->query_attack() && query_attack()->query_attack()->query_colour() == colour))
    {
	if(member_array(enemy, query_enemy(-1)) == -1)
	{
		object tmp = query_attack();
		attack_object(enemy);
		attack_object(tmp);
	}
	return;
    }
  if(!present(enemy, E(TO)))
  {
    command("smirk");
    return;
  }
  /* Just assisting */
  remove_prop(LIVE_S_EXTRA_SHORT);
  attack_object(enemy);
  enemy->catch_msg(QCTNAME(TO) + " attacks you!\n");
  tell_room(E(TO), QCTNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
}

public void init_living()
{
  ::init_living();
  add_action("reinforce_item", "reinforce");
}

/* returns 1 if the object is NOT an armour covering one of the major body parts */
int not_major_armour(object ob)
{
  object parts = ob->query_at();
	if(!parts)
		return 1;
  if(A_BODY | parts == parts)
    return 0;
  if(A_HEAD | parts == parts)
    return 0;
  if(A_ARMS | parts == parts)
    return 0;
  if(A_LEGS | parts == parts)
    return 0;
  if(A_ROBE | parts == parts)
    return 0;
  if(A_FEET | parts == parts)
    return 0;
  if(A_NECK | parts == parts)
    return 0;
  return 1;
}

int reinforce_item(string a)
{
  object to_rein;
  notify_fail("");
  /* no argument */
  if(!strlen(a))
  {
    TO->command("say What item do ye want to have improved with fur?");
    return 0;
  }
  /* can't see player */
  if(!CAN_SEE(TO, TP))
  {
    TO->command("say I can't see ye there, what do ye want again?");
    return 0;
  }
  /* no item given */
  if(!parse_command(a, TP, "%o", to_rein))
  {
    TO->command("say What item do ye want to have improved with fur?");
    return 0;
  }
  /* item isn't an armour piece that covers a major body part */
  if(not_major_armour(to_rein))
  {
    TO->command("say I can't reinforce that!");
    return 0;
  }
  /* alredy reinforced */
  if(to_rein->query_prop(OBJ_COLD_WEATHER_PROTECT))
  {
    TO->command("say I can't make that any better I'm afraid.");
    return 0;
  }
  
  /* It was lined with something else. */
  if (stringp(to_rein->short()) &&
	wildmatch("*-lined*", to_rein->short()))
  {
	TO->command("say That has been already lined!\n");
	return 0;
  }
  
  
  mixed pay_res;
  pay_res = pay(1000, TP, "", 0, TO, "");
  /* can't pay */
  if(pay_res == -1)
  {
    notify_fail("You can't pay for it!\n");
    return 0;
  }
  /* changing item */
  write("You hand your " + to_rein->short() + " to " + query_the_name(TO) + ".\n");
  say(QCTNAME(TP) + " hands " + TP->query_possessive() + " " + to_rein->short() + " to " + QTNAME(TO)
    + ".\n");
  to_rein->move(TO);
  set_alarm(5.0, 0.0, &first_phase(to_rein, TP));
  say(QCTNAME(TO) + " begins his work.\n");
  return 1;
}

void first_phase(object ob, object owner)
{
  command("emote measures the " + ob->short() + " carefully, and begins to cut fur.");
  command("smile happ");
  set_alarm(5.0, 0.0, &second_phase(ob, owner));
}

void second_phase(object ob, object owner)
{
  string half1, half2;
  command("emote skillfully lines the " + ob->short() + " with fur pieces.");
  ob->add_prop(OBJ_COLD_WEATHER_PROTECT, 1);
  /* pair of boots or something */
  if(parse_command(ob->short(), ({}), "%s 'of' %s", half1, half2))
    ob->set_short(half1 + " of fur-lined " + half2);
  /* single item */
  else
    ob->set_short("fur-lined " + ob->short());
  ob->set_long(ob->query_long() + "It has been lined with warm fur.\n");
  ob->add_adj("fur-lined");
  command("give " + ob->query_name() + " to " + owner->query_real_name());
  if(present(ob))
    command("drop " + ob->query_name()); 
 
}
  
