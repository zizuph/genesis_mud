inherit "/std/room";
#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <money.h>
#include <macros.h>

object inquisitor;

create_room()
{
  set_short("In the large Temple Dome");
  set_long(break_string("You are in the large Temple Dome. "+
           "This dome was built a long time ago and you wonder if this isn't the largest "+
           "underground system ever made by man. You are about 100 meters below earth. "+
           "The walls are lit up by torches. You can see ancient artifacts and statues of long time  "+
           "dead leaders of this Order. To the north you can se the present inquisitor's throne. "+
           "The throne is fastened in the wall a few meters above ground so that you can't sit in it. \n",70));

  add_exit(DRYPLAIN+"sacred_room","south");
  call_out("reset_room",1);
  add_item("throne","This throne looks very ancient. It has some strange runes ingraved.\n");
  add_item("statue","The staues resembles of previous great leaders in chronological order.\n"); 
  add_item("statues","The staues resembles of previous great leaders in chronological order.\n");
  add_item("torches","Large torches fastened in old and rusty torchstands.\n");
  add_prop(ROOM_I_INSIDE, 1);
}
reset_room()
{
  seteuid(getuid());

  if(!inquisitor)
    {
      inquisitor = clone_object(MONSTER+"inquisitor");

      inquisitor->move(TO);
    }
}