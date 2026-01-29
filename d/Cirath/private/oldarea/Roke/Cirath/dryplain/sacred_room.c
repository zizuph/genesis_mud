inherit "/std/room";
#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <money.h>
#include <macros.h>

object servant;

create_room()
{
  set_short("In the Temple");
  set_long(break_string("You are in the large Temple hall. The walls are covered with pictures and torches. "+
           "There is a small sign on the wall which you better read before doing anything. "+
           "In the middle of the room you can see a large altar with some sacred items on. "+
           "The atmosphere is peaceful and the only thing reminding you about the life outside "+
           "is the small hole in the roof letting frech air in. \n",70));

  add_exit(DRYPLAIN+"dpa6","up");
  add_exit(DRYPLAIN+"sacred_hall","north");
  call_out("reset_room",1);
  add_item("sign","@@sign");
  add_cmd_item("sign","read","@@sign");
  add_prop(ROOM_I_INSIDE, 1);
  add_item("altar","It looks like a large table with many sacred items on.\n");
}

sign()
{
  return "If you want to join our Holy Order you have to prove yourself worthy. \n"+
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
    add_action("disgrace","disgrace");
  }
disgrace(string s)
{
  NF("Do you want to leave something? Our Holy Order??\n");
  if(s!="order")
    return 0;

  NF("You're not a member!\n");
  if(!present("sacred_brooch",TP))
    return 0;

  present("sacred_brooch",TP)->remove_object();

  write("You leave the order. The servant gives you a wound with his sacred knife.\n"+
        "You start to bleed from a tiny wound. Although the wound stops bleeding almost \n"+
        "immediately and it only leaves an aching spot.\n");
  say(QCTNAME(TP)+" leaves our Sacred Order. \n"+
        "The Servant hurts him with his sacred knife, hard.\n");

  return 1;
}
sacrifice(string s)
{
    NF("Sacrifice what?\n");
    if (!s) return 0;
  if(!parse_command(s,TO,"[platinum] 'coin' 'in' / 'on' [the] 'altar'"))
    return 0;

  if(TP->query_alignment() < 1300)
     {
      write("You are not worthy to be a member. \n");
      say(QCTNAME(TP)+" is not worthy to join the Holy Temple Order. \n");
      return 1;
     }

  if(TP->query_prop(CIRATHCLUB)==1)
    {
     write("We don't need your assistance in our Order, You have already found your party. \n");
     say(QCTNAME(TP)+" isn't worthy to join the Society. \n");
     return 1;
     }

  if(TP->query_race_name() == "goblin")
     {
      write("You are not enough worthy to be a member, because we don't like goblins at all. \n");
      say(QCTNAME(TP)+" is not worthy to join the Holy Temple Order. \n");
      return 1;
     }

  if(TP->query_gender() ==1)
     {
      write("We don't want any women in our society. Sorry but such are our rules. \n");
      say(QCTNAME(TP)+" is not worthy to join the Holy Temple Order. \n");
      return 1;
     }


  if(!servant)
      reset_room();

  NF("You don't have any platinum coins.\n");
  if("/sys/global/money"->move_coins("platinum",1,TP,servant))

    return 0;
  
  say(QCTNAME(TP)+" joins The Holy Temple Order.\n");
  write("You recieve a ametist brooch. \n"+
        "You have now joined the Holy Temple Order. May the gods be with you. \n");
  write("If you REALLY wants to leave this Order, please return here and type 'leave order'.\n");
  clone_object(OBJ+"sacred_obj")->move(TP);

  write_file(CIRATH_LOG,TP->query_real_name()+" joined The Holy Temple Order "+
     extract(ctime(time()),4,15)+"\n");
  return 1;
}