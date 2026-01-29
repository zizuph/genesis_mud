inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

// Prototypes
int delay_north();
int move_me();

void
create_moria_room()
{
  set_short("By a pool");
  set_long("A narrow chimney angels upwards above a small, crystal "+
     "clear pool of water here. The walls of this alcove have been "+
     "worn smooth over the ages by the constant trickle of water "+
     "running from the chimney. To the north you can see the "+
     "cleft running through this area of rock, and stone.\n");

  add_exit("/d/Shire/khazad/wd1","north","@@delay_north@@",1);
}

int
delay_north()
{
  set_alarm(5.0, 0.0, &move_me());
  write("You carefuly start towards the northern exit keeping the deadly "+ 
        "trolls in front of you at all times\n");
  return 1;
}

int
move_me()
{
  TP->move_living("north","/d/Shire/khazad/west/wd1",0,0);
  return 1;
}


