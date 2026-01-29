/************************************************************************/
/*                                                                      */
/* Money making master object for the Shire.                            */
/* This object is based on the make_money.h file originally written by  */
/* Mayhem on April 5, 1994.                                             */
/*                                                                      */
/* Updated by Duragus on Sept, 1998.                                    */
/************************************************************************/

/*
 * This object allows an npc to have money based on the average stats
 * of the npc and a little bit of randomness.  It conforms to the new
 * money system of Genesis, that is, to use the OBJ_M_HAS_MONEY prop to
 * allow the removal of all /std/heap objects that npcs used to carry,
 * wasting memory.
 *
 * Usage:
 * 
 * To give an npc some cash, simply add the following line to the end
 * of the create_* function:
 * MAKE_MONEY;
 *
 * You should not call get_money directly, as used to occur.  All code
 * with set_alarm(1.0,0.0,"get_money"); should be changed.
 *
 * If you want to add a bit more cash, just to get those players killing
 * your npcs that much more, there are four functions to allow you to
 * add specific amounts of money.  The functions are:
 * make_copper(num);
 * make_silver(num);
 * make_gold(num);
 * make_platinum(num);
 *
 * Try not to add too much to your npcs, we don't want players wandering
 * about with their purses bursting the seams :)
 *
 * If you find any problems with this code, feel free to mail me.
 * Duragus.
 */
#pragma strict_types
#pragma save_binary

#include <money.h>
#include "/d/Shire/cypress/sys/defs.h"

int amount_of_coin, amount_of_coin2;
string type_of_coin, type_of_coin2;

private void make_money( int i, string type );
private int *add_arrays( mixed list1, int *list2 );
       
private mixed
set_npc_val()
{
   int npc_avg, ran_num;
   npc_avg = PO->query_average_stat();
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

public void
get_money()
{

   set_npc_val();
   make_money(amount_of_coin, type_of_coin);
   make_money(amount_of_coin2, type_of_coin2);
}

/*
 * This function has been completely overhauled to take advantage of
 * the new money function in the mudlib.  It now sets the OBJ_M_HAS_MONEY
 * property in the object this is called in.  To do this properly, it
 * first queries the property to see if it has anything, then adds to
 * that array.
 */
private void
make_money(int i,string type)
{
   object money;
   mixed money_list;
   int list = 0;

   money_list = (int *)PO->query_prop(OBJ_M_HAS_MONEY);

   if( money_list != 0 )
      list = 1;
      
   switch( type ) {
      case "copper":
	 if( list )
	    PO->add_prop(OBJ_M_HAS_MONEY,add_arrays(money_list,({i,0,0,0})));
	 else
	    PO->add_prop(OBJ_M_HAS_MONEY, ({i,0,0,0}));
	 break;
      case "silver":
	 if( list )
	    PO->add_prop(OBJ_M_HAS_MONEY,add_arrays(money_list,({0,i,0,0})));
	 else
	    PO->add_prop(OBJ_M_HAS_MONEY, ({0,i,0,0}));
	 break;
      case "gold":
	 if( list )
	    PO->add_prop(OBJ_M_HAS_MONEY,add_arrays(money_list,({0,0,i,0})));
	 else
	    PO->add_prop(OBJ_M_HAS_MONEY, ({0,0,i,0}));
	 break;
      case "platinum":
	 if( list )
	    PO->add_prop(OBJ_M_HAS_MONEY,add_arrays(money_list,({0,0,0,i})));
	 else
	    PO->add_prop(OBJ_M_HAS_MONEY, ({0,0,0,i}));
	 break;
      default:
	 log_file("make_money",ctime(time())+":Bad money type " + type + "\n");

	 }
}

private int *
add_arrays( mixed list1, int *list2 )
{
   int n1, n2, i;
   int *result = ({});

   if( intp(list1) )
      list1 = (int *)MONEY_FN->split_values(list1);

   n1 = sizeof(list1);
   n2 = sizeof(list2);

   if( n1 == n2 ) 
   {
      for( i = 0 ; i < n1 ; i++ )
	 result += ({list1[i] + list2[i]});
      return result;
   }
   else if( n1 > n2 ) 
   {
      for( i = 0 ; i < n2 ; i++ )
   	 result += ({list1[i] + list2[i]});
      result += list1[i..n1];
      return result;
   }
   else
   {
      for( i = 0 ; i < n1 ; i++ )
   	 result += ({list1[i] + list2[i]});
      result += list2[i..n2];
      return result;
   }
}

public void
make_gold(int coin_amount)
{
   amount_of_coin = coin_amount;
   make_money(amount_of_coin, "gold");
}

public void
make_silver(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "silver");
}

public void
make_copper(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "copper");
}
  
public void
make_platinum(int coin_amount)
{
  amount_of_coin = coin_amount;
  make_money(amount_of_coin, "platinum");
}
