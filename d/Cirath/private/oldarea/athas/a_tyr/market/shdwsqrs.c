 /* /d/Cirath/athas/a_tyr/market/shdwsqrs.c
  * Shadow square, south end
  * Decius, December 1996
  */

#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/d/Cirath/std/block.h"
#include "/d/Cirath/common/mobber.h"
 
void
reset_room()
{
    bring_room_mob("traders", ATH_PERSON+"mrkt_mob.c", 1);
}

void
create_room()
{
  ::create_room();
  set_short("Shadow square south end");
  set_long("The heat of the blazing sun radiates in "+
    "shimmering waves from the ground, and the hide roofs "+
    "of the many tiny stalls here in shadow square. "+
    "All around, vendors hawk their wares with shrieking "+
    "calls, competing with each other and with the elven "+
    "market to the west. Customers of all races wander "+
    "through here, though noticably few of them are elves. "+
    "Shadow square continues to the north, and entrances "+
    "to buildings are to the east and south.\n");

  add_item("elves","You notice that the few elves to be seen "+
    "are scurrying quickly towards their destinations, all "+
    "the while glaring evilly towards the building to the east.\n");
  add_item(({"wares","products"}),"Slightly used, previously "+
    "owned, or as the vendors prefer, 'experienced' goods "+
    "are for sale here.\n");
  ADD_SUN_ITEM;
  ADD_ZIG_ITEM;

  add_item("vendors","They shriek, wail, anything to draw "+
    "your attention.\n");

  OUTSIDE;

  add_exit(TZ_MARKET+"shdwsqre.c","north",0,1,0);
  add_exit(TZ_MARKET+"hhh.c","east",0,1,0);
  add_exit(TZ_MARKET+"elfmkt.c","west",0,1,0);
  add_exit(TZ_MARKET+"shdwsqrw.c","northwest",0,1,0);
  add_exit(TZ_MARKET+"souvenir.c","south","@@block_exit@@",1,0);

  reset_room();
}
