/****************************************/
/*    Kitchen of Icewall Castle */
/* Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
inherit "/lib/trade";
inherit ICEINROOM;
#define NUM sizeof(MONEY_TYPES)

int test;
object andrea;
/* Andrea and fooditems created by Stevenson */

int move_item(mixed arg);

reset_icewall_room() 
{
    if (!andrea) 
      {
	  andrea=clone_object(ICE_CAST_M+"andrea");
	  andrea->move(TO);
      }
}

init() {
    ADA("buy");
    ADD("buy","get");
    ADA("test");
    ::init();
}

create_icewall_room()
{
    config_default_trade();
    set_short("Andrea's Kitchen");
    set_long("You are standing in a very large kitchen which is cluttered"
	     + " with all sorts of kitchen utensils. There is a large table"
	     + " in the middle of the room at which a very busy cook is chopping"
	     + " something to death. There are trails of blood all over"
	     + " the floor and a large, solid-fuel cooker sits in one corner."
	     + " On the wall is a sign.\n");
    
    add_item("sign","It is readable.\n");
    add_cmd_item("sign","read","@@read");
    add_item("utensils",
	     "There are all sorts of cooking utensils lying around the room.\n");
    add_item("table",
	     "The large, wooden table is used for preparing food.\n");
    add_item("cook",
	     "She is chopping at something with a large meat cleaver.\n");
    add_item("cleaver",
	     "The cook is holding a very sharp cleaver.\n");
    add_item("blood",
	     "It looks like many animals have met their death here.\n");
    add_item("cooker",
	     "There are various pots and pans sitting on the cooker.\n");
    add_item(({"pots","pot","pans","pan"}),
	     "There is steam rising off each of the pots.\n");
    
    
    
    add_exit(ICE_CAST1_R + "main_hall.c", "west");
    
    reset_icewall_room();
}

int 
buy(string str) 
{
    string name, str1, str2, str3;
    int * arr, price, num;
    
    NF("Andrea is out chasing chickens right now.\n");
    if (!andrea || !P(andrea, TO)) 
      return 0;
    
    NF("Buy what?\n");
    if (!str) 
      return 0;
    
    if (sscanf(str,"%s with %s and get %s", str1, str2, str3) != 3) 
      {
	  str3 = "";
	  if (sscanf(str,"%s with %s",str1, str2) != 2) 
	    {
		str2 = "";
		str1 = str;
	    }
      }
    
    if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;
    
    if ((str1 == "chicken")||(str1=="chickens")||
	(str1=="pieces of chicken")) 
      {
	  name = "chicken";
	  price = num * 30;

    if (num > 10) 
      {
	  NF("Andrea has only two hands.\n");
	  return 0;
      }
    
     
      if (sizeof(arr = pay(price, TP, str2, test, 0, str3)) == 1)
          return 0;
    
      write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
      if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get "+text(exclude_array(arr,0,NUM-1))+".\n");
      write("Andrea hands out the food.\n");
    
      return move_item(({name, num, TP}));
      }

    if ((str1 == "egg")||(str1=="eggs")||
	(str1=="hardboiled egg") || (str1=="hardboiled eggs")) 
      {
	  name = "egg";
	  price = num * 10;

    if (num > 10) 
      {
	  NF("Andrea has only two hands.\n");
	  return 0;
      }
     
      if (sizeof(arr = pay(price, TP, str2, test, 0, str3)) == 1)
          return 0;
    
      write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
      if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get "+text(exclude_array(arr,0,NUM-1))+".\n");
      write("Andrea hands out the food.\n");
    
      return move_item(({name, num, TP}));
      }

     if ((str1 == "baked chicken")||(str1=="stuffed chicken")||
	(str1=="stuffed and baked chicken")||(str1=="stuffed chickens") ||
        (str1 == "baked chickens")||(str1=="stuffed and baked chickens")) 
      {
	  name = "chicken2";
	  price = num * 60;

    if (num > 10) 
      {
	  NF("Andrea has only two hands.\n");
	  return 0;
      }
    
      if (sizeof(arr = pay(price, TP, str2, test, 0, str3)) == 1)
          return 0;
    
      write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
      if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get "+text(exclude_array(arr,0,NUM-1))+".\n");
      write("Andrea hands out the food.\n");
    
      return move_item(({name, num, TP}));
      }

    else 
      {
	  NF("What did you want to buy?\n");
	  return 0;
      }
    
}

int 
move_item(mixed arg) 
{
    object chicken, ob;
    string file, name;
    int i, num;
    
    name = arg[0];
    num = arg[1];
    ob = arg[2];
    
    for (i=0;i<10;i++) 
      {
	  num--;
	  file = ICE_CAST_O + name;
	  chicken=clone_object(file);
	  
	  if (!test && (chicken->move(ob))) 
	    {
		ob->catch_msg("You drop the " + chicken->short() +
			      " on the floor.\n");
		say(QCTNAME(ob)+" drops a " + chicken->short() +
		    " on the floor.\n",ob);
		chicken->move(TO);
	    }
	  else if (!test) 
	    {
		if (num == 0) 
		  {
		      if (arg[1] > 1) 
			{
			    ob->catch_msg("You get some " + chicken->plural_short() +
					  ".\n");
			    say(QCTNAME(ob)+" buys some "+chicken->plural_short() +
				".\n",ob);
			}
		      else 
			{
			    ob->catch_msg("You get "+chicken->short()+".\n");
			    say(QCTNAME(ob)+" buys "+chicken->short() + ".\n",ob);
			}
		  }
	    } 
	  else 
	    {
		say(QCTNAME(ob)+" seems to be estimating something.\n",ob);
		return 1;
	    }
	  if (num <1) 
	    break;
      }
    if (num>0)
      set_alarm(1.0,0.0,"move_item",({name, num, ob}));
    return 1;
}

int 
test(string str) 
{
    int i;
    string str1;
    
    NF("Test what?\n");
    
    if (sscanf(str, "buy %s",str1)) 
      {
	  test = 1;
	  write("This would be the result of a buy:\n");
	  i = buy(str1);
	  test = 0;
	  return i;
      }
}

string 
read() 
{
    write("\n");
    write(
	  "Welcome to Andrea's Kitchen.\n----------------------------\n"
	  + "Here, I cook only the finest in chicken. You may purchase a "
	  + "mouth-watering piece for yourself for only 30cc. Quite a "
	  + "bargain in these parts, too. Since the chickens are breeding " 
          + "like crazy, I have also added hardboiled eggs to the menu. "
          + "Feel free to taste my stuffed and baken chicken as well. "
          + "If you have a polar bear's appetite "
	  + "you may purchase up to 10 pieces.\n\n'buy chicken' or 'buy chicken with copper' will "
	  + "enact the purchase. 'test buy chicken' will also work. "
	  + "\n\nEnjoy,\nAndrea\n"
	  + "\n");
    return "";
}
