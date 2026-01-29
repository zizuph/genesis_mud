// file name:    ledge2
// creator(s):   Cirion, April 1996
// last update:  Lilith 24 Feb 2014: updated pass() so small players 
//                   don't get trapped
// purpose:      Ledge for the newbie area.
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"
  
void create_room()
{
  set_short("end of ledge");
  set_long("The ledge comes to a sudden end before you, falling down "
    +"into the dark sea far below and making it impossible to "
    +"travel any further along the rock wall. A narrow tunnel winds into the rock "
    +"to the west, leading into gloom and shadows.\n");

  ACI(({"down","ledge","cliff","up"}),"climb","The cliff is "
    +"sheer and unclimbable.\n");
  ACI(({"off","down","ledge","cliff"}),({"jump","leap"}),
     "That would be foolish.\n");

  AI(({"wall","walls","rock"}),"The rock face is "
    +"sheer, reaching up to the cavern ceiling high above.\n");
  AI(({"sea","water","down"}),"The dark sea far below spreads "
    +"out as far as the eye can see, broken here and there "
    +"by a number of islands of various sizes.\n");
  AI(({"island","islands"}),"You cannot make out any details "
    +"from here.\n");
  AI(({"down","cliff","dropoff","ledge"}),"The ledge is very "
    +"narrow, only as wide as your feet, and drops down "
    +"hundreds of meters to the sea below.\n");
  AI(({"cavern","ceiling"}),"The cavern ceiling lies high "
    +"above, veined with long lines of glowing rock that "
    +"provide light for the area.\n");

  IN;

  add_exit(OUTPATH+"ledge2", "southwest", "@@pass@@");
  add_exit(OUTPATH+"cave1", "west");
}

int pass()
{
  if(TP->query_panic() + LEDGE_PANIC > TP->query_stat(SS_DIS))
  {
    write("You are too scared to continue on. You better calm "
          +"down first.\n");
    return 1;
  }
/*
  if(random(TP->query_stat(SS_DEX)) < random(40))
  {
    TP->add_panic(LEDGE_PANIC * 2);
    say(QCTNAME(TP)+" stumbles and nearly loses "
      +POSSESS(TP)+" balance.\n");
    write("As you try to edge your way along, you stumble "
      +"slightly and nearly fall.\n");
    return 1;
  }
*/
  TP->add_panic(LEDGE_PANIC);
  write("You edge your way along the narrow ledge.\n");
  return 0;
}
