#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <money.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

#define BARTENDER     THIS_DIR + "bartender"
#define BOTTLE        OBJ_DIR + "bottle"
#define GLASS         OBJ_DIR + "bottle"
#define NUM           sizeof(MONEY_TYPES)

/*
 * Prototypes
 */
void reset_room();

static object bartender;
static int    alarm;

void
create_room()
{
  add_prop(ROOM_I_INSIDE,1); 

  config_default_trade();  /* Set up the trading system */

  set_short("Army pub");
  set_long("This is the place where Angmar's warriors spend most of "+
	"the money they have - the pub. It is newly rebuilt "+
	"because the old one has been destroyed by angry Angmar's warriors "+
        "because of the lack of the rum. The new bartender therefore tries "+
       "his best to have a full stock all the time. There is a sign next "+
	"to the exit and a counter with a sink. A menu is lying on the "+
	"counter and behind it "+
	"you can see huge barrels and a shelf full of glasses and "+
	"empty bottles.\n");

  add_item(({"sink","water"}), "The sink is full of water. Bartender "+
	"washes glasses there before he puts them back on the shelf.\n");
  add_item(({"shelf","bottles","bottle","glasses","glass"}), "There are "+
	"many kinds of bottles and glasses on the shelf ready for use.\n");
  add_item(({"barrels","barrel"}), "Huge barrels containing supply of "+
	"drinks for the whole army.\n");
  add_item("counter", "It's made out of wood. On one side there is a "+
	"sink full of water and on the other side you see a menu.\n");
  add_item("menu","An ordinary menu, what did you expected? It is here "+
	"for everyone to read it.\n");
  add_cmd_item("menu","read","@@read_menu"); 
  add_item("exit","You should use it if you want to leave.\n");
  add_item("sign","A big sign nailed to the wall.\n");
  add_cmd_item("sign","read","@@read_sign"); 

  add_exit(THIS_DIR+"c2", "west", "@@block_exit@@");

  reset_room();
}

string
read_menu()
{
  if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
  return "\nYou can buy:\n\n"+
	"pint or half pint of:\n"+
	"   ale ................ 13 /  7 cc\n"+
	"   apple cider ........ 20 / 10 cc\n"+
	"   dark beer .......... 30 / 16 cc\n\n"+
        "glass of\n"+
        "   light table wine ... 22 cc\n"+
	"   white wine ......... 34 cc\n"+
	"   heavy red wine ..... 45 cc\n\n"+
	"small, regular or double \n"+
	"   cherry ............. 12 /  23 /  44 cc\n"+
	"   brandy ............. 42 /  83 / 164 cc\n"+
	"   strong rum ......... 92 / 183 / 364 cc\n\n"+
	"You can also buy whole bottle of drink to take it away.\n"+
	"Please read sign for prices. Also you can ask me to\n"+
	"refill your bottle or glass with whatever is available.\n\n";
}

string
read_sign()
{
  if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
  return "\n"+
"    +--------------------------------------------------+\n"+
"    |                                                  |\n"+
"    |    No glasses out of this room!                  |\n"+
"    |      Return them on the counter before you go.   |\n"+
"    |                                                  |\n"+
"    +--------------------------------------------------+\n"+
"\n"+
"If you want to take drink with you you can buy full bottle.\n"+
"I have three sizes of bottles available:\n"+
"   small .............  96 cc\n"+
"   medium ............ 176 cc\n"+
"   big ............... 410 cc\n\n"+
"Here are prices of bottle of (excluding price of the bottle):\n"+
"   ale ................   21 /   38 /    86 cc\n"+
"   apple cider ........   31 /   56 /   128 cc\n"+
"   dark beer ..........   47 /   86 /   198 cc\n\n"+
"   light table wine ...   84 /  153 /   355 cc\n"+
"   white wine .........  136 /  248 /   576 cc\n"+
"   heavy red wine .....  178 /  326 /   758 cc\n\n"+
"   cherry .............  348 /  632 /  1472 cc\n"+
"   brandy ............. 1338 / 2432 /  5672 cc\n"+
"   strong rum ......... 2988 / 5432 / 12672 cc\n\n";
}

void
reset_room()
{
  if(bartender)
  {
    if(present(bartender,TO)) return;

    bartender->command("oops");
    bartender->command("say I must not leave my pub!");
    bartender->command("ponder destroyed pub because of no bartender");
    tell_room(ENV(bartender), QCTNAME(bartender)+" runs back to "+HIS(bartender)+
                           " pub.\n");
    bartender->move_living("M", TO);
    tell_room(TO, QCTNAME(bartender)+" arrives running.\n");
    bartender->command("say Back again.");
    bartender->command("emote quickly looks around.");
    bartender->command("sigh relieved");
    bartender->command("say It will not happen again. Just don't destroy "+
			"the pub like the last time, please.");
    return;
  }
  
  bartender = clone_object(BARTENDER);
  bartender->arm_me();
  bartender->move_living("M",TO);
  bartender->command("say Back in business.");
  bartender->command("emote quickly looks around.");
  bartender->command("sigh relieved");
  bartender->command("say It will not happen again. Just don't destroy "+
			"the pub like the last time, please.");
} 

init()
{
  ::init();
  add_action("do_buy","buy");
  add_action("do_buy","order");
  add_action("do_return","return");
  add_action("do_return","put");
  add_action("do_return","give");
  add_action("do_refill","refill");
}

int
do_return(string arg)
{
  object *list, *tmp;
  string what;
  int i, j;

  NF(CAP(query_verb())+" what?\n");
  if(!arg) return 0;

  arg = implode((explode(arg, " ")-({"the","a","an","on","counter"})), " ");

  tmp = FIND_STR_IN_OBJECT(arg, TP);
  list = ({ });
  for(i=0; i<sizeof(tmp); i++)
    if(member_array("_a_p_g_", tmp[i]->query_names()) != -1)
      list += ({ tmp[i] });

  if(!sizeof(list)) return 0;

  write("You put "+COMPOSITE_DEAD(list)+" on the counter.\n");
  say(QCTNAME(TP)+" puts "+QCOMPDEAD+" on the counter.\n");
  if(bartender && present(bartender,TO))
    for(i=0; i<sizeof(list); i++)
      list[i]->move(bartender);
  else
    for(i=0; i<sizeof(list); i++)
      list[i]->remove_object();
  return 1;
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(!alarm && (member_array("_a_p_g_",ob->query_names()) != -1))
  {
    set_alarm(itof(10+random(10)), 0.0, "get_glasses");
    alarm = 1;
  }
}

void
get_glasses()
{
  alarm = 0;
  if(bartender && present(bartender,TO) && present("_a_p_g_", TO))
  {
    bartender->command("say Why some customers can't return glasses?");
    bartender->command("sigh");
    bartender->command("get glasses");
  }
}

int
check_bartender(string arg)
{
  object enemy;
  string who;

  if (bartender && present(bartender,TO))
  {
    who = TP->query_nonmet_name();
    if(enemy = bartender->query_attack())
    {
      if(enemy == TP)
      {
        bartender->command("say Now you want to "+arg+" something?");
        bartender->command("ponder stupid "+who);
      }
      else
      {
        bartender->command("say Please "+who+"! Dont you see that I have "+
			"to fight "+enemy->query_nonmet_name()+"? "+
                        "Maybe you can help me too?");
        bartender->command("wink at "+TP->query_name());
      }
      return 0;
    }
    else 
      return 1;
  }
  else
  {
    TP->catch_msg("There is no bartender here. You must wait for him.\n");
    return 0;
  }
}

int
check_light()
{
  if(CAN_SEE_IN_ROOM(bartender)) return 1;
  bartender->command("say I am sorry, but I can't work when I can't see...");
  bartender->command("sigh");
  return 0;
}

object
make_pint()
{
  object glass;

  seteuid(geteuid(TO));
  glass = clone_object(GLASS);
  glass->set_adj("pint");
  glass->set_short("pint glass");
  glass->set_pshort("pint glasses");
  glass->set_max(540);
  return glass;
}
object
make_half_pint()
{
  object glass;

  seteuid(geteuid(TO));
  glass = clone_object(GLASS);
  glass->set_adj(({"pint","half"}));
  glass->set_short("half pint glass");
  glass->set_pshort("half pint glasses");
  glass->set_max(270);
  return glass;
}
object
make_glass()
{
  object glass;

  seteuid(geteuid(TO));
  glass = clone_object(GLASS);
  glass->set_adj("wine");
  glass->set_short("wine glass");
  glass->set_pshort("wine glasses");
  glass->set_max(200);
  return glass;
}
object
make_small()
{
  object glass;

  seteuid(geteuid(TO));
  glass = clone_object(GLASS);
  glass->set_adj("small");
  glass->set_short("small glass");
  glass->set_pshort("small glasses");
  glass->set_max(25);
  return glass;
}
object
make_regular()
{
  object glass;

  seteuid(geteuid(TO));
  glass = clone_object(GLASS);
  glass->set_adj("regular");
  glass->set_short("regular glass");
  glass->set_pshort("regular glasses");
  glass->set_max(50);
  return glass;
}
object
make_double()
{
  object glass;

  seteuid(geteuid(TO));
  glass = clone_object(GLASS);
  glass->set_adj("double");
  glass->set_short("double glass");
  glass->set_pshort("double glasses");
  glass->set_max(100);
  return glass;
}

int
do_buy(string arg)
{
  object glass, bottle;
  int price, price2, *arr;
  string arg1, arg2;

  NF("");
  if(!check_bartender("buy")) return 0;
  if(!check_light()) return 0;

  NF("Buy what?\n");
  if (!arg || arg =="") return 0;

  TP->catch_msg("You order yourself "+arg+".\n");
  say(QCTNAME(TP)+" orders "+HIM(TP)+"self "+arg+".\n");

  arg = implode((explode(arg, " ")-({"the","a","an","of","glass","pint","regular"})), " ");
  switch (arg)
  {
    case "ale":
	glass = make_pint();
	glass->set_filled_short(({"ale"}));
	glass->set_alco(2 * glass->query_max() / 100);
	break;
    case "apple cider":
    case "cider":
	glass = make_pint();
	glass->set_filled_short(({"apple cider"}));
	glass->set_alco(4 * glass->query_max() / 100);
	break;
    case "dark beer":
    case "beer":
	glass = make_pint();
	glass->set_filled_short(({"dark beer"}));
	glass->set_alco(6 * glass->query_max() / 100);
	break;
    case "half ale":
    case "small ale":
	glass = make_half_pint();
	glass->set_filled_short(({"ale"}));
	glass->set_alco(2 * glass->query_max() / 100);
	break;
    case "half apple cider":
    case "half cider":
    case "small apple cider":
    case "small cider":
	glass = make_half_pint();
	glass->set_filled_short(({"apple cider"}));
	glass->set_alco(4 * glass->query_max() / 100);
	break;
    case "half dark beer":
    case "half beer":
    case "small dark beer":
    case "small beer":
	glass = make_half_pint();
	glass->set_filled_short(({"dark beer"}));
	glass->set_alco(6 * glass->query_max() / 100);
	break;
    case "light table wine":
    case "table wine":
    case "light wine":
	glass = make_glass();
	glass->set_filled_short(({"light table wine"}));
	glass->set_alco(9 * glass->query_max() / 100);
	break;
    case "white wine":
	glass = make_glass();
	glass->set_filled_short(({"white wine"}));
	glass->set_alco(12 * glass->query_max() / 100);
	break;
    case "heavy red wine":
    case "red wine":
    case "heavy wine":
	glass = make_glass();
	glass->set_filled_short(({"heavy red wine"}));
	glass->set_alco(14 * glass->query_max() / 100);
	break;
    case "wine":
	bartender->command("say Please, specify which wine do you want.");
	bartender->command("say I have light table wine, white wine "+
				"and heavy red wine.");
	bartender->command("point at menu");
	return 1;
    case "small cherry":
	glass = make_small();
	glass->set_filled_short(({"cherry"}));
	glass->set_alco(20 * glass->query_max() / 100);
	break;
    case "cherry":
	glass = make_regular();
	glass->set_filled_short(({"cherry"}));
	glass->set_alco(20 * glass->query_max() / 100);
	break;
    case "double cherry":
	glass = make_double();
	glass->set_filled_short(({"cherry"}));
	glass->set_alco(20 * glass->query_max() / 100);
	break;
    case "small brandy":
	glass = make_small();
	glass->set_filled_short(({"brandy"}));
	glass->set_alco(40 * glass->query_max() / 100);
	break;
    case "brandy":
	glass = make_regular();
	glass->set_filled_short(({"brandy"}));
	glass->set_alco(40 * glass->query_max() / 100);
	break;
    case "double brandy":
	glass = make_double();
	glass->set_filled_short(({"brandy"}));
	glass->set_alco(40 * glass->query_max() / 100);
	break;
    case "small strong rum":
    case "small rum":
	glass = make_small();
	glass->set_filled_short(({"strong rum"}));
	glass->set_alco(60 * glass->query_max() / 100);
	break;
    case "strong rum":
    case "rum":
	glass = make_regular();
	glass->set_filled_short(({"strong rum"}));
	glass->set_alco(60 * glass->query_max() / 100);
	break;
    case "double strong rum":
    case "double rum":
	glass = make_double();
	glass->set_filled_short(({"strong rum"}));
	glass->set_alco(60 * glass->query_max() / 100);
	break;
  }
  if(glass)
  {
    glass->set_name(({"glass", "_a_p_g_"}));
    glass->set_pname("glasses");
    glass->set_soft(glass->query_max());
    glass->remove_prop(OBJ_I_VALUE);

    price = 2 + (glass->query_soft()/50) +
	    (10*glass->query_alco()*glass->query_alco()/glass->query_soft());

    arr = pay(price, TP, "", 0, 0, "", 0);

    if(sizeof(arr) == 1)
    {
      bartender->command("say But you can't afford that!");
      glass->remove_object();
      return 1;
    }
    write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
    say(QCTNAME(TP)+" pays "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
    if (text(exclude_array(arr, 0, NUM-1))) 
    {
      write("You get "+text(exclude_array(arr, 0, NUM-1))+" back.\n");
      say(QCTNAME(bartender)+" gives "+text(exclude_array(arr, 0, NUM-1))+
	" back.\n");
    }
    tell_room(TO, QCTNAME(bartender)+" takes a "+glass->query_short()+
	" from the shelf and fills it with the "+
	glass->query_filled_short()[0]+".\n");
    TP->catch_msg(QCTNAME(bartender)+" hands you the "+
	glass->query_short()+".\n");
    say(QCTNAME(bartender)+" hands "+QTNAME(TP)+" the "+
	glass->query_short()+".\n");
    if(glass->move(TP)) 
    {
      bartender->command("oops");
      bartender->command("say I see that you can't cary it... "+
			"I will leave it here for you.");
      bartender->command("emote puts the "+glass->query_short()+
			" on the counter.");
      glass->move(TO);
    }
    return 1;
  }
/*********************************************************************/
  sscanf(arg, "%s bottle %s", arg1, arg2);

  NF("");
  if(arg1 && !arg2)
  {
    bartender->command("say What do you want to buy?");
    bartender->command("peer at "+TP->query_real_name());
    return 0;
  }
  if(arg1 && member_array(arg1, ({"small","medium","big"})) == -1)
  {
    bartender->command("say You must chose one of the bottles I have.");
    bartender->command("point at sign");
    return 0;
  }
  if(!arg1)
    sscanf(arg, "bottle %s", arg2);

  seteuid(geteuid(TO));
  bottle = clone_object(BOTTLE);
  bottle->set_name("bottle");
  bottle->set_pname("bottles");
  if(arg1)
  {
    bottle->set_adj(arg1);
    bottle->set_short(arg1+" bottle");
    bottle->set_pshort(arg1+" bottles");
    switch (arg1)
    {
      case "small":
        bottle->set_max(825);
        break;
      case "medium":
        bottle->set_max(1500);
        break;
      case "big":
        bottle->set_max(3500);
        break;
    }
  }
  else
  {
    switch (arg2)
    {
      case "ale":
      case "apple cider":
      case "cider":
      case "dark beer":
      case "beer":
        bottle->set_adj("big");
    	bottle->set_short("big bottle");
    	bottle->set_pshort("big bottles");
        bottle->set_max(3500);
	break;
      case "light table wine":
      case "light wine":
      case "table wine":
      case "white wine":
      case "heavy red wine":
      case "heavy wine":
      case "red wine":
        bottle->set_adj("medium");
    	bottle->set_short("medium bottle");
    	bottle->set_pshort("medium bottles");
        bottle->set_max(1500);
	break;
      case "cherry":
      case "brandy":
      case "rum":
      case "strong rum":
        bottle->set_adj("small");
    	bottle->set_short("small bottle");
    	bottle->set_pshort("small bottles");
        bottle->set_max(825);
	break;
      case "wine":
	bartender->command("say Please, specify which wine do you want.");
	bartender->command("say I have light table wine, white wine "+
				"and heavy red wine.");
	bartender->command("point at sign");
	bottle->remove_object();
      	return 1;
      default:
	bartender->command("say What drink do you want in the bottle?");
	bottle->remove_object();
      	return 0;
    }
  }
  bottle->set_soft(bottle->query_max());
  switch (arg2)
  {
    case "ale":
	bottle->set_filled_short(({"ale"}));
	bottle->set_alco(2 * bottle->query_max() / 100);
      	break;
    case "apple cider":
    case "cider":
	bottle->set_filled_short(({"apple cider"}));
	bottle->set_alco(4 * bottle->query_max() / 100);
      	break;
    case "dark beer":
    case "beer":
	bottle->set_filled_short(({"dark beer"}));
	bottle->set_alco(6 * bottle->query_max() / 100);
      	break;
    case "light table wine":
    case "light wine":
    case "table wine":
	bottle->set_filled_short(({"light table wine"}));
	bottle->set_alco(9 * bottle->query_max() / 100);
      	break;
    case "white wine":
	bottle->set_filled_short(({"white wine"}));
	bottle->set_alco(12 * bottle->query_max() / 100);
      	break;
    case "heavy red wine":
    case "heavy wine":
    case "red wine":
	bottle->set_filled_short(({"heavy red wine"}));
	bottle->set_alco(14 * bottle->query_max() / 100);
      	break;
    case "wine":
	bartender->command("say Please, specify which wine do you want.");
	bartender->command("say I have light table wine, white wine "+
				"and heavy red wine.");
	bartender->command("point at sign");
	bottle->remove_object();
      	return 1;
    case "cherry":
	bottle->set_filled_short(({"cherry"}));
	bottle->set_alco(20 * bottle->query_max() / 100);
      	break;
    case "brandy":
	bottle->set_filled_short(({"brandy"}));
	bottle->set_alco(40 * bottle->query_max() / 100);
      	break;
    case "strong rum":
    case "rum":
	bottle->set_filled_short(({"strong rum"}));
	bottle->set_alco(60 * bottle->query_max() / 100);
      	break;
    default:
	bartender->command("say What drink do you want in the bottle?");
	bottle->remove_object();
      	return 0;
  }
  price = 2 + (bottle->query_soft()/50) +
	  (10*bottle->query_alco()*bottle->query_alco()/bottle->query_soft());
  price2 = 2*bottle->query_prop(OBJ_I_VALUE);

  arr = pay(price+price2, TP, "", 0, 0, "", 0);

  if(sizeof(arr) == 1)
  {
    bartender->command("say But you can't afford that!");
    bottle->remove_object();
    return 1;
  }
  write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
  say(QCTNAME(TP)+" pays "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
  if (text(exclude_array(arr, 0, NUM-1))) 
  {
    write("You get "+text(exclude_array(arr, 0, NUM-1))+" back.\n");
    say(QCTNAME(bartender)+" gives "+text(exclude_array(arr, 0, NUM-1))+
	" back.\n");
  }
  tell_room(TO, QCTNAME(bartender)+" takes a "+bottle->query_short()+
	" from the shelf and fills it with the "+
	bottle->query_filled_short()[0]+".\n");
  TP->catch_msg(QCTNAME(bartender)+" hands you the "+
	bottle->query_short()+".\n");
  say(QCTNAME(bartender)+" hands "+QTNAME(TP)+" the "+
	bottle->query_short()+".\n");
  if(bottle->move(TP)) 
  {
    bartender->command("oops");
    bartender->command("say I see that you can't cary it... "+
			"I will leave it here for you.");
    bartender->command("emote puts the "+bottle->query_short()+
			" on the counter.");
    bottle->move(TO);
  }
  return 1;
}

block_exit()
{
  if (present("_a_p_g_",TP) && bartender && present(bartender,TO))
  {
    write("You start to move towards the exit...\n");
    tell_room(TO, QCTNAME(TP)+" starts to move towards the exit...\n", TP);
    bartender->command("shout Can't you read?");
    bartender->command("grin at "+TP->query_real_name());
    bartender->command("point at sign");
    bartender->command("shout Return glasses and then you can go!");
    return 1;
  }
  return 0;
}

int
do_refill(string arg)
{
  string bottle, drink;
  object *tmp;
  int s, price, *arr;

  NF("");
  if(!check_bartender(query_verb())) return 0;
  if(!check_light()) return 0;

  NF(CAP(query_verb())+" what?\n");
  if(!arg) return 0;

  NF(CAP(query_verb())+" what with what?\n");
  if(sscanf(arg, "%s with %s", bottle, drink) != 2) return 0;

  tmp = FIND_STR_IN_OBJECT(bottle, TP);
  if(!sizeof(tmp)) return 0;

  TP->catch_msg("You ask "+QTNAME(bartender)+" to "+query_verb()+" "+arg+".\n");
  say(QCTNAME(TP)+" asks "+QTNAME(bartender)+" to "+query_verb()+" "+arg+".\n");

  NF(VBFC_ME("one_bottle_at_a_time"));
  if(sizeof(tmp)>1) return 0;

  NF(VBFC_ME("wrong_bottle"));
  if(!(s = (tmp[0]->query_max()))) return 0;

  NF(VBFC_ME("nonempty_bottle"));
  if(tmp[0]->query_soft()) return 0;

  NF(VBFC_ME("wrong_drink"));
  drink = implode((explode(drink, " ")-({"the","a","an"})), " ");
  switch(drink)
  {
    case "ale":
	tmp[0]->set_filled_short(({"ale"}));
	tmp[0]->set_alco(2 * s / 100);
      	break;
    case "apple cider":
    case "cider":
	tmp[0]->set_filled_short(({"apple cider"}));
	tmp[0]->set_alco(4 * s / 100);
      	break;
    case "dark beer":
    case "beer":
	tmp[0]->set_filled_short(({"dark beer"}));
	tmp[0]->set_alco(6 * s / 100);
      	break;
    case "light table wine":
    case "light wine":
    case "table wine":
	tmp[0]->set_filled_short(({"light table wine"}));
	tmp[0]->set_alco(9 * s / 100);
      	break;
    case "white wine":
	tmp[0]->set_filled_short(({"white wine"}));
	tmp[0]->set_alco(12 * s / 100);
      	break;
    case "heavy red wine":
    case "heavy wine":
    case "red wine":
	tmp[0]->set_filled_short(({"heavy red wine"}));
	tmp[0]->set_alco(14 * s / 100);
      	break;
    case "wine":
	bartender->command("say Please, specify which wine do you want in it.");
	bartender->command("say I have light table wine, white wine "+
				"and heavy red wine.");
	bartender->command("point at sign");
      	return 1;
    case "cherry":
	tmp[0]->set_filled_short(({"cherry"}));
	tmp[0]->set_alco(20 * s / 100);
      	break;
    case "brandy":
	tmp[0]->set_filled_short(({"brandy"}));
	tmp[0]->set_alco(40 * s / 100);
      	break;
    case "strong rum":
    case "rum":
	tmp[0]->set_filled_short(({"strong rum"}));
	tmp[0]->set_alco(60 * s / 100);
      	break;
    default:
      	return 0;
  }
  tmp[0]->set_soft(s);
  price = 2 + (s/50) + (10*tmp[0]->query_alco()*tmp[0]->query_alco()/s);

    arr = pay(price, TP, "", 0, 0, "", 0);

    if(sizeof(arr) == 1)
    {
      bartender->command("say But you can't afford that!");
      tmp[0]->set_alco(0);
      tmp[0]->set_filled_short("");
      tmp[0]->set_soft(0);
      return 1;
    }
    write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
    say(QCTNAME(TP)+" pays "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
    if (text(exclude_array(arr, 0, NUM-1))) 
    {
      write("You get "+text(exclude_array(arr, 0, NUM-1))+" back.\n");
      say(QCTNAME(bartender)+" gives "+text(exclude_array(arr, 0, NUM-1))+
	" back.\n");
    }
    say(QCTNAME(bartender)+" takes a "+tmp[0]->query_short()+
	" from "+QTNAME(TP)+" and fills it with the "+
	tmp[0]->query_filled_short()[0]+".\n");
    TP->catch_msg(QCTNAME(bartender)+" takes a "+tmp[0]->query_short()+
	" from you and fills it with the "+
	tmp[0]->query_filled_short()[0]+".\n");
    TP->catch_msg(QCTNAME(bartender)+" hands you the "+
	tmp[0]->query_short()+".\n");
    say(QCTNAME(bartender)+" hands "+QTNAME(TP)+" the "+
	tmp[0]->query_short()+".\n");
    return 1;
}

string
one_bottle_at_a_time()
{
  bartender->command("say I can fill only one thing at a time.");
  return "";
}

string
wrong_bottle()
{
  bartender->command("say I don't fill that.");
  return "";
}

string
nonempty_bottle()
{
  bartender->command("say Better first empty it.");
  return "";
}

string
wrong_drink()
{
  bartender->command("say What do I have to fill it with?.");
  return "";
}