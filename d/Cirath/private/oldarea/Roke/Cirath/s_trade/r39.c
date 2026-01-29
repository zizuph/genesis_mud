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
           "You are standing on a bricked road in a desert made of rocks. The "+
           "surroundings looks deserted and you're glad that there is a road "+
           "here, so you don't have to walk in this hard-travelled terrain. The "+
           "canyon grows wider here.\n"
           ,60));  

  add_item("canyon","A, nowadays, dried-out river must have created it a long time ago.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");

  OUTSIDE;

  add_exit(S_TRADE+"r38","east");
  add_exit(S_TRADE+"r40","southwest");

}
