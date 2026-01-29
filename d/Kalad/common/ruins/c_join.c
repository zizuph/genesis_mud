inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/zhent/defs.h"
#include <money.h>
#include <macros.h>

create_room()
{
  set_short("Consecration room");
  set_long("You have entered the darkest confines within the temple "
	+"to Cyric. This room is lit only by the circle of candles "
	+"that is in the middle of the room. Within the circle is "
	+"pentagram painted in blood, and lines with gold dust. This "
	+"is the circle within which the consecration vows must be "
	+"taken. Those who are 'accept' a 'baptism' in the blood of "
	+"Cyric will be forever protected from harm.\n");
  add_item(({"candles","candle"}),"They are burning low, only giving "
        +"off a small amount of light.\n");
  add_item(({"circle"}),"The circle is painted with blood, and is lined "
	+"with a ring of gold dust.\n");
  add_item(({"cloth"}),"The pentagram is large and painted in blood.\n");
  add_item(({"blood"}),"It is very dark, red, and dry.\n");
  add_cmd_item("circle","enter","You enter the circle, now you may "
	+"experience the baptism of Cyric.\n");
  add_prop(ROOM_NO_TIME_DESC,1);
}
init()
{
  ::init();
    add_action("accept","accept");
    add_action("renounce","renounce");
  }
renounce(string s)
{
  NF("Renounce what? Your faith?\n");
  if(s!="faith")
    return 0;

  NF("You're not a follower of the one true God!\n");
  if(!present("c_club",TP))
    return 0;
  present("c_club",TP)->remove_object();

  write("You renounce your faith in Cyric. You seem to hear an unearthly "
	+"chuckle, and you shiver.\n");
  say(QCTNAME(TP)+" renounces " + TP->query_possessive() + "faith in Cyric.\n");
  return 1;
}
accept(string s)
{
        NF("Accept what?\n");
    if(s!="baptism")
    return 0;
  say(QCTNAME(TP)+" accepts a baptism in the blood of Cyric.\n");
  write("You recieve an emblem.\n");
  write("To renounce your faith in Cyric, return here and type 'renounce "
   +" faith'.\n");
  clone_object(ZHENT+"obj/c_club")->move(TP);
  return 1;
}
