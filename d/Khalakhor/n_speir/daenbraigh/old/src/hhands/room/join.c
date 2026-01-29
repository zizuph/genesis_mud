/*
 * Hammerhands guild, join room
 * TAPAKAH, 10/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

inherit "/d/Khalakhor/std/room";
inherit HH_GUILDROOM;

string tattooer_desc();
string read_poster();
int hhjoin(string str);
int hhleave(string str);
int hhtattoo(string str);

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Hammerhands joinroom");
  set_long("You are standing in a spacy and nearly empty room of the "+
	   "cube-like building of the guild of Hammerhands. You see "+
	   "passages in various directions and a low arch leads out to the "+
	   "northeast. In a far corner a table with some unusual equipment "+
	   "stands. " + "@@tattooer_desc@@" +
	   "A large poster hangs on the wall.\n");
  add_item(({"table"}),
	   "It is a bit far off to distinguish its destination.\n");
  add_item(({"poster"}),"@@read_poster");

  add_exit("common","southwest",&check_enter(HH_ACCESS_ALL));
  add_exit("shop","northeast",&check_enter(HH_ACCESS_ALL));
  add_exit("train","southeast",&check_enter(HH_ACCESS_MEMBER));
  add_exit("dorm","east",&check_enter(HH_ACCESS_MEMBER));
  add_exit("pub","south",&check_enter(HH_ACCESS_ALL));
  add_exit("entrance1","northwest",&check_enter(HH_ACCESS_ALL));

  add_prop(ROOM_I_INSIDE,1);
  add_prop(HH_INSIDE,1);
  add_npc(HH_GM,1,&->equip_me());
  load_board(HH_PUBLIC_BOARD);
}

void
reset_room()
{
  ::reset_room();
}

void
init()
{
  ::init();
  add_action(hhjoin,"hhjoin");
  add_action(hhleave,"hhleave");
  add_action(hhtattoo,"hhtattoo");

}

int
hhjoin(string str)
{
  write("You have joined the Hammerhands.\n");
  return 1;
}

int
hhleave(string str)
{
  string dummy, how;

  if(! TP->query_prop(HH_MEMBER)) {
    notify_fail("What?\n");
    return 0;
  }
  if(str) 
    if(sscanf(str,"%s %s",dummy,how) == 2)
      if(dummy == "paying")
	if(how == "experience") {
	  write("Paying experience...\n");
	  return 1;
	}
	else if(how == "money") {
	  write("Paying money...\n");
	  return 1;
	}
  notify_fail("Leave paying money or leave paying experience?\n");
  return 0;
}

int
hhtattoo(string str)
{
  write("Getting a new tattoo.\n");
  return 1;
}

string
tattooer_desc()
{
  if(present("guildmaster",TO))
    return "An intense muscular goblin is sitting behind it. ";
  else
    return "";
}

string
read_poster()
{
  string text;

  text =
    "You read:\n\n"+
    "                   Welcome to Hammerhands guild.\n"+
    "Only confident enough veterans of bludgeon-capable weapons such as\n"+
    "clubs, polearms and axes may join.  We are good with the bludgeon,\n"+
    "                    but we are not good at all.\n"+
    "Use `hhjoin' to join!\n";
   
  return text;
}
