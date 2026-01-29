inherit "/std/room";
inherit "/lib/trade";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <macros.h>

#define NOSEWAIT 10

string ringname;
int earned;

sign()
{
  return "The sign says:\n\n"+
    "+---------------------------------------------------------+\n"+
    "|          THE CIUBORI NOSE-RING SPECIALIST SHOP          |\n"+
    "+---------------------------------------------------------+\n"+
    "|                                                         |\n"+
    "|    You can choose between gold or moonstone material.   |\n"+
    "|To buy a nose-ring you only have to type <ringbuy> <type>|\n"+
    "|If you want know the cost, type <cost> <type>. If you are|\n"+
    "|  not satisfied with your ring and want it removed type  |\n"+
    "|                       <removering>.                     |\n"+
    "|                                                         |\n"+
    "+---------------------------------------------------------+\n";
}

create_room()
{
  set_short("The nose-ring shop");
  set_long(break_string(
    "You're standing inside a weird shop. The walls are painted "+
    "white and so are the floor and the roof. A chair is placed in the "+
    "centre of the room. There is a sign on the wall.\n",60));

  add_exit(CIUBORI+"sapphire/street1","east");
  earned=0;
  add_cmd_item("sign","read","@@sign");
  add_item("sign","@@sign");
  config_default_trade();
}
int query_earned()
{
  return earned;
}
init()
{
  ::init();

    add_action("ringbuy"   ,"ringbuy");
    add_action("ringcost"  ,"cost");
    add_action("ringremove","removering");
  }

int query_cost(string str)
{
  if (str == "gold") return 1728;
  else if (str == "moonstone") return 172800;
  else return 0;
}

ringcost(string str)
{
  string rst;  

  say(QCTNAME(TP)+" queries about the cost for a "+str+" ring.\n");
  if (str == "gold") rst = "1 platinum coin";
  else if (str == "moonstone") rst == "100 platinum coins";
  else rst = "something";

  TP->catch_msg("You have to pay "+rst+" for it.\n");
  return 1;
}

int
ringbuy(string str)
{
  int cost;

  if(str=="gold" || str=="moonstone")
  {
    cost = query_cost(str);

    if (can_pay(cost,TP)==0)
    {
      TP->catch_msg("You can't afford it!\n");
      return 1;
    }

    pay(cost,TP);

    TP->catch_msg("You pay the owner "+cost+" copper coins when he arrives.\n");
    TP->catch_msg("The owner, a filthy goblin, forces you to sit down "+
      "on the chair.\n");
    say("The owner, a filthy goblin, arrives and forces "+QTNAME(TP)+
      " to sit down in the chair.\n");
    ringname = str + "ring";

    call_out("rb1", NOSEWAIT);

    return 1;
  } 
  return 1;
}

rb1()
{
  TP->catch_msg("The goblin walks to a desk in the corner and fetches a HUGE "+
    "spike!\n");
  say("The goblin walks to a desk in the corner and fetches a HUGE "+
    "spike!\n");
  call_out("rb2", NOSEWAIT);
}

rb2()
{
  TP->catch_msg("The owner walks back and grins as he starts to pierce "+
    "a hole in your nose.\nIt hurts...\n");
  say("The owner walks back again and grins as he starts to pierce "+
    "a hole in "+QTNAME(TP)+"'s nose.\n"+QCTNAME(TP)+" looks as "+
    TP->query_pronoun()+"'s in a lot of pain.\n");
  call_out("rb3", NOSEWAIT);
}

rb3()
{
  TP->catch_msg("The goblin manages to push the gigatic spike through "+
    "the skin between the nostrils, blood starts to flow from your nose "+
    "like the flood in the spring.\n");
  say("The goblin succeds in pushing the gigantic spike through the "+
    "skin between the nostrils, "+QTNAME(TP)+" starts to bleed and blood "+
    "flows down from "+TP->query_possessive()+" nose.\n");
  call_out("rb4", NOSEWAIT);
}

rb4()
{
  TP->catch_msg("The owner fetches a ring from one of his pockets and "+
    "pulls it through the hole in the nose.\nYou scream in pure pain!\n");
  say("The owner fetches a ring from one of his pockets and pulls it "+
    "through the hole in the nose.\n"+QCTNAME(TP)+" starts screaming "+
    "in pain.\n");
  call_out("rb5", NOSEWAIT);
}

rb5()
{
  object ob;

  TP->catch_msg("The goblin owner connects the two edges of the ring and "+
    "voila! You have your own "+ringname+" nose-ring!.\n");
  say(QCTNAME(TP)+" shrieks loud when the owner connects the ring "+
    "edges and rises up from the chair on shivering legs.\n");
  ob = clone_object(OBJ + ringname);
  ob->move(TP);
}
