/*
 * weaponsmith.c
 *
 * Used in nyreese/cadu_smith.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* The weaponsmith of Gont */
/* Coded by Glindor for use in Re-Albi */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>

int busy = 0;
object customer;
object weapon;
int newrepcorr, newrepdull, price;
int can_repair_corr, can_repair_dull;
int has_introduced = 0;
int money_gotten = 0;
int fw_id;

void got_money(object obj, object from);
void give_back(object obj, object from);
void give_back_busy(object obj, object from);
void give_back_noweapon(object obj, object from);
void got_it();
void fix_weapon();
void drop_it();
void do_repair();
int repair_it();

void
create_monster()
{
    set_name("gilahin");
    add_name("smith");
    add_name("weaponsmith");
    set_race_name("dwarf");
    set_living_name("gilahin");
    set_title("the weaponsmith");
    set_adj("strong");
    set_long("This is the weaponsmith of Cadu.\n" +
             "He looks quite torn after many years of hard work in the " +
             "blacksmith, and he's a man that commands respect.\n");
    
    set_alignment(500);

    default_config_npc(55);
    set_base_stat(SS_CON, 60);
    set_base_stat(SS_STR, 80);
    set_skill(SS_WEP_CLUB, 80);

    config_default_trade();
    set_money_give_max(1000000);
    set_money_give_out(({1000000,100000,10000,1000}));
    set_money_give_reduce(({0,0,0,0}));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int query_knight_prestige(){return -3;}

void
equip_me()
{
    object wep;
    seteuid(getuid(this_object()));
    wep = clone_object(ROKEDIR + "wep/hammer");
    wep->move(this_object());
    command("wield hammer");
}

void
remove_int()
{
    has_introduced = 0;
}

void
add_introduced(string person)
{
    if (!has_introduced)
    {
        set_alarm(4.0, 0.0, &command("introduce myself"));
        has_introduced = 1;
        set_alarm(15.0, 0.0, remove_int);
    }
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!from) return;
    if (obj->query_name() == "coin")
    {
        set_alarm(4.0, 0.0, &got_money(obj, from));
        return;
    }

    if (obj->check_weapon())
    {
        if (busy)
        {
            set_alarm(4.0, 0.0, &give_back_busy(obj, from));
            return;
        }
        busy = 1;
        weapon = obj;
        customer = from;
        fw_id = set_alarm(2.0, 0.0, got_it);
        return;
    }
    set_alarm(4.0, 0.0, &give_back_noweapon(obj,from));
}

void
got_it()
{
    command("say Thank you, I'll see what I can do.");
    tell_room(E(TO), QCTNAME(TO) + " studies the " + weapon->query_name() +
              ".\n");
    fw_id = set_alarm(4.0, 0.0, fix_weapon);
}

void
got_money(object obj, object from)
{
  int value;

  if (!busy || busy == 1 || busy == 3 || from != customer)
  {
      command("say Thank you, " + from->short(TO) + "!");
      obj->remove_object();
      return;
  }
  value = obj->heap_value();
  money_gotten += value;
  obj->remove_object();
  if (money_gotten >= price*12)
  {
      repair_it();
      return;
  }
  command("say Thank you, but the repair will cost more than that.");
  return;
}  

void
someone_left(object who, object where)
{
    if (!busy || who != customer) return;
    
    if (busy == 1 || busy == 3)
    {
        remove_alarm(fw_id);
    }

    command("shout Hey, you forgot your " + weapon->query_name() + ".");
    command("shrug");
    set_alarm(2.0, 0.0, drop_it);
}

void
give_back_busy(object obj, object from)
{
    command("say I'm busy right now, " + from->short(TO) + ".");
    command("give " + OB_NAME(obj) + " to " + from->query_real_name());
    if (present(obj, TO))
    {
        command("shrug");
        command("drop " + OB_NAME(obj));
    }
}

void
give_back_noweapon(object obj, object from)
{
    command("say I only deal with weapons " + from->short(TO) + ".");
    command("give " + OB_NAME(obj) + " to " + from->query_real_name());
    if (present(obj, TO))
    {
        command("shrug");
        command("drop " + OB_NAME(obj));
    }
}

void
give_back(object obj, object from)
{
    command("say Here is your " + obj->query_name() + ".");
    command("give " + OB_NAME(obj) + " to " + from->query_real_name());
    if (present(obj, TO))
    {
        command("shrug");
        command("drop " + OB_NAME(obj));
    }
    busy = 0;
}

void
drop_it()
{
    if (!busy) return;
    command("drop " + OB_NAME(weapon));
    busy = 0;
}

int
regret()
{
    if (!busy || this_player() != customer) 
    {
        command("say You haven't given me anything.");
        return 1;
    }
    if (busy == 3)
    {
        command("say You have already made your decision.");
        return 1;
    }
    if (busy == 1)
    {
        remove_alarm(fw_id);
    }
    command("say Ok, then.");
    command("shrug");

    busy = 3;
    set_alarm(4.0, 0.0, &give_back(weapon, customer));
    return 1;
}

void
fix_weapon()
{
    int olddull, oldrepdull, oldcorr, oldrepcorr;
    int oldvalue1, oldvalue2, valuediff;

    if (weapon->query_prop(OBJ_I_BROKEN))
    {
        command("say Sorry, but this " + weapon->query_name() + 
                " is completely broken.");
        command("say There is nothing I can do about it.");
        fw_id = set_alarm(4.0, 0.0, &give_back(weapon, customer)); 
        return;
    }

    olddull = weapon->query_dull();
    oldrepdull = weapon->query_repair_dull();
    oldcorr = weapon->query_corroded();
    oldrepcorr = weapon->query_repair_corr();

    if (olddull - oldrepdull == 0 && oldcorr-oldrepcorr == 0)
    {
        command("say This " + weapon->query_name() + " is fine.");
        if (oldrepdull || oldrepcorr)
            command("say But it has been repaired before.");
        command("say I don't need to do anything with it.");
        fw_id = set_alarm(4.0, 0.0, &give_back(weapon, customer));
        return;
    }

    newrepdull = olddull;
    while (!F_LEGAL_WEAPON_REPAIR_DULL(newrepdull, olddull)) newrepdull--;
    newrepcorr = oldcorr;
    while (!F_LEGAL_WEAPON_REPAIR_CORR(newrepcorr, oldcorr)) newrepcorr--;

    /* 0=can't repair; 1=can repair a little;
       2=can repair fully; 3=don't need to repair */
    if (olddull==oldrepdull) 
    {
        can_repair_dull = 3;
    }
    else if (newrepdull == oldrepdull)
    {
        can_repair_dull = 0;
    }
    else if (newrepdull == olddull)
    {
        can_repair_dull = 2;
    }
    else 
    {
        can_repair_dull = 1;
    }

    if (oldcorr==oldrepcorr) 
    {
        can_repair_corr = 3;
    }
    else if (newrepcorr == oldrepcorr)
    {
        can_repair_corr = 0;
    }
    else if (newrepcorr == oldcorr)
    {
        can_repair_corr = 2;
    }
    else 
    {
        can_repair_corr = 1;
    }

    switch (can_repair_dull*4 + can_repair_corr)
    {
    case 0:
    case 3:
    case 12:
        command("say Sorry, there is nothing i can do with this " +
                weapon->query_name() + ".");
        fw_id = set_alarm(4.0, 0.0, &give_back(weapon,customer));
        return;
        break;
    case 1:
        command("say I can polish this " + weapon->query_name() +
                " a little.");
        command("say But I can't repair it.");
        break;
    case 2:
        command("say I can give this back its original shine.");
        command("say But I can't repair it.");
        break;
    case 4: 
        command("say I can repair this " + weapon->query_name() +
                " a little.");
        command("say But the rust is too deep to remove.");
        break;
    case 5:
        command("say I can repair and polish this " + weapon->query_name() +
                " a little.");
        break;
    case 6:
        command("say I can give this back its original shine.");
        command("say But I can only repair it a little.");
        break;
    case 7:
        command("say I can repair this " + weapon->query_name() +
                " a little.");
        break;
    case 8:
        command("say I can repair this " + weapon->query_name() + " fully.");
        command("say But the rust is too deep to remove.");
        break;
    case 9:
        command("say I can repair this " + weapon->query_name() + " fully.");
        command("say But I can't get all the rust off.");
        break;
    case 10:
    case 11:
    case 15:  /* if its only broken */
        command("say I can make this " + weapon->query_name() + " as new.");
        break;
    case 13:
        command("say I can polish this " + weapon->query_name() +
                " a little.");
        break;
    case 14:
        command("say I can give this back its original shine.");
        break;
    default:
        command("say Hmm. Something is wrong. Please bug report this.");
        break;
    }

    oldvalue1 = oldvalue2 = weapon->query_value();

/* if (weapon->query_prop(OBJ_I_BROKEN))
    {
      weapon->remove_prop(OBJ_I_BROKEN);
      oldvalue1=weapon->query_value();
      weapon->add_prop(OBJ_I_BROKEN,1);
    }
*/
    valuediff = oldvalue1 *
        F_WEAPON_VALUE_REDUCE(olddull - newrepdull, oldcorr - newrepcorr)/
        F_WEAPON_VALUE_REDUCE(olddull - oldrepdull, oldcorr - oldrepcorr) -
        oldvalue2;

    if (valuediff <= 0) valuediff = 8;

    price = valuediff / 8; /* *1.5/12 , price is in silver */
    if (price < 1) price = 1;

    command("say I'll take " + price + " silver to fix that.");
    money_gotten = 0;
    busy = 2;
}

int
repair_it()
{
    int topay;
    int getback;

    if (!busy || this_player() != customer)
    {
        command("say You have not given me anything to repair.");
        return 1;
    }

    if (busy == 1)
    {
        command("say Let me look at it first.");
        return 1;
    }

    if (busy == 3)
    {
        command("say You have already made your decision.");
        return 1;
    }

    getback = 0;
    topay = 12 * price - money_gotten;

    if (topay < 0)
    {
        getback = -topay;
        topay = 0;
    }

    if (!pay(topay, customer, 0, 1, 0, 0, 0))
    {
        command("say You can't afford that, " + customer->short(TO) + ".");
        return 1;
    }

    if (can_repair_dull == 1 || can_repair_dull == 2)
        if (!weapon->set_repair_dull(newrepdull))
        {
            command("say Hmm, something is wrong, please bug report this.");
            return 1;
        }
    if (can_repair_corr == 1 || can_repair_corr == 2)
        if (!weapon->set_repair_corr(newrepcorr))
        {
            command("say Hmm, something is wrong, please bug report this.");
            return 1;
        }
    //  weapon->remove_prop(OBJ_I_BROKEN);

    if (topay) 
    {
        customer->catch_msg("You pay for the repair.\n");
        tell_room(E(TO), QCTNAME(customer) + " pays the weaponsmith.\n",
                  customer);
        pay(topay, customer, 0, 0, 0, 0, 0);
    }

    command("say Thank you, I'll fix it at once.");

    if (getback)
    {
        customer->catch_msg("You get some money back.\n");
        give(getback, customer, 0, 0, 0, 0);
    }

    busy = 3;
    fw_id = set_alarm(4.0, 0.0, do_repair);
  
    return 1;
}

void
do_repair()
{
    tell_room(E(TO), QCTNAME(TO) + " does some work on the " +
              weapon->query_name() + ".\n");
    fw_id = set_alarm(4.0, 0.0, &give_back(weapon,customer));
}

void
init_living()
{
    ::init_living();

    add_action(regret, "regret");
    add_action(repair_it, "pay");
}
