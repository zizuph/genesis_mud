#include <macros.h>

inherit "/std/object";

create_object() 
{
  set_name("test");
  set_short("test");
}

int 
shit2() 
{
  object *list;
  int i;

  list = all_inventory(environment(this_player()));		       
  list->catch_msg(QCTNAME(list) + "\n");; 
}
