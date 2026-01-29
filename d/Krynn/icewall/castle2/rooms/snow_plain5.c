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

    add_exit("conquer13","northwest","@@northwest",1,1);
    add_exit("conquer14","north","@@north",1,1);
    add_exit("conquer16","west","@@west",1,1);
    add_exit("conquer22","southeast","@@southeast",1,1);
    add_exit("conquer21","south","@@south",1,1);
    add_exit("conquer17","east","@@east",1,1);
    add_exit("snow_plain4","southwest","@@southwest",1,1);
    add_exit("snow_plain6","northeast","@@northeast",1,1);

    add_item(({"sled marks","marks"}),"The sharp, frozen " +
      "surface of the fresh snow is cut deep by twin parallel " +
      "marks of a sled being pulled by humans, dogs, or something " +
      "else alltogether." +
      "Judging by the vastness of the snow field surrounding you, " +
      "it would be suicide to try and find a way on your own. " +
      "Better to follow the sled, wherever it went, and hope it " +
      "and its owners didnt fall into a bottomless ravine or fell " +
      "to one of the myriad of horrible deaths readily available " +
      "in the frozen land. The sled marks visible here lead " +
      "northeast and southwest, heading in a straight line for " +
      "a while. Mayhaps all is in order.\n");

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
   "You are standing on vast, snow-covered plains. In all " +
   "directions the snow sparkles as far as you can see. " +
   "There are some sled marks visible here.\n");
  
}
              
int
east()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "east. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading east.\n");
  return 0;
} 

int
west()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "west. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading west.\n");
  return 0;
}
          
int
southwest()
{ 
  write("You smartly follows the sledmarks to the southwest.\n");
  say(QCTNAME(TP) + " follows the sledmarks to the southwest.\n");
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
northwest()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "northwest. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading northwest.\n");
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
  write("You smartly follows the sledmarks to the northeast.\n");
  say(QCTNAME(TP) + " follows the sledmarks to the northeast.\n");
  return 0;
}
