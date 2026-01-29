inherit "/std/room";
inherit "/w/stark/celtcamp/rooms/camp/tentbase";
#include "/w/stark/defs.h"

void
 create_room()
 {
  ::create_room();
  
  add_exit(CAMP_DIR2+"camp6","out",0,0);
  
  summon_kguard();
  summon_kguard();
  summon_kguard();
}
