/*
* Rich Men's Club
*
* Coded by Conan Jan -95
*
*/

#pragma save_binary

inherit "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <money.h>

int test;
object t;

int move_item(mixed arg);

sign()
{
  return "The sign reads:\n\n"+
  "+-----------------------------------------+\n"+
  "| o                                     o |\n"+
  "|   T H E   R I C H   M E N ' S   B A R   |\n"+
  "|                                         |\n"+
  "| You can order the following things here |\n"+
  "|                                         |\n"+
  "|    a glass of water.............1 cc    |\n"+
  "|    a packet of peanuts.........10 cc    |\n"+
  "|    a pint of cold beer.........20 cc    |\n"+
  "|    a havana cigar..............30 cc    |\n"+
  "|    a glass of bordeaux.........80 cc    |\n"+
  "|    a glass of finest whiskey..140 cc    |\n"+
  "|    a glass of aged cognac.....180 cc    |\n"+
  "|    a picnic lunch bag.........300 cc    |\n"+
  "|                                         |\n"+
  "|  You can also 'start here' if you want  |\n"+
  "|     this as your starting location.     |\n"+
  "| o                                     o |\n"+
  "+-----------------------------------------+\n\n";
}

public void
create_room()
{
  config_default_trade();

  set_short("Second floor of The Rich Men's Club");
  set_long(break_string(
    "You are on the second floor of 'The Rich Men's Club'. "+
    "This elegantly furnished room is filled with cigar smoke. "+
    "A bar is standing in the middle of it, serving drinks to "+
    "the members. Stairs leads up and down from here and "+
    "there is a sign on the wall.\n",60));
  
  add_item("sign","@@sign");
  add_cmd_item("sign","read","@@sign");
  add_item("bar","It's a nice bar where all sorts of drinks are served.\n");
  add_item("stairs","They are leading up and down and are made of "+
    "dark stone.\n");
  add_item("furniture","That furniture must have cost a fortune.\n");
  
  add_exit(RMCROOMS+"private3","up","@@check");
  add_exit(RMCROOMS+"private1","down",0);
  
  INSIDE;

}

void
init()
{
  ::init(); 
  add_action("start","start");
  add_action("order", "buy");
  add_action("order", "order");
}

int
check()
{
  FIXEUID;
  
  if (TP->query_wiz_level()>0) return 0;

  if (RMCMASTER->query_level(TP->query_real_name()) > 8) return 0;
  
  write("Nah, those stairs looks slippery...it's safer here.\n");
  return 1;
}

int
order(string str)
{
  string name, str1, str2, str3;
  int *arr, price, num;

  NF("buy what?\n");
  if (!str)
    return 0;

  if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
  {
    str3 = "";
    if (sscanf(str, "%s with %s", str1, str2) != 2)
    {
      str2 = "";
      str1 = str;
    }
  }

  if (sscanf(str1, "%d %s", num, str1) != 2)
    num = 1;

  if (num > 10) num = 10;

  switch(str1)
  { 
  case "water":
  case "waters":
    name = "water";
    price = num * 1;
    break;
  case "pack":
  case "packs":
  case "peanuts":
    name = "peanuts";
    price = num * 10;
    break;
  case "beer":
  case "beers":
    name = "coldbier";
    price = num * 20;
    break;
  case "cigar":
  case "cigars":
    name = "cigar";
    price = num * 30;
    break;
  case "bordeaux":
  case "bordeaux'":
    name = "bordeaux";
    price = num * 80;
    break;
  case "whiskey":
  case "whiskeys":
    name = "whiskey";
    price = num * 140;
    break;
  case "whiskey":
  case "whiskeys":
    name = "whiskey";
    price = num * 140;
    break;
  case "cognac":
  case "cognacs":
    name = "cognac";
    price = num * 180;
    break;
  case "bag":
  case "bags":
    name = "picnic";
    price = num * 300;
    break;
  default:
    NF("I don't understand what you want to buy.\n");
    return 0;
  }

  if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
    return 0;  /* pay() handles notify_fail() call */
  
  write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
  if (text(exclude_array(arr, 0, NUM-1)))
    write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
  write("The bartender starts working with your order.\n");

  return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
  object drink, ob;
  string file, name;
  int i, num;

  name = arg[0];
  num = arg[1];
  ob = arg[2];

  for (i = 0; i < 10; i++)
  {
    num--;
    file = RMCOBJ + name;
    drink = clone_object(file);

    if (!test && (drink->move(ob)))
    {
      ob->catch_msg("You drop the " + drink->short() +
        " on the floor.\n");
      say(QCTNAME(ob) + " drops a " + drink->short() +
        " on the floor.\n", ob);
      drink->move(TO);
    } else if (!test) {
      if (num == 0)
      {
        if (arg[1] > 1)
        {
          ob->catch_msg("You get some " + drink->plural_short() +
            ".\n");
          say(QCTNAME(ob) + " buys some " + drink->plural_short() +
            ".\n", ob);
        } else {
          ob->catch_msg("You get " + drink->short() + ".\n");
          say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
            ob);
        }
      }
    } else {
      say(QCTNAME(ob) + " seems to be estimating something.\n",
        ob);
    return 1;
    }
    if (num < 1)
      break;
  }

  if (num > 0)
    set_alarm(1.0, 0.0, &move_item(1, ({name, num, ob})));
  return 1;
}

int start(string s)
{
   //TP->set_temp_start_location(RMCMASTER+"richprivate2");
   TP->set_temp_start_location(RMCROOMS+"private2");
   write("Ok, you will be starting here. But note that it's only temporary. "+
     "You have to type 'start here' every time you log in. This inconvenience "+
     "has occurred since the club hasn't gained the status as default starting "+
     "place yet. When and if it has, it will be noticed here or on the board "+
     "downstairs. Conan.\n");
   return 1;
}
