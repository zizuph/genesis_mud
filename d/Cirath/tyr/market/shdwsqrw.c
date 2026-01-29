 /* shdwsqrw.c
  * Shadow square, west end
  * Decius, December 1996
  */

#pragma strict_types
#pragma save_binary

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"
#include "/d/Cirath/std/block.h"


void
reset_room()
{
    bring_room_mob("traders", TYR_NPC+"mrkt_mob.c", 1);
}

void
create_room()
{
  ::create_room();
  set_short("Shadow Square west end");
  set_long("This is a relatively tame section of shadow "+
    "square. Vendors here sell some small animals, and "+
    "even a few slaves... nothing of any great interest "+
    "or intrigue. For that you would go south, into the "+
    "elven market.\n");

  add_item("slaves","They are pathetic hungry creatures "
   +"being sold for a high profit to anyone desiring them.\n");

  ADD_SUN_ITEM;
  ADD_ZIG_ITEM;
  OUTSIDE;

  add_exit(TYR_MARKET+"shdwsqrn.c","north",0,1,0);
  add_exit(TYR_PAINT+"bdpnt.c","west",0,1,0);
  add_exit(TYR_MARKET+"elfmkt.c","south",0,1,0);
  add_exit(TYR_MARKET+"shdwsqrs.c","southeast",0,1,0);
  add_exit(TYR_MARKET+"shdwsqre.c","east",0,1,0);
  add_exit(TYR_MARKET+"bardqrtr.c","northeast",0,1,0);

  reset_room();
}
