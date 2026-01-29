/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r08.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You're on the southern trade-route. West lies a bridge over "+
           "the river Durni and east a jungle. The road leads in north-"+
           "south direction. A small path leads northeast into the jungle.\n");  

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

  add_exit(S_TRADE+"r09","north",0,1);
  add_exit(S_TRADE+"r07","south",0,1);
  add_exit(JUNGLE+"road/bridge","west",0,1);
  add_exit(JUNGLE+"j11","northeast",0,1);
  reset_room();
}
