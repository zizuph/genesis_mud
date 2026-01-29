/* Master include file for making money on any npc. 5 April 1994 Mayhem */

/* How to use this crazy(?) system:
    First determine if you are including /d/Shire/common/defs.h.
    If you aren't, then you have to type a little more.
    If you are, within create_monster/creature/etc enter the following:
    MAKE_MONEY;
    I always put it near the end of the function, but it isn't necessary.
    If you aren't, enter the following in the same general location:
    set_alarm(1.0,0.0,"get_money");
    Note: the 1.0 can be whatever you want I suppose, but don't make it
    repeating or your guy will have WAY too much money.

    In addition, I have made available the following functions:
    make_platinum(num);
    make_gold(num);
    make_silver(num);
    make_copper(num);
       
    All those are optional, and should only be used on exceptional npcs
    to 'pad the kitty'  (Ie, make them a little richer than normal)
    Of course, you could also use them on very poor npcs, just by giving
    them a few coppers and not calling the main, "get_money", function.

    The 'automatic' addition of money uses the stat average of your npc
    and some formulas I concocted. The formulas are subject to change
    as the environment of the mud changes (just a warning), else it
    should be fairly stable and dependable.
    There is a random bit added in, so things won't get boring and 
    familiar.
    Any questions? Mail me, I love mail.
   Mayhem, 12 April 1994
 */

#include <money.h>

int amount_of_coin, amount_of_coin2;
string type_of_coin, type_of_coin2;
       

mixed set_npc_val()
{
  int npc_avg, ran_num;
  npc_avg = this_object()->query_average_stat();
  ran_num = random(9,time());

  if(npc_avg<50)
  {
    amount_of_coin=npc_avg/2 + ran_num;
    type_of_coin="copper";
    amount_of_coin2=npc_avg/2;
    type_of_coin2="copper";
  }

  if(npc_avg>49 && npc_avg<100)
  {
    amount_of_coin=npc_avg/2 + ran_num;
    type_of_coin="copper";
    amount_of_coin2=npc_avg/10 + ran_num/3;
    type_of_coin2="silver";
  }

  if(npc_avg>99 && npc_avg<150)
  {
    amount_of_coin=npc_avg/5 + ran_num;
    type_of_coin="silver";
    if(random(10)<1)
    {
      amount_of_coin2=(npc_avg+100)/((1+ran_num)*10);
      type_of_coin2="gold";
    }
    else
    {
      amount_of_coin2=npc_avg/10 + ran_num/2;
      type_of_coin2="silver";
    }
  }

  if(npc_avg>149)
  {
    if(random(10)<2)
    {
      amount_of_coin=npc_avg/110;
      type_of_coin="platinum";
      amount_of_coin2=npc_avg/20;
      type_of_coin2="gold";
    }
    else
    {
      amount_of_coin=npc_avg/12;
      type_of_coin="gold";
      amount_of_coin2=npc_avg/15 + 2*ran_num;
      type_of_coin2="silver";
    }
  }
}


get_money()
{
    set_npc_val();
    make_money(amount_of_coin, type_of_coin);
    make_money(amount_of_coin2, type_of_coin2);
}


make_money(i,type)
{
  object money;

  seteuid(getuid(this_object()));
  
  money=clone_object("/std/coins");
  money->set_heap_size(i);
  money->set_coin_type(type);
  money->move(this_object(),1);
}


mixed make_gold(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "gold");
}

mixed make_silver(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "silver");
}

mixed make_copper(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "copper");
}
  
mixed make_platinum(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "platinum");
}
