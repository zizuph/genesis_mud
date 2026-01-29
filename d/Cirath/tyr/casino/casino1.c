/* casino1.c: Crystal Spider Casino Fountain. - Serpine 8/20/97. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/std/block.h"


void
create_room()
{
    ::create_room();
    set_short("the Crystal Spider's fountain");
    set_long("The casino known as the Crystal Spider seems out of "
            +"place in the chaos that is the elven market, though it does "
            +"have a reputation as the most notorious gambling hall in "
            +"Tyr. The entrance to the ancient, hulking structure is just "
            +"off to the southwest, past a small bubbling fountain.\n");
 
    add_item(({"market", "elven market"}),
              "You'd have to go north to see it.\n");
    add_item(({"stalls", "tent stalls", "stall", "tent stall"}),
             "Light, tough, and easy to pack up in a heartbeat.\n");
    add_item("merchandise", "Mostly cheap trinkets and old pieces "
             +"of junk, and probably all of it stolen.\n");
    add_item(({"casino", "crystal spider", "crystal spider", "casino",
               "ancient hulking structure", "structure"}),
             "Its not much to look at, but the appearances can decieve.\n");
    add_item(({"fountain","bubbling fountain",
               "small bubbling fountain","small fountain"}),
             "For a moment you can almost imagine what the fountain "
            +"would look like if it flowed with real water rather "
            +"than the city's waste products.\n");
 
  ADD_SUN_ITEM;
  OUTSIDE;
 
   add_exit(TYR_MARKET+"elfmkt.c","north",0,1,0);
   add_exit(TYR_MARKET+"casino2.c","southwest","@@block_exit@@",1,0);
}
