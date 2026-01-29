// stair11
// grace april 1994

#include "../local.h"
inherit SPURRM;


create_spur_room()
{
   SHORT("Tower stair, level three");
   LONG("You stand at the third floor exit on a circular "
      + "stairwell "
      + "that connects the second and third floors of the " 
      + "Knights' Spur with the towers and battlements.\n");

   INSIDE;
   LIGHT;

   add_exit(ROOM + "stair10", "down",0);
   add_exit(ROOM + "pass4l3", "south", 0);
   add_exit(ROOM + "stair12", "up", "@@block");

   AI("door", "A hastily-constructed door blocking further passage "+
        "upwards. It is locked.\n");
   AI("lock", "It is a very heavy lock. It looks to be unpickable.\n");
   AI("sign", "It is printed in block letters.\n");
   ACI("sign", "read", 
        "       The battlements are under repair due to damages\n"+
        "       caused during the last DragonArmy attack.\n");
}                

block()
{
       write("Your progress up the stairs is blocked by a roughly-"+
        "made door.\nOn the door is a small sign.\n");
        return 1;
}

