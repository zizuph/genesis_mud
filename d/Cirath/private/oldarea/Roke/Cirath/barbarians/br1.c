inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"

void create_room()
{
  set_short("Road in Barbarian Camp");
  set_long(break_string("This is a road that leads through the camp in "+
           "east-west direction. To the east it leads further into the "+
           "camp and west out of it. The road itself is made of sand. "+
           "North and south there are entrances to clan tents.\n",60));

  add_item((("tents")),"The tents belongs to two of the barbarian clans./n");
  add_item((("tent")),"There's a lot of them you know...\n");
  add_item(({"north tent","northern tent"}),"In this tent the Dragon Clan "+
             "rest.\n");
  add_item(({"south tent","southern tent"}),"This tent is closed for the "+
             "time being.\n");
  add_item((("dust")),"The wind is whirling it up from the ground.\n");
  add_item((("sand")),"Of course it's sand in a desert, what did you think?\n");
  add_item(({"path","paths"}),"They are well-travelled...\n");
  add_item((("camp")),"You're standing in it...The mighty Barbarian Camp!\n");

  add_exit(BARBARIANS+"br2","east");
  add_exit(BARBARIANS+"bo1","west");
  add_exit(BARBARIANS+"clan1","north");
  add_exit(BARBARIANS+"clan2","south","@@stop");
}

int
stop()
{
  write("The tent is closed.\n");
  return 1;
}