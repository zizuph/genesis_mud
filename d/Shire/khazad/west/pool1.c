
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("By a pool");
  set_long("A narrow chimney angels upwards above a small, crystal "+
     "clear pool of water here. The walls of this alcove have been "+
     "worn smooth over the ages by the constant trickle of water "+
     "running from the chimney. To the north you can see the "+
     "cleft running through this area of rock, and stone.\n");

  add_exit("/d/Shire/khazad/west/wd1","north",0,1);
}
 
int
do_drink(string str)
{
  if (!str)
    return 0;
 
  else if (str == "water from pool" || str == "from pool")
  {
    if (TP->drink_soft(TP->drink_max()/25,0))
    {
      write("You get down on one knee and take a quick sip "+
            "of water.\n");
      say(QCTNAME(TP)+" goes down on one knee and takes a quick "+
          "sip of water.\n");
      return 1;
    }
 
    else
    {
      write("You don't feel like you can drink anymore.\n");
      return 1;
    }
  }
}
 
void
init()
{
  ::init();
  add_action(do_drink, "drink");
}
