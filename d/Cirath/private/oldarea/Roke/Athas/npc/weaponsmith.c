/* The weaponsmith of Gont */
/* Coded by Glindor for use in Roke ONLY !!! */
/* Dont steal this one... */

inherit "/std/monster";
inherit "/lib/trade";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Roke/common/defs.h"

int busy=0;
object customer;
object weapon;
int newrepcorr,newrepdull,price;
int can_repair_corr,can_repair_dull;
int has_introduced=0;
int money_gotten=0;

create_monster()
{
  if (!IS_CLONE)
    return;
	set_short("strong dwarven weaponsmith");
  set_name("tentavva");
  add_name("smith");
  add_name("weaponsmith");
  set_race_name("dwarf");
  set_living_name("tentavva");
  set_title("the weaponsmith of Tyr");
  set_adj("strong");
  set_long("This is the weaponsmith of Tyr.\n"+
	BSS("He looks humongous for an dwarf, strong and healthy, just as "+
		"a smith should be.\n"));

  set_alignment(500);

  default_config_npc(55);
  set_base_stat(SS_CON,60);
  set_base_stat(SS_STR,80);
  set_hp(10000);
  set_skill(SS_WEP_AXE,80);

  trig_new("%w 'introduces' %s","react_introduce");

  config_default_trade();
  set_money_give_max(1000000);
  set_money_give_out(({1000000,100000,10000,1000}));
  set_money_give_reduce(({0,0,0,0}));

/* call_out("arm_me",1); */
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
}
query_knight_prestige(){return -3;}
/*
arm_me()
{
  object wep;
  seteuid(getuid(this_object()));
   /* wep = clone_object(A_OBJ_D+"smithsaxe"); */
/* wep->move(this_object()); */
/* command("wield hammer"); */
/* } */

void
react_introduce(string person,string who)
{
    if (!has_introduced)
      {
        call_out("introduce_me",4);
        has_introduced=1;
        call_out("remove_int",15);
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

init_living()
{
  ::init_living();

  add_action("regret","regret");
  add_action("repair_it","pay");
}

enter_inv(obj,from)
{
  ::enter_inv(obj,from);
  if (!from) return;
  if (obj->query_name()=="coin")
    {
      call_out("got_money",2,({obj,from}));
      return;
    }

  if (obj->check_weapon())
    {
      if (busy)
	{
	  call_out("give_back_busy",4,({obj,from}));
	  return;
	}
      busy=1;
      weapon=obj;
      customer=from;
      call_out("got_it",2);
      return;
    }
  call_out("give_back_noweapon",4,({obj,from}));
}

got_it()
{
	command("say Well, I'll see what I can do, it is not so "+
		"good as MY axe you know.");
	command("emote polishes his heavy axe.");
  tell_room(E(TO),QCTNAME(TO)+" studies the "+weapon->query_name()+".\n");
  call_out("fix_weapon",4);
}

got_money(object *things)
{
  int value;

  if (!busy || busy==1 || busy==3 || things[1]!=customer)
    {
      command("say Thank you, "+things[1]->short(TO)+"!");
      things[0]->remove_object();
      return;
    }
  value=things[0]->heap_value();
  money_gotten+=value;
  things[0]->remove_object();
  if (money_gotten>=price*12)
    {
      repair_it();
      return;
    }
  command("say Thank you, but the repair will cost more than that.");
  return;
}  

someone_left(who, where)
{
  if (!busy || who!=customer) return;

  if (busy==1) 
    {
      remove_call_out("fix_weapon");
    }

  command("shout Hey, you forgot your "+weapon->query_name()+".");
  command("shrug");
  call_out("drop_it",2);
}

give_back_busy(object *things)
{
  command("say I'm busy right now, "+things[1]->short(TO)+".");
  command("give "+things[0]->query_name()+" to "+things[1]->query_real_name());
  if (present(things[0],TO))
    {
      command("shrug");
      command("drop "+things[0]->query_name());
    }
  return 1;
}

give_back_noweapon(object *things)
{
  command("say I only deal with weapons "+things[1]->short(TO)+".");
  command("give "+things[0]->query_name()+" to "+things[1]->query_real_name());
  if (present(things[0],TO))
    {
      command("shrug");
      command("drop "+things[0]->query_name());
    }
  return 1;
}

give_back(object *things)
{
  command("say Here is your "+things[0]->query_name()+".");
  command("give "+things[0]->query_name()+" to "+things[1]->query_real_name());
  if (present(things[0],TO))
    {
      command("shrug");
      command("drop "+things[0]->query_name());
    }
  busy=0;
  return 1;
}

drop_it()
{
  if (!busy) return;
  command("drop "+weapon->query_name());
  busy=0;
}

regret()
{
  if (!busy || this_player()!=customer) 
    {
      command("say You haven't given me anything.");
      return 1;
    }
  if (busy==3)
    {
      command("say You have already made your decision.");
      return 1;
    }
  if (busy==1)
    {
      remove_call_out("fix_weapon");
    }
  command("say Ok, then.");
  command("shrug");

  busy=3;
  call_out("give_back",4,({weapon,customer}));
  return 1;
}

fix_weapon()
{
  int olddull,oldrepdull,oldcorr,oldrepcorr;
  int oldvalue1,oldvalue2,valuediff;

  if (weapon->query_prop(OBJ_I_BROKEN))
    {
      command("say This "+weapon->query_name()+" is broken.");
    }

  olddull = weapon->query_dull();
  oldrepdull = weapon->query_repair_dull();
  oldcorr = weapon->query_corroded();
  oldrepcorr= weapon->query_repair_corr();

  if (olddull-oldrepdull==0 && oldcorr-oldrepcorr==0)
    {
      command("say This "+weapon->query_name()+" is fine.");
      if (oldrepdull || oldrepcorr)
	command("say But it has been repaired before.");
      command("say I don't need to do anything with it.");
      call_out("give_back",4,({weapon,customer}));
      return 1;
    }

  newrepdull=olddull;
  while (!F_LEGAL_WEAPON_REPAIR_DULL(newrepdull,olddull)) newrepdull--;
  newrepcorr=oldcorr;
  while (!F_LEGAL_WEAPON_REPAIR_CORR(newrepcorr,oldcorr)) newrepcorr--;

  /* 0=can't repair; 1=can repair a little;
     2=can repair fully; 3=don't need to repair */
  if (olddull==oldrepdull) 
    {
      can_repair_dull=3;
    }
  else if (newrepdull == oldrepdull)
    {
      can_repair_dull=0;
    }
  else if (newrepdull == olddull)
    {
      can_repair_dull=2;
    }
  else 
    {
      can_repair_dull=1;
    }

  if (oldcorr==oldrepcorr) 
    {
      can_repair_corr=3;
    }
  else if (newrepcorr == oldrepcorr)
    {
      can_repair_corr=0;
    }
  else if (newrepcorr == oldcorr)
    {
      can_repair_corr=2;
    }
  else 
    {
      can_repair_corr=1;
    }

  switch (can_repair_dull*4+can_repair_corr)
    {
    case 0:
    case 3:
    case 12:
    case 15: /* this shouldnt happen */
      command("say Sorry, there is nothing i can do with this "+
	      weapon->query_name()+".");
      call_out("give_back",4,({weapon,customer}));
      return 1;
      break;
    case 1:
      command("say I can polish this "+weapon->query_name()+" a little.");
      command("say But I can't repair it.");
      break;
    case 2:
      command("say I can give this back its original shine.");
      command("say But I can't repair it.");
      break;
    case 4: 
      command("say I can repair this "+weapon->query_name()+" a little.");
      command("say But the rust is too deep to remove.");
      break;
    case 5:
      command("say I can repair and polish this "+weapon->query_name()+
	      " a little.");
      break;
    case 6:
      command("say I can give this back its original shine.");
      command("say But I can only repair it a little.");
      break;
    case 7:
      command("say I can repair this "+weapon->query_name()+" a little.");
      break;
    case 8:
      command("say I can repair this "+weapon->query_name()+" fully.");
      command("say But the rust is too deep to remove.");
      break;
    case 9:
      command("say I can repair this "+weapon->query_name()+" fully.");
      command("say But I cant't get all the rust off.");
      break;
    case 10:
    case 11:
      command("say I can make this "+weapon->query_name()+" as new.");
      break;
    case 13:
      command("say I can polish this "+weapon->query_name()+" a little.");
      break;
    case 14:
      command("say I can give this back its original shine.");
      break;
    default:
      command("say Hmm. Something is wrong. Please bug report this.");
      break;
    }

   oldvalue1=oldvalue2=weapon->query_value();

 if (weapon->query_prop(OBJ_I_BROKEN))
    {
      weapon->remove_prop(OBJ_I_BROKEN);
      oldvalue1=weapon->query_value();
      weapon->add_prop(OBJ_I_BROKEN,1);
    }

  valuediff=oldvalue1*
    F_WEAPON_VALUE_REDUCE(olddull-newrepdull,oldcorr-newrepcorr)/
      F_WEAPON_VALUE_REDUCE(olddull-oldrepdull,oldcorr-oldrepcorr)-oldvalue2;

  if (valuediff<=0) valuediff=8;

  price=valuediff/8; /* *1.5/12 , price is in silver */
  if (price<1) price=1;

  command("say I'll take "+price+" silver to fix that.");
  money_gotten=0;
  busy=2;
  return 1;
}

repair_it()
{
  int topay;
  int getback;

  if (!busy || this_player()!=customer)
    {
      command("say You have not given me anything to repair.");
      return 1;
    }

  if (busy==1)
    {
      command("say Let me look at it first.");
      return 1;
    }

  if (busy==3)
    {
      command("say You have already made your decision.");
      return 1;
    }

  getback=0;
  topay=12*price-money_gotten;

  if (topay<0)
    {
      getback=-topay;
      topay=0;
    }

  if (!pay(topay,customer,0,1,0,0,0))
    {
      command("say You can't afford that, "+customer->short(TO)+".");
      return 1;
    }

  if (can_repair_dull==1 || can_repair_dull==2)
    if (!weapon->set_repair_dull(newrepdull))
      {
	command("say Hmm, something is wrong, please bug report this.");
	return 1;
      }
  if (can_repair_corr==1 || can_repair_corr==2)
    if (!weapon->set_repair_corr(newrepcorr))
      {
	command("say Hmm, something is wrong, please bug report this.");
	return 1;
      }
  weapon->remove_prop(OBJ_I_BROKEN);

  if (topay) 
    {
      customer->catch_msg("You pay for the repair.\n");
      tell_room(E(TO),QCTNAME(customer)+" pays the weaponsmith.\n",customer);
      pay(topay,customer,0,0,0,0,0);
    }

  command("say Thank you, i'll fix it at once.");

  if (getback)
    {
      customer->catch_msg("You get some money back.\n");
      give(getback,customer,0,0,0,0,0);
    }

  busy=3;
  call_out("do_repair",4);
  
  return 1;
}

do_repair()
{
  tell_room(E(TO),QCTNAME(TO)+" does some work on the "+weapon->query_name()+
	    ".\n");
  call_out("give_back",4,({weapon,customer}));
}

