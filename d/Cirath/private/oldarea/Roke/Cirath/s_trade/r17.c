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
           "This is the southern trade-route that leads from Tyr to "+
           "the cirathian city Ciubori. The road is made of stone "+
           "bricks that have been polished by all the feets that have "+
           "walked on them. The view from here is great. North, the "+
           "mountain Dohrath can be seen, with all its might. To the "+
           "south is a stream and on the other side a jungle. A little "+
           "village is to the northeast and to the west, there is a green "+
           "forest surrounded by mist.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"water","stream"}),"The stream flows fast and the water is "+
           "clear.\n");
  add_item("village","It's one of the poor villages that are inhabited by "+
           "the 'inlanders' as the cirathian people prefer to call them./n");
  add_item(({"dohrath","mountain","peak","peaks","my-doh","kar-doh","suri-doh",
           "nih-doh"}),"Dohrath is a very impressive mountain.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item("forest","It's a dark green forest. Somewhat threatening with all "+
          "that fog around it.\n");
  add_item(({"fog","mist"}),"It is surrounding the forest.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r18","west");
  add_exit(S_TRADE+"r16","northeast");

}
