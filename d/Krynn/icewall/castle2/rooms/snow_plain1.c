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

    add_exit("conquer10","north","@@north",1,1);
    add_exit("conquer11","northeast","@@northeast",1,1);
    add_exit("conquer18","south","@@south",1,1);
    add_exit("conquer19","southeast","@@southeast",1,1);
    add_exit("east_path5","west","@@west",1,1);
    add_exit("snow_plain2","east","@@east",1,1);

    add_item(({"sled marks","marks"}),"The sharp, frozen " +
      "surface of the fresh snow is cut deep by twin parallel " +
      "marks of a sled being pulled towards, or from the castle. " +
      "Judging by the vastness of the snow field surrounding you, " +
      "it would be suicide to try and find a way on your own. " +
      "Better to follow the sled, wherever it went, and hope it " +
      "and its owners didnt fall into a bottomless ravine or fell " +
      "to one of the myriad of horrible deaths readily available " +
      "in the frozen land. The sled marks visible here lead east and west.\n");

   set_tell_time(900);

   add_tell("It is hellishly cold, and the wind picks up. Move before " +
    "frostbite kills you... To stay motionless is to die.\n");
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
   "east, the snow sparkles as far as you can see, but to " +
   "your west, it rises sharply into a frozen hill upon which " +
   "you can see an ice-covered, gloomy castle. There are some " +
   "sled marks visible here.\n");
  
}

int
east()
{ 
  write("You smartly follows the sledmarks to the east.\n");
  say(QCTNAME(TP) + " follows the sledmarks to the east.\n");
  return 0;
} 

int
west()
{ 
  write("You smartly follows the sledmarks to the west.\n");
  say(QCTNAME(TP) + " follows the sledmarks to the west.\n");
  return 0;
}
          
int
south()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "south. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading south.\n");
  return 0;
}  

int
southeast()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "southeast. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading southeast.\n");
  return 0;
}

int
north()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "north. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading north.\n");
  return 0;
}

int
northeast()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "northeast. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading northeast.\n");
  return 0;
}
