inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "You're on the southern trade-route. West lies a bridge over "+
           "the river Durni and east a jungle. The road leads in north-"+
           "south direction. A small path leads northeast into the jungle.\n"
           ,60));  

  add_item("jungle","It's a jungle, what more is it to say?\n");
  add_item(({"river","water","stream"}),"This is the large river Durni "+
           "which flows down to the south coast of Cirath. It's very "+
           "big.\n");
  add_item(({"bridge","stonebridge"}),"This bridge leads over the "+
           "river. It looks sturdy.\n");
  add_item("road","This is the road that leads from Tyr to the cirathian city "+
           "Ci'u'bori.\n");
  add_item("path","It's a little path leading into the thick jungle to the east.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r09","north");
  add_exit(S_TRADE+"r07","south");
  add_exit(JUNGLE+"road/bridge","west");
  add_exit(JUNGLE+"j11","northeast");

}
