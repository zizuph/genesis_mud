// Paralyzes a player while he's holding a slab in l4/n26 to allow
// other players entering the worm lair.

#include "/d/Avenir/common/dark/dark.h"
#define SLAB_ROOM "n26"

inherit "/std/paralyze";

void
create_paralyze()
{
  ::create_paralyze();
  
  set_stop_verb ("drop");
  set_stop_fun ("do_drop");
  set_stop_object(this_object());
  set_fail_message (
    "You are busy holding the slab. You must drop it first.\n");
  set_stop_message (0);
  set_remove_time (300);
  // The paralyze should be removed earlier than that by the room cloning
  // it. Make thew time here is greater than time delay set in l4/n26
  // by do_hold function.
}


int
do_drop(string str)
{
  object tp = this_player();
    
  if (!str || str != "slab")
    {   
      tp->catch_msg ("Drop what?\n");
    return 0;
    }
  call_other(L4+SLAB_ROOM, "wait_for_free", tp);
  return 1;
}





