 /* /d/Cirath/athas/a_tyr/market/elfmkt.c
  * The elven market.
  * Decius, December 1996 | Serpine, 08/20/97
  */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/std/block.h"


void
create_room()
{
  ::create_room();
  set_short("the elven market");
  set_long("There are elves aplenty here in the elven market, "+
    "a place of infamy, where everything can be bought or sold. "+
    "Sharp eyed elven merchants watch from their tent stalls, "+
    "keeping wary watch for any sign of a templar patrol, prepared "+
    "to 'rearrange' their merchandise, or even flee if necessary. "+
    "To the north and east shadow square surrounds the market, "+
    "while south is the Crystal Spider Casino, and west are the "+
    "gray-brown residences of the vendors.\n");
 
    add_item(({"elves", "elf", "elven merchant", "elven merchants", "vendor", "vendors"}),
             "'Never trust an elf selling gifts' starts an old saying. "
             +"'Assuming your foolish enough to trust an elf at all.'\n");
    add_item(({"stalls", "tent stalls", "stall", "tent stall"}),
             "Light, tough, and easy to pack up in a heartbeat.\n");
    add_item("merchandise", "Mostly cheap trinkets and old pieces "
             +"of junk, and probably all of it stolen.\n");
    add_item(({"casino", "crystal spider", "crystal spider", "casino"}),
             "The arch above the gate is a silver-plated spider.\n");
    add_item(({"gray-brown residences", "residences"}),
             "Not much to see, individual elves don't stick around long "
            +"enough to pretty things up.\n");
 
  ADD_SUN_ITEM;
  ADD_ZIG_ITEM;
  OUTSIDE;
 
   add_exit(TYR_MARKET+"shdwsqrs.c","east",0,1,0);
   add_exit(TYR_MARKET+"shdwsqrw.c","north",0,1,0);
   add_exit(TYR_MARKET+"shdwsqre.c","northeast",0,1,0);
   add_exit(TYR_MARKET+"elfhl.c","west","@@block_exit@@",1,0);
   add_exit(TYR_CASINO+"casino1.c","south",0,1,0);
}
