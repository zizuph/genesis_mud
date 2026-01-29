inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("By a river");
  
  set_long(break_string(
           "You are standing on the west side of the mighty river "+
           "Durni. There's a large stonebridge here, leading over "+
           "the streaming water. West lies the jungle and on the "+
           "other side the river, the jungle continues.\n"
           ,60));  

  add_item("jungle","It's a jungle, what more is it to say?\n");
  add_item(({"river","water","stream"}),"This is the large river Durni "+
           "which flows down to the south coast of Cirath. It's very "+
           "big.\n");
  add_item(({"bridge","stonebridge"}),"This bridge leads over the "+
           "river. It looks sturdy.\n");

  OUTSIDE;

  add_exit(JUNGLE+"road/bridge","east");
  add_exit(JUNGLE+"j10","southwest");
}
