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
           "You are standing on a road that leads through the rocks in a desert canyon."+
           "The canyon was propably made by a river that dried out long ago. The sun burns "+
           "your shoulders and the "+
           "sweat is pouring from your skin. This is no place to live, unless you "+
           "can survive on eating rocks.\n"
           ,60));  

  add_item("canyon","The canyon is pretty deep. and has quite impressive shapes.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r40","east");
  add_exit(S_TRADE+"r42","west");

}
