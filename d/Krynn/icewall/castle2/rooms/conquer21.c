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


    add_exit("snow_plain4","west","@@west",1,1);
    add_exit("conquer22","east","@@east",1,1);  
    add_exit("conquer26","southwest","@@southwest",1,1);
    add_exit("conquer27","south","@@south",1,1);
    add_exit("conquer28","southeast","@@southeast",1,1);
    add_exit("conquer16","northwest","@@northwest",1,1);
    add_exit("conquer17","northeast","@@northeast",1,1);
    add_exit("snow_plain5","north","@@north",1,1);

   set_area_name(WAR_AREA_ICEWALL);

   add_item(({"snow","plains"}),"Lifeless and dead. Nothing could ever " +
     "grow here.\n");
   add_item(({"cliff","icy cliff","cliffs","icy cliffs"}),"Tall and " +
     "dangerous, the cliffs form a natural barrier running through the " +
     "ice plains.\n");

   set_tell_time(900);

   add_tell("It is hellishly cold, and the wind picks up. Move before " +
    "frostbite kills you... To stay motionless is to die.\n");
   add_tell("The wind howls in cold fury.\n");
   add_tell("Snow falls from the heavy sky, obscuring your vision.\n");
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
   "You are standing on vast, snow-covered plains of Icewall. " +
   "Everywhere you look there is only cold, lifeless snow...\n");
  
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
northwest()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "northwest. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading northwest.\n");
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
northeast()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "northeast. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading northeast.\n");
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
southwest()
{ 
  write("With quite an effort, you brave the deep snow trudging " +
    "southwest. The effort and the biting cold drains your health.\n");
  TP->heal_hp(-random(100));
  say(QCTNAME(TP) + " trudges through the deep snow, heading southwest.\n");
  return 0;
}