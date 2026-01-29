inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/zhent/defs.h"
#include <money.h>
#include <macros.h>

object oldbitch;

create_room()
{
  set_short("inside a hut");
  set_long("This is the inner sanctum of the temple of Bane. Here "
	+"new initiates are asked to pledge themselves to Bane. The "
	+"room is dimly lit, a few candles providing the only light. "
	+"There is an altar in the center of the room, here the "
	+"new priests are initiated.\n");
  add_item(({"candles","candle"}),"They are burning low, only giving "
	+"off a small amount of light.\n");
  add_item(({"altar"}),"The altar is streaked with blood, and is covered "
	+"with a red velvet cloth.\n");
  add_prop(ROOM_NO_TIME_DESC,1);
  add_item(({"cloth"}),"It is made of red velvet.\n");
  add_item(({"sign"}),"Try to read it.\n");
  add_cmd_item("sign","read","@@sign");
  add_cmd_item("at altar","pray","You pray at the altar. Your soul feels "
	+"tarnished and black.\n");
} 
sign()
{
  return "To join us, pledge your soul to Bane.\n";
}
init()
{
  ::init();
    add_action("pledge","pledge");
    add_action("revoke","revoke");
  }
revoke(string s)
{
  NF("Revoke what? Your pledge?\n");
  if(s!="pledge")
    return 0;

  NF("You're not a follower of the one true God!\n");
  if(!present("b_club",TP))
    return 0;
  present("b_club",TP)->remove_object();

  write("You revoke your pledge to Bane. The clouds darken, and "
	+"thunder rumbles in the distance. This day you have made "
	+"an enemy.\n");
  say(QCTNAME(TP)+" revokes" + TP->query_possessive() + " pledge to Bane.\n");

  return 1;
}
pledge(string s)
{
	NF("Pledge what?\n");
    if(s!="soul")
    return 0;
  say(QCTNAME(TP)+" pledges " + TP->query_possessive() + " soul to Bane.\n");
  write("You recieve an insignia.\n");
  write("To revoke your pledge to Bane, return here and type 'revoke pledge'.\n");
  clone_object(ZHENT+"obj/b_club")->move(TP);
  return 1;
}
