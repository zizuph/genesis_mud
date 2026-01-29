inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a desert path");
  
  set_long(break_string(
           "You are travelling on a small path in the desert canyon. The canyon is "+
           "very impressive and on the eastern edge of it, you can see some sort of "+
           "wall.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("wall","It's high and reaches to the horizon in both north and south directions.\n");
  add_item("canyon","It's deep and impressive.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");

  OUTSIDE;

  add_exit(NOMADS+"r03","north");
  add_exit(NOMADS+"r01","south");
}
