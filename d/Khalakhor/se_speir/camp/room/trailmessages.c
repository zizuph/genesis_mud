inherit "/std/room";
#include "/w/stark/defs.h"
#include <macros.h>
#include "/d/Krynn/haven/local.h"

void
 create_room()
 {
  ::create_room();
  set_short("In a large open clearing");
  
}

void
summon_ktrain()
{
    setuid();
    seteuid(getuid());
    
    object guard;
    
    guard = clone_object("/w/stark/celtcamp/ktrain.c");
    guard->move(this_object());
}
 