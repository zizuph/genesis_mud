/*
 * Goblin village elder servant
 * TAPAKAH 04/2005
 */

#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h";
#include <macros.h>

inherit VILLAGER;

int bribeme(string str);
void
create_khalakhor_monster()
{
  if(! IS_CLONE)
    return;
  ::create_khalakhor_monster();

  set_name("servant");
  set_long(query_long() + "He is a servant of the village elder.");
  
}
void
init_living()
{

  ::init_living();

  add_action(bribeme,"bribe");
}
int
bribeme(string str)
{
  string who;
  
  if(!str) {
    notify_fail("Bribe who?\n");
    return 0;
  }
  if(sscanf(str,"%s",who) == 1) 
    if(who == "servant") {
      write("You try to bribe the servant, but fail.\n");
      return 1;
    }
  notify_fail("Bribe who?\n");
  return 0;
}
