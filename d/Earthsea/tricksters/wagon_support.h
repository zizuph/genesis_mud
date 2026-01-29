#include <macros.h>

#include "defs.h"

object wagon;

void init_wagon_support()
{
 add_cmd_item("rope","pull","@@pull_rope");
}

int pull_rope()
{
 say(QCTNAME(TP)+" pulls the rope.\n");
 
 if((INSIDE_WAGON)->query_moving())
  {
   write("Wagon is currently moving.\n");
   return 1;
  }

 if(present("_trick_wagon_",TO))
  {
   write("But wagon is already here!\n");
   return 1;
  }

 (INSIDE_WAGON)->start_moving();
 write("Wagon is on its way.\n");
 return 1;
}

