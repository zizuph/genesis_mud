inherit "/std/room";
inherit "/w/stark/celtcamp/rooms/trainingtents/trainingtentbase";
#include "/w/stark/defs.h"
#include <macros.h>
void
 create_room()
 {
  ::create_room();
  summon_ktrain();
  summon_ktrain();
  summon_ktrain();
  summon_ktrain();
  summon_ktrain();
  
  add_exit(CAMP_DIR3+"training8","out",0,0);
  
  
}