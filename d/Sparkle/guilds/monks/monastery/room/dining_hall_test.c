#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

//inherit M_ROOM_BASE;
//inherit "/std/room";
inherit "/d/Sparkle/std/room/room_test";

void create_room ()
{

  set_short ("dining hall");
  set_long ("This is a long, warm room with a very high ceiling. " +
            "A doorway in the west wall leads out into a dark hall.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_lower_south", "west");
  add_item (({"test"}), "test @@dg_test|test2@@");
  add_item (({"test2"}), "test @@dg_test@@");
  add_item (({"test3"}), "test @@dg_test2@@");
}

string dg_test (
  string sMessage)
{
  this_player()->catch_tell("bah" + "\n");
  return ("Hmm\n");
}

string dg_test2 ()
{
  this_player()->catch_tell("bah" + "\n");
  return ("Hmm\n");
}
