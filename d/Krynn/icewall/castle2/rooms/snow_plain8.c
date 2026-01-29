#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/warfare/warfare.h"

#include <macros.h>
#include <stdproperties.h>

inherit ICEOUTROOM2;

void
create_icewall_room()
{

    set_short("On the vast snow plains");
    set_long("@@long_descr");

    set_area_name(WAR_AREA_ICEWALL);

    add_exit("snow_plain7","west","@@west",1,1);
    add_exit("snow_plain9","east");
    add_exit("snow_plain10","north","@@noenter_camp",1,1);

    add_item(({"sled marks","marks"}),"The sharp, frozen " +
      "surface of the fresh snow is cut deep by twin parallel " +
      "marks of a sled being pulled by humans, dogs, or something " +
      "else alltogether. They appear out of nowhere, presumably " +
      "sliding from a more solid surface of an ice or densly packed " +
      "snow, and cut deeply into the frozen fresh snow to your west. " +
      "Judging by the vastness of the snow field surrounding you, " +
      "it would be suicide to try and find a way on your own. " +
      "Better to follow the sled wherever it went, or wherever it " +
      "came from...\n");
    add_item("ocean","You are too far away to notice anything more.\n");

   set_tell_time(900);

   add_tell("It is hellishly cold, and the wind picks up. Move before " +
    "frostbite kills you... To stay motionless is to die.\n");
   add_tell("You could swore you heard a guttural laughter carried here " +
    "by the bone-chilling wind from the north...\n");
   add_tell("Squinting, you can just make out campfires flickering to " +
    "the north.\n");
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
   "You are standing on vast, snow-covered plains. To your " +
   "west, the snow sparkles as far as you can see, but to " +
   "your east, quite some distance away, you can squint and see " +
   "a dark, cold ocean spreading to the horizon. There are some sled marks " +
   "visible here.\n");
  
}
            
int
noenter_camp()
{
   write("You attempt to move north, but suddenly step on the edge " +
    "of a great ravine! Tumbling back, you manage not to fall inside, " +
    "but the slippery edge gave you quite a fright. From your adventure, " +
    "you managed to profit - you moved far enough north to realize that this " +
    "is indeed a dragonarmy encampment, " +
    "and if the tales are to be trusted, it must be the dreaded White.\n");
   say(QCTNAME(TP) + " tries to move north, but almost manages to slip " +
    "into a bottomless ravine and shaking, decides to abandon the venture.\n");
   return 1;
}
 
int
west()
{ 
  write("You smartly follows the sledmarks to the west.\n");
  say(QCTNAME(TP) + " follows the sledmarks to the west.\n");
  return 0;
}