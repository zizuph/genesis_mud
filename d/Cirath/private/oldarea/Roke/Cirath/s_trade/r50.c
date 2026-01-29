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
           "You are standing on a quite large, stone-bricked road. This road is called "+
           "'The Southern Trade Route' and leads from Tyr into "+
           "the kingdom of Cirath to the city Ciubori. It's well-used by merchants that "+
           "thinks the long journey is worth it. East, the road leads into a vast, rocky "+
           "desert and northwest towards the gates.\n"
           ,60));  

  add_item(({"tyr","Tyr","gate","gates"}),"You can see the gates to the northwest.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");

  OUTSIDE;

  add_exit(S_TRADE+"r49","east");
  add_exit("/d/Roke/Athas/room/tyr/specials/stadgate2","northwest");

}
