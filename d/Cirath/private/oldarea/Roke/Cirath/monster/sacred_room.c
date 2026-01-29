inherit "/std/room";
#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <money.h>
#include <macros.h>

object servant;

create_room()
{
  set_short("In the Temple");
  set_long("You are in the large Temple hall. The walls are covered with pictures and torches.\n"+
           "There is a small sign on the wall which you better read before doing anything.\n"+
           "In the middle of the room you can see a large altar with some sacred items on.\n"+
           "The atmosphere is peaceful and the only thing. \n");

  add_exit(DRYPLAIN+"dpa6","out");
  call_out("reset_room",1);
  add_item("sign","@@sign");
  add_cmd_item("sign","read","@@sign");

  add_item("altar","It looks like a large table with many sacred items on.\n");
}

sign()
{
  return "If you want to join our Hole Order you have to prove yourself worthy. \n"+
  "If you are worthy you have to stay worthy for the rest of your life, otherwise the gods \n"+
  "will disgrace you from this Order, so pray to your God it wont happen. Being a brother \n"+
  "in this order, gives you some advantages. One thing we don't accept is ANY killing of good \n"+
  "aligned creatures. The only thing to avoid such actions is to kill only knowned evil aligned. \n"+
  "So you better watch your steps.\n";
}

reset_room()
{
  seteuid(getuid());

  if(!servant)
    {
      servant = clone_object(MONSTER+"servant");

      servant->move(TO);
    }
}
init()
{
  ::init();
    add_action("sacrifice","sacrifice");
    add_action("leave","leave");
  }
leave(string s)
{
  NF("Do you want to leave something? Our Holy Order??\n");
  if(s!="order")
    return 0;

  NF("You're not a member!\n");
  if(!present("sacred_brooch",TP))

    return 0;

  present("sacred_brooch",TP)->remove_object();

  write("You leave the order. The servant hits you with his sacred knife.\n"+
        "You start to bleed from a tiny wound. The wound stops bleeding almost \n"+
        "immediately and it only leaves an aching spot.\n");
  say(QCTNAME(TP)+" leaves our Sacred Order. \n"+
        "The Servant hits him with his sacred knife.\n");

  return 1;
}
insert(string s)
{
    NF("Sacrifice what?\n");
    if (!s) return 0;
  if(!parse_command(s,TO,"[platinum] 'coin' 'in' / 'on' [the] 'altar'"))
    return 0;


    if(!servant)
      reset_room();

  NF("You don't have any platinum coins.\n");
  if("/sys/global/money"->move_coins("platinum",1,TP,servant))
    return 0;
  
  say(QCTNAME(TP)+" joins The Holy Temple Order.\n");
  write("You recieve a ametist brooch.\n");
  write("If you REALLY wants to leave this Order, please return here and type 'leave order'.\n");
  clone_object(DRYPLAIN+"sacred_brooch")->move(TP);

  CIRATH_LOG("order members",TP->query_real_name()+"\n");
  return 1;
}

