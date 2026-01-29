inherit "/d/Immortal/std/room";
#include "/d/Immortal/std/domain.h"

ceate_room() {
  set_short("In between the dimensions of life and death");
  set_long("You are floating around in total blackness - or are you dreaming?\n");
}

int
blockact()
{
  write("You are in some kind of dream, unable to wake up.\n");
  return 1;
}

int
allow_commune(string str)
{
  write("Even in your chomatose dream, you feel able to commune.\n");
  return 0;
}


init()
{
  ::init();
  add_action("blockact","",1);
  add_action("allow_commune","commune");
}

