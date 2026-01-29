 /* /d/Cirath/athas/a_tyr/market/elfmkt.c
  * The elven market.
  * Decius, December 1996
  */

#pragma strict_types
#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"

void
create_room()
{
  ::create_room();
  set_short("The elven market");
  set_long("There are elves aplenty here in the elven market, "+
    "a place of infamy, where everything can be bought or sold. "+
    "Sharp eyed elven merchants watch from their tent stalls, "+
    "keeping wary watch for any sign of a templar patrol, prepared "+
    "to 'rearrange' their merchandise, or even flee if necessary."+
    "To the north and east shadow square surrounds the market, "+
    "while south is the Crystal Spider Casino, and west are the "+
    "gray-brown residences of the vendors.\n");

  ADD_SUN_ITEM;
  ADD_ZIG_ITEM;
  OUTSIDE;

  add_exit(TZ_MARKET+"shdwsqrs.c","east",0,1,0);
  add_exit(TZ_MARKET+"shdwsqrw.c","north",0,1,0);
  add_exit(TZ_MARKET+"shdwsqre.c","northeast",0,1,0);
  add_exit(TZ_MARKET+"elfhl.c","west","@@block_exit@@",1,0);
  add_exit(TZ_MARKET+"casino1.c","south","@@block_exit@@",1,0);
}
