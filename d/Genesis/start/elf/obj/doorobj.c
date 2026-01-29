#include "../stddefs.h"
#include <stdproperties.h>

#pragma save_binary

inherit "std/door";


void create_object()
{
  ::create_object();

  unset_no_show();
  set_no_show_composite(0);
}

void set_door_id(string id) 		
{ 
  door_id = id; 
}
